// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "BlinkActivity.h"

void BlinkActivity::Setup()
{
#ifdef ARDUINO
    pinMode(settings.Pin(), OUTPUT);
#endif
    updateInterval();
}

void BlinkActivity::Tick()
{
#ifdef ARDUINO
    digitalWrite(settings.Pin(), settings.State());
#else
    const char *text = (settings.State() == BLINK_ON)
                           ? "OFF"
                           : "ON";
    printf("pin:%u %s\n", settings.Pin(), text);
#endif
    settings.ToggleState();
    updateInterval();
}
