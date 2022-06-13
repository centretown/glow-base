// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "SerialActivity.h"

bool SerialActivity::Pulse()
{
    if (!Active())
    {
        return false;
    }

    if (current >= length)
    {
        current = 0;
    }

    auto i = current;
    current++;
    return activities[i]->Pulse();
}