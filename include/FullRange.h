// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"

namespace glow
{
    class FullRange : public Range
    {
    private:
        uint16_t length;

    public:
        FullRange(uint16_t length) : length(length) {}

        virtual uint16_t Begin() { return 0; };
        virtual uint16_t End() { return length; }
    };
}