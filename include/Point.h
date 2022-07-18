// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    struct Point
    {
        uint16_t x, y;

        inline Point() : x(0), y(0) {}

        inline Point(uint16_t x, uint16_t y) : x(x), y(y) {}

        inline Point(div_t d) : Point(d.quot, d.rem) {}
    };
} // namespace glow
