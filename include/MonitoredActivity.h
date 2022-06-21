// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Monitor.h"
#include "Activity.h"

namespace glow
{
    class MonitoredActivity : public Activity
    {
    protected:
        Monitor *monitor;

    public:
        MonitoredActivity(Monitor *monitor) : monitor(monitor) {}
        ~MonitoredActivity() {}
        virtual void Reset() { monitor->Reset(); }
        virtual bool Ready() { return monitor->Ready(); }
        virtual bool Done() { return monitor->Done(); }
    };
}
