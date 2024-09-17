#include <Utils/Config.h>
#include "KeyboardProcessor.h"

#include <Core/Controller/Keyboard/KeyboardEvents.h>
#include <Core/Controller/Keyboard/IKeyboardHandler.h>

namespace Game
{
    namespace Core
    {
        inline namespace Keyboard
        {

            KeyboardProcessor::KeyboardProcessor() :
                repeated_(Key::Unknown)
            {

            }

            KeyboardProcessor::~KeyboardProcessor()
            {
                repeated_ = Key::Unknown;
                keys_ = {};
                handlers_.clear();
            }


            Action KeyboardProcessor::GetAction() const noexcept
            {
                if (touches_.empty())
                {
                    return Action::Unknown;
                }
                return touches_.back().second;
            }

            Key KeyboardProcessor::GetKey() const noexcept
            {
                if (touches_.empty())
                {
                    return Key::Unknown;
                }
                return touches_.back().first;
            }

            bool KeyboardProcessor::IsPressed(Key key) const noexcept
            {
                if (key == Key::Unknown)
                {
                    return false;
                }

                return keys_[static_cast<int>(key)];
            }

            bool KeyboardProcessor::IsPressed(const char sym) const noexcept
            {
                return IsPressed(TryConvert(sym));
            }

            bool KeyboardProcessor::IsReleased(Key key) const noexcept
            {
                if (key == Key::Unknown)
                {
                    return false;
                }

                return keys_[static_cast<int>(key)] == 0;
            }


            bool KeyboardProcessor::IsReleased(const char sym) const noexcept
            {
                return IsReleased(TryConvert(sym));
            }


            bool KeyboardProcessor::IsRepeat(const Key key) const noexcept
            {
                if (key == Key::Unknown)
                {
                    return false;
                }

                return repeated_ == key;
            }

            bool KeyboardProcessor::IsRepeat(const char sym) const noexcept
            {
                return IsRepeat(TryConvert(sym));
            }

            Key KeyboardProcessor::TryConvert(char sym) noexcept
            {
                const auto upper = static_cast<int>(Key::A) <= sym && sym <= static_cast<int>(Key::Z);
                const auto lower = static_cast<int>(Key::a) <= sym && sym <= static_cast<int>(Key::z);
                const auto space = static_cast<int>(Key::Space) == sym;
                if (upper || lower || space)
                {
                    return static_cast<Key>(sym);
                }
                return Key::Unknown;
            }


            void KeyboardProcessor::Post(const std::function<void(IKeyboardHandler *)> &event)
            {
                for (auto h : handlers_)
                {
                    event(h);
                }
            }

            void KeyboardProcessor::PushEvent(Key key, Action action) noexcept
            {
                if (key == Key::Unknown || action == Action::Unknown)
                {
                    APP_LOG("Unknown key or action for keyboard\n");
                    return;
                }

                const auto bit = action == Action::Repeat || action == Action::Press ? 1 : 0;
                if (action == Action::Repeat && repeated_ != key)
                {
                    repeated_ = key;
                }

                if (action == Action::Release && repeated_ == key)
                {
                    repeated_ = Key::Unknown;
                }

                touches_.emplace(key, action);
                keys_[static_cast<int>(key)] = bit;

                if (action == Action::Repeat)
                {
                    APP_LOG("On Repeat Keyboard\n");
                    Post([key](auto h)
                    {
                        if (h->FindBindings(key, static_cast<int>(Action::Repeat)))
                        {
                            h->OnRepeat(key);
                        }
                    });
                }

                if (action == Action::Press)
                {
                    APP_LOG("On Press Keyboard\n");
                    Post([key](auto h)
                    {
                        if (h->FindBindings(key, static_cast<int>(Action::Press)))
                        {
                            h->OnPress(key);
                        }
                    });
                }

                if (action == Action::Release)
                {
                    APP_LOG("On Release Keyboard\n");
                    Post(
                        [key](auto h)
                        {
                            if (h->FindBindings(key, static_cast<int>(Action::Release)))
                            {
                                h->OnRelease(key);
                            }
                        });
                }

                Trim();
            }

            void KeyboardProcessor::Trim() noexcept
            {
                while (touches_.size() > onTrimBufferSize)
                {
                    touches_.pop();
                }
            }


            void KeyboardProcessor::Subscribe(IKeyboardHandler *handler)
            {
                if (!handler)
                {
                    return;
                }

                if (std::find(handlers_.cbegin(), handlers_.cend(), handler) != handlers_.cend())
                {
                    return;
                }

                handlers_.push_back(handler);
            }


            void KeyboardProcessor::Unsubscribe(IKeyboardHandler *handler)
            {
                if (!handler)
                {
                    return;
                }
                const auto it = std::remove(handlers_.begin(), handlers_.end(), handler);
                if (it == handlers_.cend())
                {
                    return;
                }

                handlers_.erase(it);
            }


        }
    }
}
