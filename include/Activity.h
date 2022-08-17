// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"
#include "Updater.h"

namespace glow
{
    class Activity : public Monitor
    {
    protected:
        UpdateSource *updater;

    public:
        Activity(UpdateSource *updater) : updater(updater) {}

        inline bool Pulse()
        {
            if (Ready())
            {
                updater->Update();
                // PulseWidth();
                return true;
            }
            return false;
        }

        // inline void Apply(uint8_t state, int16_t index)
        // {
        //     updater.Apply(state, index);
        // }
    };

}
