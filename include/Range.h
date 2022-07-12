// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    typedef uint32_t range_pack;
    typedef struct
    {
        uint16_t begin;
        uint16_t end;
    } range_limits;

    class Range
    {
    private:
        union
        {
            range_pack pack;
            range_limits limits;
        };

    public:
        Range(range_pack pack = 0)
        {
            Pack(pack);
        }

        Range(uint16_t begin, uint16_t end)
        {
            Resize(begin, end);
        }

        Range(Range &range) : Range(range.Pack()) {}

        // access
        inline uint16_t Begin() { return limits.begin; }
        inline uint16_t End() { return limits.end; }
        inline range_pack Pack() { return pack; }
        inline uint16_t Length() { return End() - Begin(); }

        // modify
        inline void Pack(range_pack v)
        {
            pack = v;
            Resize(limits.begin, limits.end);
        }

        inline void Copy(Range &range)
        {
            Pack(range.Pack());
        }

        inline void Resize(uint16_t begin, uint16_t end)
        {
            if (end < begin)
            {
                auto v = end;
                end = begin;
                begin = v;
            }
            limits.begin = begin;
            limits.end = end;
        }

        // implement
        template <typename T, typename U>
        inline void Spin(T &t, U u)
        {
            for (uint16_t i = limits.begin; i < limits.end; i++)
            {
                t.Put(i, u);
            }
        }
    };
}