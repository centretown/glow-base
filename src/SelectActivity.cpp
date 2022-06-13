// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "SelectActivity.h"

bool SelectActivity::Pulse()
{
    if (!Active())
    {
        return false;
    }

    return activities[selection]->Pulse();
}