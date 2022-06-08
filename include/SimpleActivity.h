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
    SimpleActivity(T &settings) : settings(settings) {}
    ~SimpleActivity() {}
};
