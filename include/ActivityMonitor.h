// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
namespace glow
{
    class ActivityMonitor
    {
    public:
        virtual void Setup(Activity *activity) = 0;
        virtual bool Ready(Activity *activity) = 0;
        virtual bool Done(Activity *activity) = 0;
    };
}
