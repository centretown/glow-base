// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Monitor.h"
#include "Activity.h"

namespace glow
{
    class CountMonitor : public Monitor
    {
    private:
        Monitor *monitor;
        const uint32_t maximum = 1;
        uint32_t count = 0;

    public:
        CountMonitor(Monitor *monitor, uint32_t maximum)
            : monitor(monitor), maximum(maximum) {}
        ~CountMonitor() {}

        inline const uint32_t Maximum() { return maximum; }
        inline const uint32_t Count() { return count; }

        virtual void Reset()
        {
            monitor->Reset();
            count = 0;
        }

        virtual bool Ready()
        {
            bool ready = monitor->Ready();
            if (ready)
            {
                count++;
            }
            return ready;
        }

        virtual bool Done()
        {
            return (count >= maximum);
        }
    };
}