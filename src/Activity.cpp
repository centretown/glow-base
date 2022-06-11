// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Activity.h"

DefaultTrigger Trigger::defaultTrigger;
DefaultTrigger *Trigger::Default() { return &defaultTrigger; }

uint64_t Activity::now = millis();

uint64_t Activity::Now()
{
    return now;
}

void Activity::Cycle()
{
    now = millis();
}

bool Activity::Pulse()
{
    if (!trigger->Active(this) || now < next)
    {
        return false;
    }
    next = now + interval;
    Tick();
    return true;
}
