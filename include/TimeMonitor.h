// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "ActivityMonitor.h"

const uint32_t MONITOR_DEFAULT_DURATION = 5000;

class TimeMonitor : public ActivityMonitor
{
private:
    uint64_t end = 0;
    uint64_t begin = 0;

public:
    TimeMonitor(uint64_t begin, uint64_t end);
    TimeMonitor(uint64_t end);
    TimeMonitor();

    ~TimeMonitor() {}

    inline void Begin(uint64_t v) { begin = v; }
    inline uint64_t Begin() { return begin; }
    inline void End(uint64_t v) { end = v; }
    inline uint64_t End() { return end; }
    // inline void After(uint32_t after, uint32_t duration)
    // {
    //     begin = Activity::Now() + after;
    //     end = begin + duration;
    // }
    // inline void Duration(uint32_t duration)
    // {
    //     begin = Activity::Now();
    //     end = begin + duration;
    // }

    virtual bool Active(Activity *activity);
    virtual bool Done(Activity *activity);
};
