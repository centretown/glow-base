// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"

class Activity
{
protected:
    uint16_t interval = 500;
    uint64_t next = 0;

public:
    Activity(uint16_t interval = 500);
    ~Activity() {}

    inline void SetInterval(uint16_t i)
    {
        interval = i;
    }

    inline uint16_t Interval()
    {
        return interval;
    }

    void Pulse();
    virtual void Setup() {}
    virtual void Reset() {}
    virtual void Tick() = 0;

private:
    virtual bool ready();
};
