// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"

template <class T>
class SimpleActivity : public Activity
{
protected:
    T &settings;

public:
    SimpleActivity(T &settings, uint16_t interval = 500)
        : settings(settings)
    {
        Interval(interval);
    }
    ~SimpleActivity() {}
};
