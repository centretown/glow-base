// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "CompoundActivity.h"

CompoundActivity::CompoundActivity(size_t length) : length(length)
{
    activities = (Activity **)malloc(length * sizeof(Activity *));
}

CompoundActivity::~CompoundActivity()
{
    free(activities);
}

void CompoundActivity::Add(Activity *activity)
{
    if (count < length)
    {
        activities[count] = activity;
        count++;
    }
}

void CompoundActivity::Setup()
{
    for (size_t i = 0; i < count; i++)
    {
        activities[i]->Setup();
    }
}

void CompoundActivity::Reset()
{
    for (size_t i = 0; i < count; i++)
    {
        activities[i]->Reset();
    }
}
