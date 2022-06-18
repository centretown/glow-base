// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "BlinkSettings.h"
#include "ActivityMonitor.h"

class BlinkMonitor : public ActivityMonitor
{
private:
    BlinkSettings *blink;
    uint64_t next = Activity::Now();

public:
    BlinkMonitor(BlinkSettings *blink) : blink(blink) {}
    ~BlinkMonitor() {}

    // ready to update?
    virtual bool Ready(Activity *activity)
    {
        auto ready = (Activity::Now() >= next);
        if (ready)
        {
            next += (blink->State() == BLINK_ON) ? blink->On() : blink->Off();
        }
        return ready;
    }
    // check after update
    virtual bool Done(Activity *activity) { return false; }
};
