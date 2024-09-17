#pragma once

#include <functional>

namespace Game
{
    namespace Core
    {
        inline namespace Mouse
        {
            enum class Key;
            enum class Action;

            class IMouseHandler;

            class IMouseProcessorDispatcher
            {
            public:
                IMouseProcessorDispatcher() = default;
                virtual ~IMouseProcessorDispatcher() = default;

                virtual void Subscribe(IMouseHandler *)
                {
                }

                virtual void Unsubscribe(IMouseHandler *)
                {
                }


                virtual void Post(const std::function<void(IMouseHandler *)> &)
                {
                }

            };

            class IMouseProcessor : public IMouseProcessorDispatcher
            {
            public:
                IMouseProcessor() = default;

                ~IMouseProcessor() override = default;

                virtual bool IsPressed(Key) const noexcept = 0;
                virtual bool IsReleased(Key) const noexcept = 0;
                virtual bool IsRepeat(Key) const noexcept = 0;

                virtual void PushEvent(Key, Action) noexcept = 0;

                virtual Key GetKey() const noexcept = 0;
                virtual Action GetAction() const noexcept = 0;
            };
        } // namespace Keyboard
    } // namespace Core
} // namespace Game
