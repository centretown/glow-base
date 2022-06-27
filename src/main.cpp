// Copyright (c) 2022 Dave Marsh. See LICENSE.
#ifndef PIO_UNIT_TESTING
// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "base.h"
#include "PinDevice.h"
#include "BlinkActivity.h"

using namespace glow;

PinDevice blinkPin;
BlinkSettings blink(&blinkPin);
BlinkMonitor monitor(&blink);
BlinkActivity blinker(&monitor, &blink);

#ifdef ARDUINO

void setup()
{
    delay(2000);
    blinkPin.Setup();
    blinker.Reset();
}

void loop()
{
    Monitor::Cycle();
    blinker.Pulse();
}

#else
int main(int argc, char **argv)
{
}
#endif // ARDUINO
#endif