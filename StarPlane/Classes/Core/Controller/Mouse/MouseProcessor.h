#pragma once

#include <Core/Controller/Mouse/IMouseProcessor.h>

#include <list>
#include <queue>

namespace Game
{
    namespace Core
    {
        inline namespace Mouse
        {

            class MouseProcessor final : public IMouseProcessor
            {
            public:
                MouseProcessor();
                ~MouseProcessor() override;

                bool IsPressed(Key) const noexcept override;
                bool IsReleased(Key) const noexcept override;
                bool IsRepeat(Key) const noexcept override;

                void PushEvent(Key, Action) noexcept override;

                Key GetKey() const noexcept override;
                Action GetAction() const noexcept override;

                void Subscribe(IMouseHandler *) override;

                void Unsubscribe(IMouseHandler *) override;


                void Post(const std::function<void(IMouseHandler *)> &) override;

            private:
                void Trim() noexcept;

                static constexpr int onTrimBufferSize = 16;
                Key current_;
                Action currentAction_;
                std::queue<std::pair<Key, Action>> touches_;
                std::list<IMouseHandler *> handlers_;

            };
        } // namespace Mouse

    } // namespace Core

} // namespace Gamee
