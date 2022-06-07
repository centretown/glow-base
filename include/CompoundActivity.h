// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "Activity.h"

class CompoundActivity : public Activity
{
private:
    size_t length = 0;
    size_t count = 0;
    Activity **activities = NULL;

public:
    CompoundActivity(size_t length);
    ~CompoundActivity();
    void Add(Activity *Activity);

    virtual bool Pulse(uint64_t &now);
    virtual void Tick() {}
};
