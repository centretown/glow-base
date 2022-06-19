// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "ActivityMonitor.h"

namespace glow
{
    class IntervalMonitor
    {
    private:
    protected:
        uint32_t interval = 500;
        uint64_t next = Activity::Now();

    public:
        IntervalMonitor(uint32_t interval = 500) : interval(interval) {}
        ~IntervalMonitor() {}

        inline void Interval(uint32_t v)
        {
            interval = v;
        }
        inline uint32_t Interval()
        {
            return interval;
        }

        inline uint64_t Next()
        {
            return next;
        }

        virtual void Setup(Activity *activity) {}

        virtual bool Ready(Activity *activity)
        {
            auto ready = (Activity::Now() >= next);
            if (ready)
            {
                next += interval;
            }
            return ready;
        }
        virtual bool Done(Activity *activity) { return false; }
    };
}
