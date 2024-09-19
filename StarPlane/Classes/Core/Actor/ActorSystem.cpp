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
            for (size_t i = 0; i < actors_.size(); ++i)
            {
                actors_[i]->Update(dt);
            }
        }

        void ActorSystem::RegisterActor(Actor *actor)
        {
            if (!actor)
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
            if (!actor || actors_.empty())
            {
                return;
            }

            const auto it = std::find(actors_.cbegin(), actors_.cend(), actor);

            if (it == actors_.cend())
            {
                return;
            }

            EventControllerProcessor::ResolveEventController()->UnsubscribeFromKeyboard(actor);
            EventControllerProcessor::ResolveEventController()->UnsubscribeFromMouse(actor);

            actors_.erase(it);
            delete actor;
        }

        void ActorSystem::RemoveDestroyedActors() noexcept
        {
            std::vector<Actor *> removed{actors_};

            for (size_t i = 0; i < removed.size(); ++i)
            {
                if (removed[i]->IsAvailableForDestoy())
                {
                    actors_.erase(std::find(actors_.cbegin(), actors_.cend(), removed[i]));
                }

            }

            for (const auto actor : removed)
            {
                if (actor->IsAvailableForDestoy())
                {
                    EventControllerProcessor::ResolveEventController()->UnsubscribeFromKeyboard(actor);
                    EventControllerProcessor::ResolveEventController()->UnsubscribeFromMouse(actor);
                    delete actor;
                }
            }
        }

        void ActorSystem::CollisionDetection() noexcept
        {

            /**
             *O(2) algorithm
             */

            /*for (const auto in : actors_)
            {
                if (!in->IsCollisionEnabled())
                {
                    continue;
                }

                for (const auto actor : actors_)
                {
                    if (in != actor && in->Object() && actor->Object() && !in->IsAvailableForDestoy() && !actor->
                        IsAvailableForDestoy() && actor->IsCollisionEnabled())
                    {
                        const auto inObject = in->Object();
                        const auto otherObject = actor->Object();

                        const auto pos = inObject.GetPos();
                        const auto size = inObject.Size();

                        const auto otherPos = otherObject.GetPos();
                        const auto otherSize = otherObject.Size();

                        const bool condition = pos.x + size.width < otherPos.x ||
                            pos.x > otherPos.x + otherSize.width || pos.y + size.height < otherPos.y ||
                            pos.y > otherPos.y + otherSize.height;

                        if (!condition)
                        {
                            in->OnEnter(actor);
                            actor->OnEnter(in);
                        }
                    }
                }
            }*/
        }


        ActorSystem::~ActorSystem()
        {
            std::queue<Actor *> removed{};
            for (auto actor : actors_)
            {
                removed.push(actor);
            }

            actors_.clear();

            while (!removed.empty())
            {
                ::delete removed.front();
                removed.pop();
            }
        }


    }
}
