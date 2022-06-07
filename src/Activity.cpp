// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Activity.h"

Activity::Activity(uint16_t interval) : interval(interval)
{
    next = millis();
}

bool Activity::Pulse(uint64_t& now)
{
    if (now < next)
    {
        return false;
    }
    next = now + interval;
    Tick();
    return true;
}
