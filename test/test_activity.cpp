// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"
#include "ActivityTimer.h"
#include "ActivityCounter.h"

uint32_t testActivity(Activity *activity, uint32_t count = 10)
{
    uint32_t ticks = 0;
    do
    {
        Activity::Cycle();
        if (activity->Pulse())
        {
            ticks++;
        }
    } while (ticks < count && !activity->Done());

    return ticks;
}

void testBlinkActivity()
{
    Activity::Cycle();
    BlinkSettings blink;
    blink.Setup();

    BlinkMonitor monitor(&blink);
    BlinkActivity blinker(&monitor, &blink);
    blinker.Setup();

    blink.On(2000);
    blink.Off(1000);
    TEST_ASSERT_EQUAL(2000, blink.On());
    TEST_ASSERT_EQUAL(1000, blink.Off());
    auto ticks = testActivity(&blinker, 4);

    blink.On(100);
    blink.Off(900);
    TEST_ASSERT_EQUAL(100, blink.On());
    TEST_ASSERT_EQUAL(900, blink.Off());

    ticks = testActivity(&blinker, 10);

    blink.On(2000);
    blink.Off(1000);
    testActivity(&blinker, 4);

    ActivityCounter counter(&monitor, 100);
    BlinkActivity blinkerC(&counter, &blink);
    blinkerC.Setup();
    blink.On(50);
    blink.Off(50);
    ticks = testActivity(&blinkerC, 1000);
    TEST_ASSERT_EQUAL(100, ticks);

    ActivityTimer timer(&monitor, 5000);
    BlinkActivity blinkerT(&timer, &blink);
    blinkerT.Setup();
    blink.On(250);
    blink.Off(250);

    ticks = testActivity(&blinkerT, 1000);
    TEST_ASSERT_LESS_THAN(40, ticks);
    TEST_ASSERT_UINT_WITHIN(1, Activity::Now(), timer.End());
}

void testActivities()
{
    RUN_TEST(testBlinkActivity);
}
