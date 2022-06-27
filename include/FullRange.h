// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"

namespace glow
{
    class FullRange : public Range
    {
    private:
        uint16_t begin;
        uint16_t end;

    public:
        FullRange(uint16_t begin, uint16_t end) : begin(), end(end) {}

        void Begin(uint16_t v) { begin = v; }
        void End(uint16_t v) { end = v; }

        virtual uint16_t Begin() { return begin; };
        virtual uint16_t End() { return end; }
    };
}