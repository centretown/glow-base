// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    class Source
    {
    public:
        virtual uint32_t Update() = 0;
    };
}
