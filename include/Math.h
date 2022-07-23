// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Point.h"

namespace glow
{
    inline Point divMod(uint16_t index, uint16_t length)
    {
        return Point(index / length, index % length);
    }

    // Barrett Reduction
    inline Point divMul(uint16_t index, uint16_t length)
    {
        uint16_t x = index / length;
        return Point(x, index - x * length);
    }

#if defined(NATIVE)
    inline Point divFunc(uint16_t index, uint16_t length)
    {
        return Point(div(index, length));
    }
#else
    inline Point divFunc(uint16_t index, uint16_t length)
    {
        return divMod(index, length);
    }
#endif

    inline Point DivMod(uint16_t index, uint16_t length)
    {
#if defined(NATIVE)
        return Point(div(index, length));

#elif defined(ESP32) || defined(ESP32CAM) || defined(SEEED_XIAO)
        uint16_t x = index / length;
        return Point(x, index - x * length);

#else // MEGAATMEGA2560 et al
        return Point(index / length, index % length);
#endif
    }
} // namespace glow
