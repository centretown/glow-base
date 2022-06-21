// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
namespace glow
{
    class Monitor
    {
    public:
        virtual void Setup() = 0;
        virtual bool Ready() = 0;
        virtual bool Done() = 0;
    };
}
