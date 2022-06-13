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
    CompoundActivity(size_t length);
    ~CompoundActivity();

    inline size_t Length() { return length; }
    inline size_t Count() { return count; }

    void Add(Activity *activity);
    virtual void Setup();
    virtual void Reset();
    virtual void Tick() {}
    virtual bool Pulse() = 0;
};
