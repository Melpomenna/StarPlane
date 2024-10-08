#include "Actor.h"

#include <Core/Actor/ActorSystem.h>
#include <GUI/Render.h>

#include "GUI/Texture.h"

namespace Game
{
    namespace Core
    {
        Actor::Actor() :
            object_(nullptr)
        {
            DisableCollision();
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
            isAvailableForDestroy_ = false;
            ActorSystem::ResolveActorSystem()->RegisterActor(this);
        }


        void Actor::OnDestroyActor()
        {
            if (object_.object_)
            {
                object_.object_->Destroy();
            }
            isAvailableForDestroy_ = true;
        }

        bool Actor::IsCollide(Actor *other) const noexcept
        {
            if (!IsCollisionEnabled() || IsAvailableForDestroy() || other->IsAvailableForDestroy() ||
                !other->
                IsCollisionEnabled())
            {
                return false;
            }

            auto pos = object_.GetPos();
            auto rect = object_.Size();

            auto otherPos = other->Object().GetPos();
            auto otherRect = other->Object().Size();

            return !(pos.x + rect.width < otherPos.x || pos.x > otherPos.x + otherRect.width ||
                pos.y + rect.height < otherPos.y || pos.y > otherPos.y + otherRect.height);
        }


        bool Actor::IsAvailableForDestroy() const noexcept
        {
            return isAvailableForDestroy_;
        }

        unsigned Actor::Id() const noexcept
        {
            return id_;
        }

        void Actor::SetId(const unsigned id) noexcept
        {
            id_ = id;
        }


        Actor::ObjectWrapper Actor::Object() const noexcept
        {
            return object_;
        }

        void Actor::SetObject(GUI::Node *object) noexcept
        {
            if (!object)
            {
                return;
            }

            object_.object_ = object;
        }

        void Actor::EnableCollision()
        {
            isCollisionEnabled_ = true;
        }


        void Actor::DisableCollision()
        {
            isCollisionEnabled_ = false;
        }

        bool Actor::IsCollisionEnabled() const noexcept
        {
            return isCollisionEnabled_;
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

        void Actor::ObjectWrapper::Resize(GUI::Size2D size) noexcept
        {
            if (object_)
            {
                object_->Resize(size);
            }
        }

        void Actor::ObjectWrapper::FillColor(const float r, const float g, const float b, const float a)
        {
            if (object_)
            {
                object_->FillColor(r, g, b, a);
            }
        }

        void Actor::ObjectWrapper::Rotate(const double angle) noexcept
        {
            if (object_)
            {
                object_->Rotate(angle);
            }
        }

        double Actor::ObjectWrapper::Angle() const noexcept
        {
            return object_->GetTexture()->Angle();
        }

        Actor::ObjectWrapper::operator bool() const noexcept
        {
            return object_;
        }


    }
}
