// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Activity.h"
#include "ActivitySettings.h"
#include "BlinkSettings.h"

class BlinkActivity : public ActivitySettings<BlinkSettings>
{
public:
    BlinkActivity(BlinkSettings &settings);
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
