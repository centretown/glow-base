// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    class Range
    {
    private:
        bool reverse = false;

    public:
        inline bool Reverse() { return reverse; }
        inline void Reverse(bool v) { reverse = v; }
        virtual uint16_t Begin() = 0;
        virtual uint16_t End() = 0;
    };
}