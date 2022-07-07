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

        inline void Sweep(range_pack pack, T actor, bool reversed = false)
        {
            if (reversed)
            {
                reverse(pack, actor);
                return;
            }

            forward(pack, actor);
        }

    private:
        inline void reverse(range_pack pack, T actor)
        {
            Range range(pack);
            uint16_t i = range.End();
            do
            {
                i--;
                Act(i, actor);
            } while (i > range.Begin());
        }

        inline void forward(range_pack pack, T actor)
        {
            Range range(pack);
            for (uint16_t i = range.Begin(); i < range.End(); i++)
            {
                Act(i, actor);
            }
        }
    };
} // namespace glow
