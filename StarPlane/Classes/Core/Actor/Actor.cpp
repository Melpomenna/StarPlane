#include "Actor.h"

#include <Core/Actor/ActorSystem.h>
#include <GUI/Render.h>

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
            OnDestroyActor();
        }


        void Actor::OnInitActor()
        {
            ActorSystem::ResolveActorSystem()->RegisterActor(this);
        }


        void Actor::OnDestroyActor()
        {
            if (object_.object_)
            {
                object_.object_->Destroy();
                object_.object_ = nullptr;
            }
            ActorSystem::ResolveActorSystem()->RemoveActor(this);
        }


        GUI::Node *Actor::Object() const noexcept
        {
            return object_.object_;
        }

        void Actor::SetObject(GUI::Node *object) noexcept
        {
            if (!object)
            {
                return;
            }

            object_.object_ = object;
        }

        Actor::ObjectWrapper::ObjectWrapper(GUI::Node *node) :
            object_(node)
        {

        }


        void Actor::ObjectWrapper::Move(const double dx, const double dy)
        {
            if (object_)
            {
                object_->Move(dx, dy);
            }
        }

        void Actor::ObjectWrapper::SetTexture(const char *textureName)
        {
            if (object_)
            {
                object_->LoadTexture(textureName);
            }
        }

        void Actor::ObjectWrapper::SetPosition(const double x, const double y)
        {
            if (object_)
            {
                object_->SetPos(x, y);
            }
        }

        void Actor::ObjectWrapper::SetPositionByWindow(const double percentX, const double percentY)
        {
            if (object_)
            {
                const auto render = GUI::Render::ResolveRender();
                const auto width = render->GetWidth();
                const auto height = render->GetHeight();
                object_->SetPos(width * percentX, height * percentY);
            }
        }

        GUI::Position2D Actor::ObjectWrapper::GetPos() const noexcept
        {
            if (!object_)
            {
                return {0, 0};
            }

            return object_->GetPos();
        }

        GUI::Size2D Actor::ObjectWrapper::WorldSize() const noexcept
        {
            const auto render = GUI::Render::ResolveRender();

            return {render->GetWidth(), render->GetHeight()};
        }


        GUI::Size2D Actor::ObjectWrapper::Size() const noexcept
        {
            return object_->Size();
        }


    }
}
