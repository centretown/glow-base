// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
#include "SimpleActivity.h"
#include "BlinkSettings.h"

class BlinkActivity : public SimpleActivity<BlinkSettings>
{
public:
    BlinkActivity(BlinkSettings &settings, uint16_t interval = 500)
        : SimpleActivity(settings, interval)
    {
        updateInterval();
    }

    ~BlinkActivity() {}

    virtual void Setup();
    virtual void Tick();

private:
    inline void updateInterval()
    {
        Interval((settings.State() == BLINK_ON)
                     ? settings.On()
                     : settings.Off());
    }
};
