// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "State.h"

namespace glow
{
    class StateHandler
    {
    private:
        State previous;

    public:
        template <typename SOURCE, typename TARGET>
        uint32_t Handle(SOURCE &source, TARGET &target)
        {
            State current = source.Update();
            if (previous != current)
            {
                previous = current;
                target.Update(current.status, current.position);
            }
            return current.pack;
        }
    };

} // namespace glow
