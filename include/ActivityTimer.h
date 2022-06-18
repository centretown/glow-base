// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
#include "ActivityMonitor.h"
namespace glow
{

    class ActivityTimer : public ActivityMonitor
    {
    private:
        ActivityMonitor *monitor;
        uint32_t duration = 0;
        uint64_t end = 0;

    public:
        ActivityTimer(ActivityMonitor *monitor, uint32_t duration)
            : monitor(monitor)
        {
            Duration(duration);
        }
        ~ActivityTimer() {}

        inline ActivityMonitor *Monitor() { return monitor; }
        inline void Monitor(ActivityMonitor *v)
        {
            monitor = v;
            Duration(duration);
        }
        inline uint32_t Duration() { return duration; }
        inline void Duration(uint32_t v)
        {
            duration = v;
            end = Activity::Now() + duration;
        }

        inline uint64_t End() { return end; }

        virtual bool Ready(Activity *activity)
        {
            return monitor->Ready(activity);
        }

        virtual bool Done(Activity *activity)
        {
            bool done = (Activity::Now() >= end);
            if (!done)
            {
                done = monitor->Done(activity);
            }
            return done;
        }

        virtual void Reset()
        {
            Duration(duration);
        }
    };
}