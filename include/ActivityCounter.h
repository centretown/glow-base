// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Monitor.h"
#include "Activity.h"

namespace glow
{
    class ActivityCounter : public Monitor
    {
    private:
        Monitor *monitor;
        uint32_t maximum = 1;
        uint32_t count = 0;

    public:
        ActivityCounter(Monitor *monitor, uint32_t maximum)
            : monitor(monitor), maximum(maximum) {}
        ~ActivityCounter() {}

        inline uint32_t Maximum() { return maximum; }
        void Maximum(uint32_t v) { maximum = v; }
        inline uint32_t Count() { return count; }

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