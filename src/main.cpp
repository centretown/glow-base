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

void loop()
{
    blink.Pulse();
}
#else
int main(int argc, char **argv)
{
    blink.Setup();
    for (auto i = 0; i < 1000; i++)
    {
        blink.Pulse();
    }
}
#endif
#endif