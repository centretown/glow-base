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
                uint8_t mode;
                uint8_t id;
                uint16_t position;
            };
        };

    public:
        State(uint32_t pack = 0) : pack(pack) {}

        State(uint8_t mode, uint8_t id, uint16_t position)
            : mode(mode), id(id), position(position) {}

        inline void operator()(uint32_t p)
        {
            pack = p;
        }

        inline void operator()(uint8_t m, uint8_t s, uint16_t p)
        {
            mode = m;
            id = s;
            position = p;
        }

        inline bool operator!=(State &s) const
        {
            return (pack != s.pack);
        }
        inline bool operator!=(uint32_t v) const
        {
            return (pack != v);
        }

        inline bool operator==(State &s) const
        {
            return (pack == s.pack);
        }
        inline bool operator==(uint32_t v) const
        {
            return (pack == v);
        }

        inline State &operator=(State &s)
        {
            pack = s.pack;
            return *this;
        }
        inline State &operator=(uint32_t v)
        {
            pack = v;
            return *this;
        }
    };

} // namespace glow
