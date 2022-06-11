// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "Activity.h"

class TimeTrigger : public Trigger
{
private:
    uint64_t end = 0;
    uint64_t begin = 0;

public:
    TimeTrigger(uint64_t end = 0, uint64_t begin = 0)
        : end(end), begin(begin) {}
    ~TimeTrigger() {}

    inline void Begin(uint64_t s) { begin = s; }
    inline uint64_t Begin() { return begin; }
    inline void End(uint64_t s) { end = s; }
    inline uint64_t End() { return end; }

    virtual bool Active(Activity* activity)
    {
        auto now = activity->Now();
        if (begin == 0)
        {
            begin = now;
            return true;
        }
        if (now < end)
        {
            return true;
        }
        return false;
    }
};
