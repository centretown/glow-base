// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    class UpdateSource
    {
    public:
        virtual uint32_t Update() { return 0; }
    };

    class UpdateTarget
    {
    public:
        virtual uint32_t Update(uint16_t status, uint16_t position) { return 0; }
    };

} // namespace glow
