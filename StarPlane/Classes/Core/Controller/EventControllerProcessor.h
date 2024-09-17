#pragma once

#include <memory>
#include <unordered_map>

namespace Game
{

    namespace Core
    {
        inline namespace Keyboard
        {
            class IKeyboardProcessor;
            class IKeyboardHandler;
            enum class Key;
            enum class Action;
        }

        inline namespace Mouse
        {
            class IMouseProcessor;
            class IMouseHandler;
            enum class Key;
            enum class Action;
        }

        enum class BaseEventClassType : uint8_t
        {
            Keyboard,
            Mouse,
            NonDevice
        };

        class EventControllerProcessor
        {
        public:
            friend class Application;

            using IKeyboardProcessorPtrType = std::shared_ptr<IKeyboardProcessor>;
            using IMouseProcessorPtrType = std::shared_ptr<IMouseProcessor>;

            EventControllerProcessor();
            virtual ~EventControllerProcessor() = default;

            EventControllerProcessor(const EventControllerProcessor &);
            EventControllerProcessor &operator=(const EventControllerProcessor &);

            EventControllerProcessor(EventControllerProcessor &&) noexcept;
            EventControllerProcessor &operator=(EventControllerProcessor &&) noexcept;

            void SubscribeOnKeyboard(IKeyboardHandler *) const;
            void SubscribeOnMouse(IMouseHandler *) const;

            void UnsubscribeFromKeyboard(IKeyboardHandler *) const;
            void UnsubscribeFromMouse(IMouseHandler *) const;

            void PushEvent(int, int, int) const;

            const IKeyboardProcessorPtrType &Keyboard() const noexcept;
            const IMouseProcessorPtrType &Mouse() const noexcept;

            static EventControllerProcessor *ResolveEventController() noexcept;

            static Keyboard::Key KeyAsKeyboard(int, int) noexcept;
            static Keyboard::Action ActionAsKeyboard(int) noexcept;

            static Mouse::Key KeyAsMouse(int, int) noexcept;
            static Mouse::Action ActionAsMouse(int) noexcept;

        private:
            static void Release() noexcept;
            static void Init() noexcept;
            std::unordered_map<int, BaseEventClassType> events_;
            IKeyboardProcessorPtrType keyboard_;
            IMouseProcessorPtrType mouse_;

        };

    } // namespace Cor

} // namespace Game
