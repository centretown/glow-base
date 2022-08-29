// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    const uint8_t stackDepth = 8;

    template <class T>
    class Stack
    {
    private:
        T stack[stackDepth];
        uint8_t stackPtr = 0;

    public:
        uint8_t StackPtr() { return stackPtr; }

        void Push(T m)
        {
            if (stackPtr >= stackDepth - 1)
            {
                return;
            }
            stack[stackPtr] = m;
            stackPtr++;
        }

        T Pop()
        {
            if (stackPtr > 0)
            {
                --stackPtr;
            }
            return stack[stackPtr];
        }

        T Current()
        {
            uint8_t i = (stackPtr > 0) ? stackPtr - 1 : 0;
            return stack[i];
        }

        T Root()
        {
            return stack[0];
        }
    };
} // namespace glow
