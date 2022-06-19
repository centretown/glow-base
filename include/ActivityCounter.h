// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
#include "ActivityMonitor.h"

namespace glow
{
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

        inline uint32_t Maximum() { return maximum; }
        void Maximum(uint32_t v) { maximum = v; }
        inline uint32_t Count() { return count; }

        virtual void Setup(Activity *activity)
        {
            count = 0;
        }

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
    };
}