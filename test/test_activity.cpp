// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"

void testBlinkActivity()
{
    BlinkSettings blinkSettings;
    BlinkActivity blink(blinkSettings);
    blink.Setup();
    uint64_t now;

    for (auto i = 0; i < 10; i++)
    {
        now = millis();
        blink.Pulse(now);
    }

    blinkSettings.On(1000);
    blinkSettings.Off(500);
    TEST_ASSERT_EQUAL(1000, blinkSettings.On());
    TEST_ASSERT_EQUAL(500, blinkSettings.Off());

    for (auto i = 0; i < 10; i++)
    {
        now = millis();
        blink.Pulse(now);
    }

    blinkSettings.On(250);
    blinkSettings.Off(1000);
    TEST_ASSERT_EQUAL(250, blinkSettings.On());
    TEST_ASSERT_EQUAL(1000, blinkSettings.Off());

    for (auto i = 0; i < 10; i++)
    {
        now = millis();
        blink.Pulse(now);
    }

    blink.Reset();
}

void testActivities()
{
    RUN_TEST(testBlinkActivity);
}
