// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "BlinkUpdater.h"
#include "Activity.h"

namespace glow
{
    class BlinkActivity : public Activity<BlinkUpdater>
    {
    public:
        BlinkActivity(BlinkUpdater &blink) : Activity<BlinkUpdater>(blink) {}
    };
}