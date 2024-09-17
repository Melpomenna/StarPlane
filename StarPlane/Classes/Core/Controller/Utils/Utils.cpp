#include "Utils.h"

#include <Core/Controller/Keyboard/IKeyboardProcessor.h>
#include <Core/Controller/EventControllerProcessor.h>

#include <Core/Controller/Mouse/IMouseProcessor.h>
#include <Core/Controller/Mouse/MouseEvents.h>

namespace Game
{
    namespace Core
    {
        inline namespace Utils
        {
            bool IsKeyPressed(const char sym) noexcept
            {
                const EventControllerProcessor::IKeyboardProcessorPtrType kKeyboard =
                    EventControllerProcessor::ResolveEventController()->Keyboard();
                return kKeyboard->IsPressed(sym);
            }

            bool IsKeyReleased(const char sym) noexcept
            {
                const EventControllerProcessor::IKeyboardProcessorPtrType kKeyboard =
                    EventControllerProcessor::ResolveEventController()->Keyboard();
                return kKeyboard->IsReleased(sym);
            }

            bool IsKeyRepeat(const char sym) noexcept
            {
                const EventControllerProcessor::IKeyboardProcessorPtrType kKeyboard =
                    EventControllerProcessor::ResolveEventController()->Keyboard();
                return kKeyboard->IsRepeat(sym);
            }

            bool IsKeyPressed(const Keyboard::Key key) noexcept
            {
                const EventControllerProcessor::IKeyboardProcessorPtrType kKeyboard =
                    EventControllerProcessor::ResolveEventController()->Keyboard();
                return kKeyboard->IsRepeat(key);
            }

            bool IsKeyReleased(const Keyboard::Key key) noexcept
            {
                const EventControllerProcessor::IKeyboardProcessorPtrType kKeyboard =
                    EventControllerProcessor::ResolveEventController()->Keyboard();
                return kKeyboard->IsReleased(key);
            }

            bool IsKeyRepeat(const Keyboard::Key key) noexcept
            {
                const EventControllerProcessor::IKeyboardProcessorPtrType kKeyboard =
                    EventControllerProcessor::ResolveEventController()->Keyboard();
                return kKeyboard->IsRepeat(key);
            }

            bool IsLeftMouseButtonPressed() noexcept
            {
                const EventControllerProcessor::IMouseProcessorPtrType kMouse =
                    EventControllerProcessor::ResolveEventController()->Mouse();
                return kMouse->IsPressed(Mouse::Key::Left);
            }

            bool IsLeftMouseButtonReleased() noexcept
            {
                const EventControllerProcessor::IMouseProcessorPtrType kMouse =
                    EventControllerProcessor::ResolveEventController()->Mouse();
                return kMouse->IsReleased(Mouse::Key::Left);
            }

            bool IsLeftMouseButtonRepeat() noexcept
            {
                const EventControllerProcessor::IMouseProcessorPtrType kMouse =
                    EventControllerProcessor::ResolveEventController()->Mouse();
                return kMouse->IsRepeat(Mouse::Key::Left);
            }

            bool IsRightMouseButtonPressed() noexcept
            {
                const EventControllerProcessor::IMouseProcessorPtrType kMouse =
                    EventControllerProcessor::ResolveEventController()->Mouse();
                return kMouse->IsPressed(Mouse::Key::Right);
            }

            bool IsRightMouseButtonReleased() noexcept
            {
                const EventControllerProcessor::IMouseProcessorPtrType kMouse =
                    EventControllerProcessor::ResolveEventController()->Mouse();
                return kMouse->IsReleased(Mouse::Key::Right);
            }

            bool IsRightMouseButtonRepeat() noexcept
            {
                const EventControllerProcessor::IMouseProcessorPtrType kMouse =
                    EventControllerProcessor::ResolveEventController()->Mouse();
                return kMouse->IsRepeat(Mouse::Key::Right);
            }

            bool IsMouseButtonPressed(const Mouse::Key key) noexcept
            {
                const EventControllerProcessor::IMouseProcessorPtrType kMouse =
                    EventControllerProcessor::ResolveEventController()->Mouse();
                return kMouse->IsPressed(key);
            }

            bool IsMouseButtonReleased(const Mouse::Key key) noexcept
            {
                const EventControllerProcessor::IMouseProcessorPtrType kMouse =
                    EventControllerProcessor::ResolveEventController()->Mouse();
                return kMouse->IsReleased(key);
            }

            bool IsMouseButtonRepeat(const Mouse::Key key) noexcept
            {
                const EventControllerProcessor::IMouseProcessorPtrType kMouse =
                    EventControllerProcessor::ResolveEventController()->Mouse();
                return kMouse->IsRepeat(key);
            }
        }
    }
}
