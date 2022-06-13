// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"
#include "SelectActivity.h"
#include "TimeMonitor.h"

void testTrigger(Activity &activity, uint16_t count = 10)
{
    uint16_t tick = 0;
    const uint16_t max_tick = 1000;

    while (activity.Active() && tick < max_tick)
    {
        Activity::Cycle();
        if (activity.Pulse())
        {
            tick++;
        }
    }
    TEST_ASSERT(tick < max_tick);
}

void testTimeMonitor()
{
    BlinkSettings settings;
    BlinkActivity blink(settings);
    settings.On(100);
    settings.Off(100);
    uint64_t end = millis() + 5000;

    TimeMonitor timer(end);
    blink.Monitor(&timer);
    testTrigger(blink);
    auto now = millis();
    TEST_ASSERT_GREATER_OR_EQUAL(end, now);
    TEST_ASSERT_LESS_OR_EQUAL(end + 200, now);
}

void testActivity(Activity &activity, uint16_t count = 10)
{
    count *= 2;
    for (uint16_t tick = 0; tick < count;)
    {
        Activity::Cycle();
        if (activity.Pulse())
        {
            tick++;
        }
    }
}

void testSelectActivity()
{
    BlinkSettings settings;
    BlinkActivity blink(settings);
    settings.On(500);
    settings.Off(500);

    BlinkSettings settingsA;
    BlinkActivity blinkA(settingsA);
    settingsA.On(100);
    settingsA.Off(100);

    SelectActivity selector(2);

    selector.Add(&blink);
    TEST_ASSERT_EQUAL(1, selector.Count());
    selector.Add(&blinkA);
    TEST_ASSERT_EQUAL(2, selector.Count());

    TEST_ASSERT_EQUAL(0, selector.Selected());
    selector.Select(0);
    TEST_ASSERT_EQUAL(0, selector.Selected());
    testActivity(selector, 2);

    selector.Select(1);
    TEST_ASSERT_EQUAL(1, selector.Selected());
    testActivity(selector, 10);
}

void testBlinkActivity()
{
    BlinkSettings settings;
    BlinkActivity blink(settings);

    blink.Setup();
    settings.On(100);
    settings.Off(50);
    TEST_ASSERT_EQUAL(100, settings.On());
    TEST_ASSERT_EQUAL(50, settings.Off());

    testActivity(blink, 5);

    settings.On(10);
    settings.Off(1000);
    TEST_ASSERT_EQUAL(10, settings.On());
    TEST_ASSERT_EQUAL(1000, settings.Off());

    testActivity(blink, 2);

    blink.Reset();
}

void testActivities()
{
    RUN_TEST(testBlinkActivity);
    RUN_TEST(testSelectActivity);
    RUN_TEST(testTimeMonitor);
}
