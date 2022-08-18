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

    class Target
    {
    public:
        virtual uint32_t Update(uint16_t status, uint16_t position) = 0;
    };

} // namespace glow
