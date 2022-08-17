// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"

namespace glow
{
    class State
    {
    public:
        union
        {
            uint32_t pack;
            struct
            {
                int16_t position;
                int16_t status;
            };
        };

    public:
        State(uint16_t s = 0, int16_t p = 0)
        {

            status = s;
            position = p;
        }

        inline void operator()(uint32_t p)
        {
            pack = p;
        }

        inline void operator()(uint16_t s, uint16_t p)
        {
            status = s;
            position = p;
        }

        inline bool operator!=(State &s) const
        {
            return (s.pack != pack);
        }
        inline bool operator==(State &s) const
        {
            return (s.pack == pack);
        }
        inline State &operator=(State &s)
        {
            pack = s.pack;
            return *this;
        }

        inline int16_t Status() const { return status; }
        inline int16_t Status(int16_t v) { return status = v; }
        inline int16_t Position() const { return position; }
        inline int16_t Position(int16_t v) { return position = v; }
        inline uint32_t Pack() const { return pack; }
        inline uint32_t Pack(uint32_t v) { return pack = v; }
    };

} // namespace glow
