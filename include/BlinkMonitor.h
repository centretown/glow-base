// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "BlinkSettings.h"
#include "ActivityMonitor.h"
namespace glow
{
    class BlinkMonitor : public ActivityMonitor
    {
    private:
        BlinkSettings *blink;
        uint64_t next = 0;

    public:
        BlinkMonitor(BlinkSettings *blink) : blink(blink) {}
        ~BlinkMonitor() {}

        virtual void Setup(Activity *activity)
        {
            next = 0;
        }

        virtual bool Ready(Activity *activity)
        {
            auto ready = (Activity::Now() >= next);
            if (ready)
            {
                next = Activity::Now();
                next += (blink->State() == BLINK_ON)
                            ? blink->On()
                            : blink->Off();
            }
            return ready;
        }
        virtual bool Done(Activity *activity) { return false; }
    };
}