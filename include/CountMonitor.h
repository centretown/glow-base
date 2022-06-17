// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "ActivityMonitor.h"

class CountMonitor : public ActivityMonitor
{
private:
    uint32_t extent = 1;
    uint32_t count = 0;

public:
    CountMonitor(uint32_t extent = 1) : extent(extent) {}
    ~CountMonitor() {}

    inline uint32_t Extent() { return extent; }
    inline uint32_t Count() { return count; }

    virtual bool Ready(Activity *activity)
    {
        return (count < extent);
    }

    virtual bool Done(Activity *activity)
    {
        return (count >= extent);
    }

    virtual void Reset()
    {
        count = 0;
    }
};
