// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
namespace glow
{
    class ActivityMonitor
    {
    public:
        virtual void Setup() = 0;
        virtual bool Ready() = 0;
        virtual bool Done() = 0;
    };
}
