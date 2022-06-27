// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    class Range
    {
    public:
        virtual uint16_t Begin() = 0;
        virtual uint16_t End() = 0;

        inline uint16_t Next(uint16_t current)
        {
            return ++current;
        }
    };
}