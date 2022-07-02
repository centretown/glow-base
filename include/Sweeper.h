// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"

namespace glow
{
    template <typename T>
    class Sweeper
    {
    public:
        virtual void Act(uint16_t i, T *t) = 0;

        void Sweep(Range *range, T *actor)
        {
            if (range->Reverse())
            {
                uint16_t i = range->End();
                do
                {
                    i--;
                    Act(i, actor);
                } while (i > range->Begin());
            }
            else
            {
                for (uint16_t i = range->Begin(); i < range->End(); i++)
                {
                    Act(i, actor);
                }
            }
        }
    };
} // namespace glow
