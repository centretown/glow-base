// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"

namespace glow
{
    class SimpleRange : public Range
    {
    private:
        uint16_t begin;
        uint16_t end;

    public:
        SimpleRange(uint16_t begin = 0, uint16_t end = 0)
            : begin(begin), end(end)
        {
            if (end < begin)
            {
                auto e = end;
                end = begin;
                begin = e;
            }
        }
        SimpleRange(Range *range) : begin(range->Begin()), end(range->End()) {}

        void Copy(Range *range)
        {
            begin = range->Begin();
            end = range->End();
        }

        inline void Begin(uint16_t v) { begin = v; }
        inline void End(uint16_t v) { end = v; }

        virtual uint16_t Begin() { return begin; };
        virtual uint16_t End() { return end; }
    };
}