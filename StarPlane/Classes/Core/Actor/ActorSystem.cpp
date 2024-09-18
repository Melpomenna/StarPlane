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
            for (const auto &actor : actors_)
            {
                actor->Update(dt);
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

            const auto it = std::remove(actors_.begin(), actors_.end(), actor);

            if (it == actors_.cend())
            {
                return;
            }

            EventControllerProcessor::ResolveEventController()->UnsubscribeFromKeyboard(actor);
            EventControllerProcessor::ResolveEventController()->UnsubscribeFromMouse(actor);

            actors_.erase(it);
            delete actor;
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
