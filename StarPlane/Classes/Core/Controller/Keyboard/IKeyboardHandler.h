#pragma once


namespace Game
{
    namespace Core
    {
        inline namespace Keyboard
        {
            enum class Key;

            class IKeyboardHandler
            {
            public:
                IKeyboardHandler() = default;
                virtual ~IKeyboardHandler() = default;

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
                 * @brief  Find bindings keyboard for object
                 * @param param  - contains bits of actions (seem enum class Keyboard::Action)
                 * @return find bindings in object
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
        }
    }
}
