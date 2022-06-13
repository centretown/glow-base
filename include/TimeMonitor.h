// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "Activity.h"

class TimeMonitor : public ActivityMonitor
{
private:
    uint64_t end = 0;
    uint64_t begin = 0;

public:
    TimeMonitor(uint64_t end = 0, uint64_t begin = 0)
        : end(end), begin(begin) {}
    ~TimeMonitor() {}

    inline void Begin(uint64_t v) { begin = v; }
    inline uint64_t Begin() { return begin; }
    inline void End(uint64_t v) { end = v; }
    inline uint64_t End() { return end; }

    virtual bool Active(Activity *activity);
    virtual bool Dead(Activity *activity) { return (activity->Now() < End()); }
};
