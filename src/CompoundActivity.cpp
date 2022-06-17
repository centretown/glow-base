// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "CompoundActivity.h"

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

void CompoundActivity::Setup()
{
    for (size_t i = 0; i < length; i++)
    {
        activities[i]->Setup();
    }
}

void CompoundActivity::Reset()
{
    for (size_t i = 0; i < length; i++)
    {
        activities[i]->Reset();
    }
}
