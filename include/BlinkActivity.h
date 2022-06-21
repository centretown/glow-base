// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

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
        BlinkActivity(Monitor *monitor, BlinkSettings *blink)
            : MonitoredActivity(monitor), blink(blink) {}
        ~BlinkActivity() {}

        virtual void Update()
        {
            blink->ToggleState();
        }
    };
}