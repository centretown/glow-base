// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Activity.h"

Activity::Activity(uint16_t interval) : interval(interval)
{
    next = millis();
}

void Activity::Pulse()
{
    if (ready())
    {
        Tick();
    }
}

bool Activity::ready()
{
    auto now = millis();
    if (now < next)
    {
        return false;
    }
    next = now + interval;
    return true;
}