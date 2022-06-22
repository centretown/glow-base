// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"
namespace glow
{
    class Activity : public Monitor
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

        virtual void Update() = 0;
    };
}
