// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"
#include "State.h"

namespace glow
{
    class Source
    {
    private:
        Range range;
        State state;

    public:
        virtual uint32_t Update() = 0;

        void UpdateState(uint32_t v)
        {
            state = v;
        }
        
        void UpdateRange(uint32_t v)
        {
            range = v;
        }
    };
}
