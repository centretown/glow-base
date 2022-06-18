// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
class ActivityMonitor
{
public:
    // ready to update?
    virtual bool Ready(Activity *activity) = 0;
    // check after update
    virtual bool Done(Activity *activity) = 0;
    // reset the monitor (optional)
    virtual void Reset() {}
};
