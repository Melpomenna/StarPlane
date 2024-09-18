#include <Utils/Config.h>
#include "MouseProcessor.h"

#include <Core/Controller/Mouse/MouseEvents.h>
#include <Core/Controller/Mouse/IMouseHandler.h>

#include <GUI/Render.h>

namespace Game
{
    namespace Core
    {
        inline namespace Mouse
        {
            MouseProcessor::MouseProcessor() :
                current_(Key::Unknown), currentAction_(Action::Unknown), timeInDisable_(0), isMouseMove_(false)
            {
                const auto cursorPos = GUI::Render::ResolveRender()->GetCursorPosition();
                positionX_ = cursorPos.first;
                positionY_ = cursorPos.second;
            }

            MouseProcessor::~MouseProcessor()
            {
                handlers_.clear();
                currentAction_ = Action::Unknown;
                current_ = Key::Unknown;
            }

            Action MouseProcessor::GetAction() const noexcept
            {
                return currentAction_;
            }


            Key MouseProcessor::GetKey() const noexcept
            {
                return current_;
            }

            bool MouseProcessor::IsPressed(const Key key) const noexcept
            {
                return current_ == key && (currentAction_ == Action::Repeat || currentAction_ == Action::Press);
            }


            bool MouseProcessor::IsReleased(const Key key) const noexcept
            {
                return current_ != key;
            }


            bool MouseProcessor::IsRepeat(const Key key) const noexcept
            {
                return current_ == key && currentAction_ == Action::Repeat;
            }


            void MouseProcessor::Post(const std::function<void(IMouseHandler *)> &event)
            {
                for (const auto h : handlers_)
                {
                    event(h);
                }
            }

            void MouseProcessor::OnMove(const double x, const double y) noexcept
            {
                timeInDisable_ = 0;
                isMouseMove_ = true;

                const auto directionX = x > positionX_ ? MouseDirection::Left : MouseDirection::Right;
                const auto directionY = y > positionY_ ? MouseDirection::Down : MouseDirection::Up;
                positionX_ = x;
                positionY_ = y;

                Post([x, y, directionX, directionY](auto h)
                {
                    h->OnMouseMove(x, y, directionX, directionY);
                });
            }

            void MouseProcessor::OnStopMove()
            {
                isMouseMove_ = false;

                APP_LOG("OnStopMouseMove\n");

                Post([](auto h)
                {
                    h->OnMouseStopMove();
                });
            }

            void MouseProcessor::Update(const double dt)
            {
                if (!isMouseMove_)
                {
                    return;
                }

                timeInDisable_ += dt;
                if (timeInDisable_ >= maxTimeToDisable)
                {
                    OnStopMove();
                }
            }

            void MouseProcessor::PushEvent(Key key, Action action) noexcept
            {
                if (key == Key::Unknown || action == Action::Unknown)
                {
                    APP_LOG("Unknown key or command for mouse\n");
                    return;
                }

                current_ = key;
                currentAction_ = action;

                touches_.emplace(current_, currentAction_);

                switch (action)
                {
                case Action::Repeat:
                {
                    APP_LOG("On Repeat\n");
                    Post(
                        [key](auto h)
                        {
                            if (h->FindBindings(key, static_cast<int>(Action::Repeat)))
                            {
                                h->OnRepeat(key);
                            }
                        });
                }
                break;
                case Action::Press:
                {
                    APP_LOG("On Press\n");
                    Post(
                        [key](auto h)
                        {
                            if (h->FindBindings(key, static_cast<int>(Action::Press)))
                            {
                                h->OnPress(key);
                            }
                        });
                    break;
                }
                case Action::Release:
                {
                    APP_LOG("On Release\n");
                    Post(
                        [key](auto h)
                        {
                            if (h->FindBindings(key, static_cast<int>(Action::Release)))
                            {
                                h->OnRelease(key);
                            }
                        });
                }
                break;
                default:
                    break;

                }


                Trim();
            }

            void MouseProcessor::Subscribe(IMouseHandler *handler)
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


            void MouseProcessor::Trim() noexcept
            {
                while (touches_.size() > onTrimBufferSize)
                {
                    touches_.pop();
                }
            }

            void MouseProcessor::Unsubscribe(IMouseHandler *handler)
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
