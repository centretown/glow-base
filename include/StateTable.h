// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "State.h"

namespace glow
{
    struct StateItem
    {
        State state;
    };

    class StateTable
    {
    private:
        static const uint16_t width = 4;
        static const uint16_t height = 8;
        uint16_t table[width * height];

    public:
        StateTable(/* args */);
        ~StateTable();
    };

} // namespace glow
