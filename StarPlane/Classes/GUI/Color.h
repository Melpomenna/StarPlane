#pragma once

namespace Game
{
    namespace GUI
    {
        struct Color
        {
            float r;
            float g;
            float b;
            float a;
        };

        namespace internal
        {
            struct Color
            {
                Color()
                {
                    c_.r = 0;
                    c_.g = 0;
                    c_.b = 0;
                    c_.a = 0;
                }

                GUI::Color c_;
                int uniformColorLocation = -1;
            };
        }

    }
}
