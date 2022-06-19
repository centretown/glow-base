// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "CompoundActivity.h"

namespace glow
{
    CompoundActivity::CompoundActivity(size_t maximum) : maximum(maximum)
    {
        activities = (Activity **)malloc(maximum * sizeof(Activity *));
    }

    CompoundActivity::~CompoundActivity()
    {
        free(activities);
    }

    void CompoundActivity::Add(Activity *activity)
    {
        if (length < maximum)
        {
            activities[length] = activity;
            length++;
        }
    }
}