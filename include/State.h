// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"

namespace glow
{
    struct State
    {
        union
        {
            struct
            {
                int16_t state;
                int16_t position;
            };
            uint32_t pack;
        };

        State(uint8_t state = 0, int16_t position = 0)
            : state(state), position(position) {}

        inline void operator()(int16_t s, int16_t p)
        {
            state = s;
            position = p;
        }

        inline bool operator==(State &s) const
        {
            return (s.pack == pack);
        }

        inline bool operator!=(State &s) const
        {
            return (s.pack != pack);
        }
    };

} // namespace glow
