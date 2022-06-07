// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"

BlinkSettings blinkSettings;
BlinkActivity blink(blinkSettings);

void testFeatures();
void testActivities();

void run()
{
    UNITY_BEGIN();
    testFeatures();
    testActivities();
    UNITY_END();
}

#ifdef ARDUINO

void setup()
{
    delay(2000);
    run();
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
    run();
}
#endif // ARDUINO
