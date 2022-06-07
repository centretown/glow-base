// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"

void testBlink(BlinkActivity &blink, uint16_t count = 10)
{
    uint64_t now;
    count *= 2;
    for (uint16_t tick = 0; tick < count;)
    {
        now = millis();
        if (blink.Pulse(now))
        {
            tick++;
        }
    }
}

void testBlinkActivity()
{
    BlinkSettings blinkSettings;
    BlinkActivity blink(blinkSettings);
    blink.Setup();

    testBlink(blink);

    blinkSettings.On(100);
    blinkSettings.Off(50);
    TEST_ASSERT_EQUAL(100, blinkSettings.On());
    TEST_ASSERT_EQUAL(50, blinkSettings.Off());

    testBlink(blink, 20);

    blinkSettings.On(1000);
    blinkSettings.Off(1000);
    TEST_ASSERT_EQUAL(1000, blinkSettings.On());
    TEST_ASSERT_EQUAL(1000, blinkSettings.Off());

    testBlink(blink, 5);

    blink.Reset();
}

void testActivities()
{
    RUN_TEST(testBlinkActivity);
}
