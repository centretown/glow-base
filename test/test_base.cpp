// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "PinDevice.h"
#include "BlinkActivity.h"

using namespace glow;

PinDevice blinkPin;
BlinkSettings blink(&blinkPin);
BlinkMonitor monitor(&blink);
BlinkActivity blinker(&monitor, &blink);

void testFeatures();
void testBlinkActivities();
void testSort();
void testFilters();
void testSimpleSweepers();

void run()
{
    UNITY_BEGIN();
    testSimpleSweepers();
    testFeatures();
    testFilters();
    testSort();
    testBlinkActivities();
    UNITY_END();
}

#ifdef ARDUINO

void setup()
{
    delay(2000);
    run();
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
    run();
}
#endif // ARDUINO
