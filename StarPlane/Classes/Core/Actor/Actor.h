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
            Actor();
            ~Actor() override;

            void Destroy();

            virtual void Update(double) = 0;

            virtual void SetObject(GUI::Node *) noexcept;
            virtual GUI::Node *Object() const noexcept;

        private:
            void OnInitActor();
            void OnDestroyActor();

        private:
            GUI::Node *object_;
        };

    } // namespace Core

    using Actor = Core::Actor;

} // namespace Game
