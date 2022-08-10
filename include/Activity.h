// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"

namespace glow
{
    template <typename UPDATER>
    class Activity : public Monitor
    {
    protected:
        UPDATER &updater;

    public:
        Activity(UPDATER &updater) : updater(updater) {}

        inline bool Pulse()
        {
            if (Ready())
            {
                PulseWidth(updater.Update());
                return true;
            }
            return false;
        }
    };
}
