// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"

namespace glow
{
    template <typename T>
    class Sweeper
    {
    public:
        virtual void Act(uint16_t i, T t) = 0;

        void Sweep(Range *range, T actor)
        {
            if (range->Reverse())
            {
                reverse(range, actor);
                return;
            }
            
            forward(range, actor);
        }

    private:
        inline void reverse(Range *range, T actor)
        {
            uint16_t i = range->End();
            do
            {
                i--;
                Act(i, actor);
            } while (i > range->Begin());
        }

        inline void forward(Range *range, T actor)
        {
            for (uint16_t i = range->Begin(); i < range->End(); i++)
            {
                Act(i, actor);
            }
        }
    };
} // namespace glow
