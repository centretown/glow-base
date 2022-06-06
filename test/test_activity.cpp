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

    for (auto i = 0; i < 1000; i++)
    {
        blink.Pulse();
    }

    blink.Reset();
}

void testActivities()
{
    RUN_TEST(testBlinkActivity);
}
