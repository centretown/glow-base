// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"
#include "SelectActivity.h"

void testBlink(Activity &blink, uint16_t count = 10)
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

typedef struct
{
} Nothing;

void testSelectActivity()
{
    BlinkSettings settings;
    BlinkActivity blink(settings);
    settings.On(1000);
    settings.Off(1000);

    BlinkSettings settingsA;
    BlinkActivity blinkA(settingsA);
    settingsA.On(100);
    settingsA.Off(100);

    Nothing nothing;
    SelectActivity<Nothing> selector(2, nothing);

    selector.Add(&blink);
    TEST_ASSERT_EQUAL(1, selector.Count());
    selector.Add(&blinkA);
    TEST_ASSERT_EQUAL(2, selector.Count());

    TEST_ASSERT_EQUAL(0, selector.Selected());
    selector.Select(0);
    TEST_ASSERT_EQUAL(0, selector.Selected());
    testBlink(selector, 5);

    selector.Select(1);
    TEST_ASSERT_EQUAL(1, selector.Selected());
    testBlink(selector, 20);
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
    RUN_TEST(testSelectActivity);
}
