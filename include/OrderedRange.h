// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"

namespace glow
{
    class OrderedRange : public Range
    {
    private:
        uint16_t begin;
        uint16_t end;

    public:
        OrderedRange(uint16_t begin = 0, uint16_t end = 0) : begin(), end(end) {}

        inline void Begin(uint16_t v) { begin = v; }
        inline void End(uint16_t v) { end = v; }
        virtual uint16_t Next(uint16_t current)
        {
            return ++current;
        }

        virtual uint16_t Begin() { return begin; };
        virtual uint16_t End() { return end; }
    };
}