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
        virtual void Setup() { monitor->Setup(); }
        virtual bool Ready() { return monitor->Ready(); }
        virtual bool Done() { return monitor->Done(); }
    };
}
