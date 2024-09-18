#pragma once

#include <GUI/Node.h>
#include <Core/Controller/Mouse/IMouseHandler.h>
#include <Core/Controller/Keyboard/IKeyboardHandler.h>

#define A_ACTOR public Game::Core::Actor

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
                void SetPositionByWindow(double, double);

            private:
                GUI::Node *object_;
            };

            Actor();
            ~Actor() override;

            void Destroy();

            virtual void Update(double) = 0;

            virtual void SetObject(GUI::Node *) noexcept;
            virtual GUI::Node *Object() const noexcept;

        private:
            void OnInitActor();
            void OnDestroyActor();

        protected:
            ObjectWrapper object_;
        };

    } // namespace Core

    using Actor = Core::Actor;

} // namespace Game
