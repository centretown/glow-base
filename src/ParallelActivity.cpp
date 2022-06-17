// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "ParallelActivity.h"

void ParallelActivity::Update()
{
    Activity *activity;
    for (size_t i = 0; i < Length(); i++)
    {
        activity = activities[i];
        if (activity->Ready())
        {
            activity->Update();
        }
    }
}
