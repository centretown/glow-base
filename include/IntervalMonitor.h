// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"

namespace glow
{
    class IntervalMonitor : public Activity
    {
    private:
    protected:
        uint32_t interval = 500;
        uint64_t next = 0;

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

        virtual void Setup()
        {
            next = 0;
        }

        virtual bool Ready()
        {
            auto ready = (Activity::Now() >= next);
            if (ready)
            {
                next = Activity::Now() + interval;
            }
            return ready;
        }
        virtual bool Done() { return false; }
    };
}
