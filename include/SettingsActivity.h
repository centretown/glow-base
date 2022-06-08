// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"

template <class T>
class SettingsActivity : public Activity
{
protected:
    T &settings;

public:
    SettingsActivity(T &settings) : settings(settings) {}
    ~SettingsActivity() {}

    virtual void Tick() {}
};
