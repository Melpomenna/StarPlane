#define USING_WINAPI
#include <Utils/Config.h>

#include "EventControllerProcessor.h"

#include <Core/Controller/Keyboard/IKeyboardProcessor.h>
#include <Core/Controller/Keyboard/KeyboardEvents.h>
#include <Core/Controller/Keyboard/KeyboardProcessor.h>

#include <Core/Controller/Mouse/IMouseProcessor.h>
#include <Core/Controller/Mouse/MouseEvents.h>
#include <Core/Controller/Mouse/MouseProcessor.h>

#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <array>

#define REGISTER_EVENT(key,type) {key,type}
#define REGISTER_MOUSE(key) REGISTER_EVENT(key, BaseEventClassType::Mouse)
#define REGISTER_KEYBOARD(key) REGISTER_EVENT(key, BaseEventClassType::Keyboard)

#define INSERT_KEYBOARD(__obj, key) __obj.insert(REGISTER_KEYBOARD(key))
#define INSERT_MOUSE(__obj, key) __obj.insert(REGISTER_MOUSE(key))

namespace Game
{
    namespace Core
    {

        namespace
        {
            EventControllerProcessor *EVENT_CONTROLLER_PROCESSOR = nullptr;
        }


        EventControllerProcessor::EventControllerProcessor()
        {
            INSERT_MOUSE(events_, GLFW_MOUSE_BUTTON_LEFT);
            INSERT_MOUSE(events_, GLFW_MOUSE_BUTTON_RIGHT);

            constexpr int end = GLFW_KEY_Z;
            for (int start = GLFW_KEY_A; start < end; ++start)
            {
                INSERT_KEYBOARD(events_, start);
            }

            keyboard_ = std::make_shared<KeyboardProcessor>();
            mouse_ = std::make_shared<MouseProcessor>();
        }

        EventControllerProcessor::EventControllerProcessor(const EventControllerProcessor &other)
        {
            mouse_ = other.mouse_;
            keyboard_ = other.keyboard_;
        }

        EventControllerProcessor &EventControllerProcessor::operator=(const EventControllerProcessor &other)
        {
            if (this == &other)
            {
                return *this;
            }

            keyboard_ = other.keyboard_;
            mouse_ = other.mouse_;

            return *this;
        }

        EventControllerProcessor::EventControllerProcessor(EventControllerProcessor &&other) noexcept
        {
            keyboard_ = std::move(other.keyboard_);
            mouse_ = std::move(other.mouse_);
        }


        EventControllerProcessor &EventControllerProcessor::operator=(EventControllerProcessor &&other) noexcept
        {
            if (this == &other)
            {
                return *this;
            }

            keyboard_ = std::move(other.keyboard_);
            mouse_ = std::move(other.mouse_);

            return *this;
        }

        void EventControllerProcessor::SubscribeOnKeyboard(IKeyboardHandler *handler) const
        {
            keyboard_->Subscribe(handler);
        }

        void EventControllerProcessor::SubscribeOnMouse(IMouseHandler *handler) const
        {
            mouse_->Subscribe(handler);
        }


        void EventControllerProcessor::UnsubscribeFromKeyboard(IKeyboardHandler *handler) const
        {
            keyboard_->Unsubscribe(handler);
        }


        void EventControllerProcessor::UnsubscribeFromMouse(IMouseHandler *handler) const
        {
            mouse_->Unsubscribe(handler);
        }

        const EventControllerProcessor::IKeyboardProcessorPtrType &EventControllerProcessor::Keyboard() const noexcept
        {
            return keyboard_;
        }

        const EventControllerProcessor::IMouseProcessorPtrType &EventControllerProcessor::Mouse() const noexcept
        {
            return mouse_;
        }

