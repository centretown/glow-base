// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Activity.h"

ActivityMonitor ActivityMonitor::simple;
ActivityMonitor *ActivityMonitor::Simple() { return &simple; }

uint64_t Activity::now = millis();
uint64_t Activity::Now() { return now; }

void Activity::Cycle()
{
    now = millis();
}

bool Activity::Pulse()
{
    if (!Active())
    {
        return false;
    }

    if (now < next)
    {
        return false;
    }

    next = now + interval;
 
    Tick();

    if (Dead())
    {
        Reset();
        return false;
    }
    return true;
}
