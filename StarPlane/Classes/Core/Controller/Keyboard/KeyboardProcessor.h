#pragma once

#include <Core/Controller/Keyboard/IKeyboardProcessor.h>

#include <bitset>
#include <queue>
#include <list>

namespace Game
{

    namespace Core
    {
        inline namespace Keyboard
        {
            class KeyboardProcessor final : public IKeyboardProcessor
            {
            public:
                KeyboardProcessor();
                ~KeyboardProcessor() override;

                bool IsPressed(char) const noexcept override;
                bool IsReleased(char) const noexcept override;
                bool IsRepeat(char) const noexcept override;

                bool IsPressed(Key) const noexcept override;
                bool IsReleased(Key) const noexcept override;
                bool IsRepeat(Key) const noexcept override;

                void PushEvent(Key, Action) noexcept override;

                Key GetKey() const noexcept override;
                Action GetAction() const noexcept override;

                void Subscribe(IKeyboardHandler *) override;
                void Unsubscribe(IKeyboardHandler *) override;


                void Post(const std::function<void(IKeyboardHandler *)> &) override;

                static Key TryConvert(char) noexcept;

            private:
                void Trim() noexcept;

                static constexpr int kBitsCount = 256;
                static constexpr int onTrimBufferSize = 16;
                std::bitset<kBitsCount> keys_;
                std::queue<std::pair<Key, Action>> touches_;
                Key repeated_;
                std::list<IKeyboardHandler *> handlers_;
            };
        } // namespace Keyboard
    } // namespace Core
} // namespace Game
