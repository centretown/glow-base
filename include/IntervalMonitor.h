// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "ActivityMonitor.h"

class IntervalMonitor
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

    // can update
    virtual bool Ready(Activity *activity)
    {
        auto ready = (Activity::Now() >= next);
        if (ready)
        {
            next += interval;
        }
        return ready;
    }
    // check after update
    virtual bool Done(Activity *activity) { return false; }
};