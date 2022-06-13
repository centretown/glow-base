// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "TimeMonitor.h"

bool TimeMonitor::Active(Activity *activity)
{
    auto now = activity->Now();
    if (begin == 0)
    {
        Begin(now);
        return true;
    }
    return (now < End());
}
