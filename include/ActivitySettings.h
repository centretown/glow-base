// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"

template <class T>
class ActivitySettings : public Activity
{
protected:
    T &settings;

public:
    ActivitySettings(T &settings) : settings(settings) {}
    ~ActivitySettings() {}

    virtual void Tick() {}
};
