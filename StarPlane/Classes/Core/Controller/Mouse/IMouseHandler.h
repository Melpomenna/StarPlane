#pragma once


namespace Game
{
    namespace Core
    {
        inline namespace Mouse
        {
            enum class Key;

            class IMouseHandler
            {
            public:
                IMouseHandler() = default;
                virtual ~IMouseHandler() = default;

                virtual void OnPress(Key)
                {
                }

                virtual void OnRelease(Key)
                {
                }

                virtual void OnRepeat(Key)
                {
                }

                /**
                 * @brief  Find bindings mouse for object
                 * @param param  - contains bits of actions (seem enum class Mouse::Action)
                 * @return find bindings for object
                 * @retval true - if contains bindings
                 * @retval false - if cannot find bindings
                 * @details default return true
                 */
                virtual bool FindBindings(Key, const int param)
                {
                    (void)param;
                    return true;
                }

                virtual void SetBindings(Key, int)
                {

                }
            };
        } // namespace Keyboard
    } // namespace Core
} // namespace Game
