// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "State.h"

namespace glow
{
    class StateHandler
    {
    private:
        State state;

    public:
        template <typename SOURCE, typename TARGET>
        uint32_t Handle(SOURCE &source, TARGET &target)
        {
            uint32_t current = source.Update();
            if (state.pack != current)
            {
                state(current);
                target.Update(state.Status(), state.Position());
            }
            return current;
        }
    };

} // namespace glow
