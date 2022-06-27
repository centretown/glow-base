// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"
#include "Updater.h"

namespace glow
{
    class Activity : public Monitor, public Updater
    {

    public:
        inline bool Pulse()
        {
            if (Ready())
            {
                Update();
                return true;
            }
            return false;
        }
    };
}
