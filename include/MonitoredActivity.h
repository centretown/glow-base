// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
#include "ActivityMonitor.h"

namespace glow
{
    class MonitoredActivity : public Activity
    {
    protected:
        ActivityMonitor *monitor;

    public:
        MonitoredActivity(ActivityMonitor *monitor) : monitor(monitor) {}
        ~MonitoredActivity() {}
        // can update
        virtual bool Ready() { return monitor->Ready(this); }
        // check after update
        virtual bool Done() { return monitor->Done(this); }
    };
}
