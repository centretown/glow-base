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
                int16_t status;
                int16_t position;
            };
            uint32_t pack;
        };

        State(uint8_t status = 0, int16_t position = 0)
            : status(status), position(position) {}

        inline int16_t Status() const { return status; }
        inline int16_t Status(int16_t v) { return status = v; }
        inline int16_t Position() const { return position; }
        inline int16_t Position(int16_t v) { return position = v; }
        inline uint32_t Pack() const { return pack; }
        inline uint32_t Pack(uint32_t v) { return pack = v; }

        inline void operator()(int16_t s, int16_t p)
        {
            status = s;
            position = p;
        }

        inline bool operator==(State &s) const
        {
            return (pack == s.pack);
        }

        inline uint32_t operator=(State &s)
        {
            return pack = s.pack;
        }

        inline bool operator!=(State &s) const
        {
            return (pack != s.pack);
        }
    };

} // namespace glow
