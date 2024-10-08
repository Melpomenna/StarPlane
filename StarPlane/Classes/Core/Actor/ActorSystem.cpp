#include "ActorSystem.h"

#include <queue>
#include <Core/Actor/Actor.h>
#include <Core/Controller/EventControllerProcessor.h>

namespace Game
{
    namespace Core
    {
        namespace
        {
            ActorSystem *ACTOR_SYSTEM = nullptr;
        }


        ActorSystem::ActorSystem()
        {
            actors_.reserve(RESERVE_ACTORS_SIZE);
        }

        void ActorSystem::Destroy()
        {
            ::delete ACTOR_SYSTEM;


            ACTOR_SYSTEM = nullptr;
        }

        void ActorSystem::Init()
        {
            if (!ACTOR_SYSTEM)
            {
                ACTOR_SYSTEM = ::new ActorSystem();
            }
        }

        ActorSystem *ActorSystem::ResolveActorSystem()
        {
            return ACTOR_SYSTEM;
        }

        void ActorSystem::Update(const double dt)
        {

            for (auto actor : actors_)
            {
                actor->Update(dt);
            }
        }

        void ActorSystem::RegisterActor(Actor *actor)
        {
            if (actor == nullptr)
            {
                return;
            }

            if (std::find(actors_.cbegin(), actors_.cend(), actor) != actors_.cend())
            {
                return;
            }

            EventControllerProcessor::ResolveEventController()->SubscribeOnKeyboard(actor);
            EventControllerProcessor::ResolveEventController()->SubscribeOnMouse(actor);

            actors_.push_back(actor);
        }


        void ActorSystem::RemoveActor(Actor *actor)
        {
            if (actor == nullptr)
            {
                return;
            }

            auto pos = std::find(actors_.cbegin(), actors_.cend(), actor);
            if (pos == actors_.cend())
            {
                return;
            }

            EventControllerProcessor::ResolveEventController()->UnsubscribeFromKeyboard(actor);
            EventControllerProcessor::ResolveEventController()->UnsubscribeFromMouse(actor);
            actors_.erase(pos);
        }

        void ActorSystem::RemoveDestroyedActors() noexcept
        {

            std::queue<Actor *> removed{};

            for (size_t i = 0; i < actors_.size(); ++i)
            {
                if (actors_[i]->IsAvailableForDestroy())
                {
                    removed.push(actors_[i]);
                }
            }

            while (!removed.empty())
            {
                RemoveActor(removed.front());
                removed.pop();
            }
        }

        void ActorSystem::CollisionDetection() noexcept
        {
            std::sort(actors_.begin(), actors_.end(), [](Actor *lhs, Actor *rhs)
            {
                return lhs->Object().GetPos().x < rhs->Object().GetPos().x;
            });
            for (auto i = 0UL; i < actors_.size(); ++i)
            {
                for (auto j = i + 1; j < actors_.size() && actors_[i]->IsCollide(actors_[j]); ++j)
                {
                    if (i == j)
                    {
                        continue;
                    }

                    actors_[i]->OnEnter(actors_[j]);
                }
            }
        }

        void ActorSystem::OnResize(const size_t width, const size_t height) noexcept
        {
            // need for Resize storage
        }

        Actor *ActorSystem::FindById(const unsigned id) const noexcept
        {
            for (auto actor : actors_)
            {
                if (actor->Id() == id)
                {
                    return actor;
                }
            }

            return nullptr;
        }


        ActorSystem::~ActorSystem()
        {
            for (auto actor : actors_)
            {
                actor->Destroy();
            }
            RemoveDestroyedActors();
        }


    } // namespace Core
} // namespace Game
