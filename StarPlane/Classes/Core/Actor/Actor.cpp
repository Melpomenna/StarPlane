#include "Actor.h"

#include <Core/Actor/ActorSystem.h>

namespace Game
{
    namespace Core
    {
        Actor::Actor() :
            object_(nullptr)
        {
            OnInitActor();
        }

        void Actor::Destroy()
        {
            OnDestroyActor();
        }

        Actor::~Actor()
        {
            if (object_)
            {
                object_->Destroy();
            }
            OnDestroyActor();
        }


        void Actor::OnInitActor()
        {
            ActorSystem::ResolveActorSystem()->RegisterActor(this);
        }


        void Actor::OnDestroyActor()
        {
            ActorSystem::ResolveActorSystem()->RemoveActor(this);
        }


        GUI::Node *Actor::Object() const noexcept
        {
            return object_;
        }

        void Actor::SetObject(GUI::Node *object) noexcept
        {
            if (!object)
            {
                return;
            }

            object_ = object;
        }

    }
}
