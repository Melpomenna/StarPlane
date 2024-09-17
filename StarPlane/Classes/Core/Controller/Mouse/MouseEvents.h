#pragma once


namespace Game
{
    namespace Core
    {
        inline namespace Mouse
        {
            /**
             * @brief Supported mouse button
             */
            enum class Key
            {
                Left,
                Right,
                Unknown
            };

            /**
             * @brief Supported Mouse Actions
             */
            enum class Action
            {
                Press,
                Release,
                Repeat,
                Unknown
            };
        }
    }
}
