// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"
#include "BlinkSettings.h"

namespace glow
{
    class BlinkMonitor : public Monitor
    {
    private:
        BlinkSettings *blink;
        uint64_t next = 0;

    public:
        BlinkMonitor(BlinkSettings *blink) : blink(blink) {}
        ~BlinkMonitor() {}

        virtual void Reset()
        {
            next = 0;
        }

        virtual bool Ready()
        {
            auto ready = (Monitor::Now() >= next);
            if (ready)
            {
                next = Monitor::Now();
                next += (blink->State() == BLINK_ON)
                            ? blink->On()
                            : blink->Off();
            }
            return ready;
        }
        virtual bool Done() { return false; }
    };
}