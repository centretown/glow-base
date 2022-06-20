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
            : monitor(monitor), duration(duration) {}
        ~ActivityTimer() {}

        inline uint32_t Duration() { return duration; }
        inline void Duration(uint32_t v)
        {
            duration = v;
        }

        inline uint64_t End() { return end; }

        virtual void Setup(Activity *activity)
        {
            end = 0;
            monitor->Setup(activity);
        }

        virtual bool Ready(Activity *activity)
        {
            return monitor->Ready(activity);
        }

        virtual bool Done(Activity *activity)
        {
            if (end == 0)
            {
                end = Activity::Now() + duration;
            }
            bool done = (Activity::Now() >= end);
            if (!done)
            {
                done = monitor->Done(activity);
            }
            return done;
        }
    };
}