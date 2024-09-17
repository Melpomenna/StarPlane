#pragma once

#include <functional>


namespace Game
{
    namespace Core
    {
        inline namespace Keyboard
        {
            enum class Key;
            enum class Action;

            class IKeyboardHandler;

            class IKeyboardProcessorDispatcher
            {
            public:
                IKeyboardProcessorDispatcher() = default;
                virtual ~IKeyboardProcessorDispatcher() = default;

                virtual void Subscribe(IKeyboardHandler *)
                {
                }

                virtual void Unsubscribe(IKeyboardHandler *)
                {
                }


                virtual void Post(const std::function<void(IKeyboardHandler *)> &)
                {

                }

            };

            class IKeyboardProcessor : public IKeyboardProcessorDispatcher
            {
            public:
                IKeyboardProcessor() = default;

                ~IKeyboardProcessor() override = default;

                virtual bool IsPressed(char) const noexcept = 0;
                virtual bool IsReleased(char) const noexcept = 0;
                virtual bool IsRepeat(char) const noexcept = 0;

                virtual bool IsPressed(Key) const noexcept = 0;
                virtual bool IsReleased(Key) const noexcept = 0;
                virtual bool IsRepeat(Key) const noexcept = 0;

                virtual void PushEvent(Key, Action) noexcept = 0;

                virtual Key GetKey() const noexcept = 0;
                virtual Action GetAction() const noexcept = 0;


            };
        }
    }
}
