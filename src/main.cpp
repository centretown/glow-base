// Copyright (c) 2022 Dave Marsh. See LICENSE.
#ifndef PIO_UNIT_TESTING
#include "base.h"
#include "BlinkActivity.h"

BlinkSettings blinkSettings;
BlinkActivity blink(blinkSettings);

#ifdef ARDUINO
void setup()
{
    blink.Setup();
}

uint64_t now;
void loop()
{
    now = millis();
    blink.Pulse(now);
}
#else
int main(int argc, char **argv)
{
    blink.Setup();
    for (auto i = 0; i < 1000; i++)
    {
        auto now = millis();
        blink.Pulse(now);
    }
}
#endif
#endif