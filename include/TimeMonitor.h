// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"

namespace glow
{
    class TimeMonitor : public Monitor
    {
    private:
        Monitor *monitor;
        const uint32_t duration = 0;
        uint64_t end = 0;

    public:
        TimeMonitor(Monitor *monitor, uint32_t duration)
            : monitor(monitor), duration(duration) {}
        ~TimeMonitor() {}

        inline const uint32_t Duration() { return duration; }
        inline uint64_t End() { return end; }

        virtual void Reset()
        {
            monitor->Reset();
            end = 0;
        }

        virtual bool Ready()
        {
            return monitor->Ready();
        }

        virtual bool Done()
        {
            if (end == 0)
            {
                end = Monitor::Now() + duration;
            }
            return (Monitor::Now() >= end);
        }
    };
}