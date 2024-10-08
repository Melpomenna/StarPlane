#pragma once

#include <Core/Controller/Keyboard/IKeyboardHandler.h>
#include <Core/Controller/Mouse/IMouseHandler.h>
#include <GUI/Node.h>

#define A_ACTOR                                                                                                        \
public                                                                                                                 \
    Game::Core::Actor

namespace Game
{

    namespace Core
    {
        class Actor : public IKeyboardHandler, public IMouseHandler
        {
        public:
            struct ObjectWrapper final
            {
                friend class Actor;
                ObjectWrapper() = delete;
                explicit ObjectWrapper(GUI::Node *);

                void SetTexture(const char *);
                void Move(double, double);
                void SetPosition(double, double);
                GUI::Position2D GetPos() const noexcept;
                GUI::Size2D WorldSize() const noexcept;
                GUI::Size2D Size() const noexcept;
                void Resize(GUI::Size2D) noexcept;
                void SetPositionByWindow(double, double);
                void FillColor(float, float, float, float);
                void Rotate(double) noexcept;
                double Angle() const noexcept;

                operator bool() const noexcept;

            private:
                GUI::Node *object_;
            };

            Actor();
            ~Actor() override;

            void Destroy();

            virtual void Update(double) = 0;

            void SetObject(GUI::Node *) noexcept;
            ObjectWrapper Object() const noexcept;

            bool IsAvailableForDestroy() const noexcept;
            bool IsCollide(Actor *) const noexcept;

            void SetId(unsigned) noexcept;
            unsigned Id() const noexcept;

            void EnableCollision();
            void DisableCollision();

            virtual void OnEnter(Actor *)
            {
            }

            virtual void OnExit(Actor *)
            {
            }

            bool IsCollisionEnabled() const noexcept;

        private:
            void OnInitActor();
            void OnDestroyActor();

            bool isAvailableForDestroy_;

            unsigned id_;

            bool isCollisionEnabled_;

        protected:
            ObjectWrapper object_;
        };

    } // namespace Core

    using Actor = Core::Actor;

} // namespace Game
