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
        Range(uint16_t begin = 0, uint16_t end = 0)
        {
            Resize(begin, end);
        }

        Range(range_pack pack)
        {
            Pack(pack);
        }

        Range(Range &range)
        {
            Pack(range.Pack());
        }

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

        void Copy(Range &range)
        {
            Pack(range.Pack());
        }

        inline void Resize(uint16_t aBegin, uint16_t aEnd)
        {
            if (aEnd < aBegin)
            {
                auto tEnd = aEnd;
                aEnd = aBegin;
                aBegin = tEnd;
            }
            limits.begin = aBegin;
            limits.end = aEnd;
        }
    };
}