        void EventControllerProcessor::PushEvent(const int key, const int action, const int modes) const
        {
            const auto it = events_.find(key);
            if (it == events_.cend())
            {
                return;
            }

            switch (it->second)
            {
            case BaseEventClassType::Keyboard:
                keyboard_->PushEvent(KeyAsKeyboard(key, modes), ActionAsKeyboard(action));
                break;
            case BaseEventClassType::Mouse:
                mouse_->PushEvent(KeyAsMouse(key, modes), ActionAsMouse(action));
                break;
            case BaseEventClassType::NonDevice:
                APP_LOG("Non device in PushEvent\n");
                break;
            }
        }

        Keyboard::Action EventControllerProcessor::ActionAsKeyboard(const int action) noexcept
        {
            using KAction = Keyboard::Action;
            switch (action)
            {
            case GLFW_PRESS:
                return KAction::Press;
            case GLFW_RELEASE:
                return KAction::Release;
            case GLFW_REPEAT:
                return KAction::Repeat;
            default:
                return KAction::Unknown;
            }
        }

        Mouse::Action EventControllerProcessor::ActionAsMouse(const int action) noexcept
        {
            using MAction = Mouse::Action;
            switch (action)
            {
            case GLFW_PRESS:
                return MAction::Press;
            case GLFW_RELEASE:
                return MAction::Release;
            case GLFW_REPEAT:
                return MAction::Repeat;
            default:
                return MAction::Unknown;
            }
        }

        Mouse::Key EventControllerProcessor::KeyAsMouse(const int key, const int) noexcept
        {
            using MKey = Mouse::Key;
            switch (key)
            {
            case GLFW_MOUSE_BUTTON_LEFT:
                return MKey::Left;
            case GLFW_MOUSE_BUTTON_RIGHT:
                return MKey::Right;
            default:
                return MKey::Unknown;
            }
        }


        Keyboard::Key EventControllerProcessor::KeyAsKeyboard(const int key, const int modes) noexcept
        {
            using KKey = Keyboard::Key;
            int tmp = key + (modes & GLFW_MOD_SHIFT) * ('A' - 'a');
            if ((static_cast<int>(KKey::A) <= tmp && tmp <= static_cast<int>(KKey::Z)) ||
                (static_cast<int>(KKey::a) <= tmp && tmp <= static_cast<int>(KKey::z)))
            {
                return static_cast<Keyboard::Key>(tmp);
            }

            constexpr int kSize = 10;
            static_assert(kSize == (static_cast<int>(KKey::Tab) - static_cast<int>(KKey::Space) + 1),
                          "Too few arguments");

            static const std::array<std::pair<int, KKey>, kSize> data = {{
                    {GLFW_KEY_SPACE, KKey::Space},
                    {GLFW_KEY_UP, KKey::KeyUp},
                    {GLFW_KEY_DOWN, KKey::KeyDown},
                    {GLFW_KEY_LEFT, KKey::KeyLeft},
                    {GLFW_KEY_RIGHT, KKey::KeyRight},
                    {GLFW_KEY_ESCAPE, KKey::Escape},
                    {GLFW_KEY_ENTER, KKey::Enter},
                    {GLFW_KEY_LEFT_SHIFT, KKey::LShift},
                    {GLFW_KEY_RIGHT_SHIFT, KKey::RShift},
                    {GLFW_KEY_TAB, KKey::Tab},
                }
            };

            tmp = key - static_cast<int>(KKey::Space);
            const int last = static_cast<int>(data.back().second) - static_cast<int>(data.front().second);

            if (tmp < 0 || tmp > last)
            {
                return KKey::Unknown;
            }
            return data[tmp].second;
        }


        EventControllerProcessor *EventControllerProcessor::ResolveEventController() noexcept
        {
            return EVENT_CONTROLLER_PROCESSOR;
        }


        void EventControllerProcessor::Release() noexcept
        {
            ::delete EVENT_CONTROLLER_PROCESSOR;
            EVENT_CONTROLLER_PROCESSOR = nullptr;
        }


        void EventControllerProcessor::Init() noexcept
        {
            EVENT_CONTROLLER_PROCESSOR = ::new EventControllerProcessor();
        }

    }
}
