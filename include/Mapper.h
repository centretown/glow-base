// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"

namespace glow
{
    template <typename T>
    class Mapper
    {
    public:
        virtual T Get(uint16_t index) = 0;
    };

} // namespace glow
