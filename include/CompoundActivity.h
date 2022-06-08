// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "Activity.h"

class CompoundActivity : public Activity
{
protected:
    size_t length = 0;
    size_t count = 0;
    Activity **activities = NULL;

public:
    CompoundActivity(size_t length) : length(length)
    {
        activities = (Activity **)malloc(length * sizeof(Activity *));
    }

    ~CompoundActivity()
    {
        free(activities);
    }

    inline size_t Length()
    {
        return length;
    }
    inline size_t Count()
    {
        return count;
    }

    void Add(Activity *activity)
    {
        if (count < length)
        {
            activities[count] = activity;
            count++;
        }
    }

    virtual void Setup()
    {
        for (size_t i = 0; i < count; i++)
        {
            activities[i]->Setup();
        }
    }

    virtual void Reset()
    {
        for (size_t i = 0; i < count; i++)
        {
            activities[i]->Reset();
        }
    }

    virtual bool Pulse(uint64_t &now)
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

    virtual void Tick() {}
};
