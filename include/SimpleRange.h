// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"

namespace glow
{
    class SimpleRange : public Range
    {
    private:
        uint16_t begin;
        uint16_t end;

    public:
        SimpleRange(uint16_t begin = 0, uint16_t end = 0)
        {
            Resize(begin, end);
        }

        SimpleRange(Range *range)
        {
            Resize(range->Begin(), range->End());
        }

        void Copy(Range *range)
        {
            Resize(range->Begin(), range->End());
        }

        inline void Resize(uint16_t aBegin, uint16_t aEnd)
        {
            if (aEnd < aBegin)
            {
                auto tEnd = aEnd;
                aEnd = aBegin;
                aBegin = tEnd;
            }
            begin = aBegin;
            end = aEnd;
        }

        virtual const uint16_t Begin() { return begin; };
        virtual const uint16_t End() { return end; }
    };
}