#pragma once

namespace Game
{
    namespace Core
    {

        inline namespace Keyboard
        {
            /**
             * @brief Supported Keyboard buttons enum
             */
            enum class Key
            {
                A = 'A',
                B = 'B',
                C = 'C',
                D = 'D',
                E = 'E',
                F = 'F',
                G = 'G',
                H = 'H',
                I = 'I',
                J = 'J',
                K = 'K',
                L = 'L',
                M = 'M',
                N = 'N',
                O = 'O',
                P = 'P',
                Q = 'Q',
                R = 'R',
                S = 'S',
                T = 'T',
                U = 'U',
                V = 'V',
                W = 'W',
                Z = 'Z',
                a = 'a',
                b = 'b',
                c = 'c',
                d = 'd',
                e = 'e',
                f = 'f',
                g = 'g',
                h = 'h',
                i = 'i',
                j = 'j',
                k = 'k',
                l = 'l',
                m = 'm',
                n = 'n',
                o = 'o',
                p = 'p',
                q = 'q',
                r = 'r',
                s = 's',
                t = 't',
                u = 'u',
                v = 'v',
                w = 'w',
                z = 'z',
                Space = ' ',
                KeyUp,
                KeyDown,
                KeyLeft,
                KeyRight,
                Escape,
                Enter,
                LShift,
                RShift,
                Tab,
                Unknown
            };

            /**
             * @brief Supported Keyboard actions
             */
            enum class Action
            {
                Press,
                Release,
                Repeat,
                Unknown
            };

        } // namespace Keyboard
    } // namespace Core
} // namespace Game
