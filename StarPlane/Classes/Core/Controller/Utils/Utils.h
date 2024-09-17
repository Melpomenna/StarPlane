#pragma once
#include "Core/Controller/Keyboard/KeyboardEvents.h"
#include "Core/Controller/Mouse/MouseEvents.h"

namespace Game
{
    namespace Core
    {

        inline namespace Keyboard
        {
            enum class Key;
        }

        inline namespace Mouse
        {
            enum class Key;
        }

        inline namespace Utils
        {
            bool IsKeyPressed(char) noexcept;
            bool IsKeyReleased(char) noexcept;
            bool IsKeyRepeat(char) noexcept;

            bool IsKeyPressed(Keyboard::Key) noexcept;
            bool IsKeyReleased(Keyboard::Key) noexcept;
            bool IsKeyRepeat(Keyboard::Key) noexcept;

            bool IsLeftMouseButtonPressed() noexcept;
            bool IsLeftMouseButtonReleased() noexcept;
            bool IsLeftMouseButtonRepeat() noexcept;

            bool IsRightMouseButtonPressed() noexcept;
            bool IsRightMouseButtonReleased() noexcept;
            bool IsRightMouseButtonRepeat() noexcept;

            bool IsMouseButtonPressed(Mouse::Key) noexcept;
            bool IsMouseButtonReleased(Mouse::Key) noexcept;
            bool IsMouseButtonRepeat(Mouse::Key) noexcept;
        }
    }
}
