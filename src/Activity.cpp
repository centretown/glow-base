// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Activity.h"

uint64_t Activity::now = millis();
uint64_t Activity::Now() { return now; }
void Activity::Cycle() { now = millis(); }

bool Activity::Pulse()
{
    if (!Ready())
    {
        return false;
    }

    Update();

    if (Done())
    {
        Reset();
    }
    return true;
}
