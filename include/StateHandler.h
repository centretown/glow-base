// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "State.h"
#include "Updater.h"

namespace glow
{
    class StateHandler
    {
    private:
        State state;

    public:
        uint32_t Handle(Source *source, Target *target)
        {
            uint32_t current = source->Update();
            if (state.pack != current)
            {
                state(current);
                target->Update(state.Status(), state.Position());
            }
            return current;
        }
    };

} // namespace glow
