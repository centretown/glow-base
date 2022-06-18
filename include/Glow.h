// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"

namespace glow
{
    class Glow
    {
    private:
        uint8_t id = 20;

    public:
        Glow() {}
        ~Glow() {}

        uint8_t Id() { return id; }
        void Id(uint8_t v) { id = v; }
    };
}