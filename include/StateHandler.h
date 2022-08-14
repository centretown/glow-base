// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"
#include "State.h"

namespace glow
{
    class StateHandler
    {
    private:
        uint32_t previous;

    public:
        template <typename SOURCE, typename TARGET>
        uint32_t Handle(SOURCE &source, TARGET &target)
        {
            uint32_t current = source.Update();
            if (previous != current)
            {
                previous = current;
                target.Update(current);
            }
            return current;
        }
    };

} // namespace glow
