// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "BlinkActivity.h"

BlinkActivity ::BlinkActivity(BlinkSettings &settings) : ActivitySettings(settings)
{
    updateInterval();
}

void BlinkActivity::Setup()
{
#ifdef ARDUINO
    pinMode(settings.pin, OUTPUT);
#endif
    updateInterval();
}

void BlinkActivity::Tick()
{
#ifdef ARDUINO
    digitalWrite(settings.pin, settings.state);
#else
    const char *text = (settings.state == BLINK_ON)
                           ? "OFF"
                           : "ON";
    printf("pin:%u %s\n", settings.pin, text);
#endif
    toggleState();
    updateInterval();
}
