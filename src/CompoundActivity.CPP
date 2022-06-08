// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "CompoundActivity.h"

CompoundActivity<class T>::CompoundActivity(
    size_t length, T &settings) : length(length), SettingsActivity<T>(settings)
{
    activities = (Activity **)malloc(length * sizeof(Activity *));
}

CompoundActivity<class T>::~CompoundActivity()
{
    free(activities);
}

void CompoundActivity<class T>::Add(Activity *activity)
{
    if (count < length)
    {
        activities[count] = activity;
        count++;
    }
}

bool CompoundActivity<class T>::Pulse(uint64_t &now)
{
    bool ticked = false;
    for (size_t i = 0; i < count; i++)
    {
        if (activities[i]->Pulse(now))
        {
            ticked = true;
        }
    }
    return ticked;
}
