// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
#include "MonitoredActivity.h"
#include "BlinkSettings.h"
#include "BlinkMonitor.h"

namespace glow
{
    class BlinkActivity : public MonitoredActivity
    {
    private:
        BlinkSettings *blink;

    public:
        BlinkActivity(ActivityMonitor *monitor, BlinkSettings *blink)
            : MonitoredActivity(monitor), blink(blink) {}
        ~BlinkActivity() {}

        virtual void Update()
        {
            blink->ToggleState();
        }
    };
}