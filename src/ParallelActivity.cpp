// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "ParallelActivity.h"

bool ParallelActivity::Pulse()
{
    if (!Active())
    {
        return false;
    }

    bool ticked = false;
    for (size_t i = 0; i < count; i++)
    {
        bool r = activities[i]->Pulse();
        if (r && !ticked)
        {
            ticked = true;
        }
    }
    return ticked;
}
