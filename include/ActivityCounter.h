// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
#include "ActivityMonitor.h"

class ActivityCounter : public ActivityMonitor
{
private:
    ActivityMonitor *monitor;
    uint32_t maximum = 1;
    uint32_t count = 0;

public:
    ActivityCounter(ActivityMonitor *monitor, uint32_t maximum)
        : monitor(monitor), maximum(maximum) {}
    ~ActivityCounter() {}

    virtual bool Ready(Activity *activity)
    {
        bool ready = monitor->Ready(activity);
        if (ready)
        {
            count++;
        }
        return ready;
    }

    virtual bool Done(Activity *activity)
    {
        bool done = (count >= maximum);
        if (!done)
        {
            done = monitor->Done(activity);
        }
        return done;
    }

    virtual void Reset()
    {
        count = 0;
    }
};