// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"
#include "ActivityTimer.h"
#include "ActivityCounter.h"

static BlinkSettings blink;
static BlinkMonitor monitor(&blink);
static BlinkActivity blinker(&monitor, &blink);
static ActivityTimer timer(&monitor, 5000);
static BlinkActivity blinkerT(&timer, &blink);
static ActivityCounter counter(&monitor, 100);
static BlinkActivity blinkerC(&counter, &blink);

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

void testBlinkActivityTimer()
{
    timer.Reset(); // required  millis based
    blink.On(250);
    blink.Off(250);
    auto ticks = testActivity(&blinkerT, 1000);
    TEST_ASSERT_EQUAL(20, ticks);
    TEST_ASSERT_UINT_WITHIN(1, Activity::Now(), timer.End());
}

void testBlinkActivityCounter()
{
    counter.Reset(); // shouldn't be required not millis based
    blink.On(50);
    blink.Off(50);
    auto ticks = testActivity(&blinkerC, 1000);
    TEST_ASSERT_EQUAL(100, ticks);
}

void testBlinkActivity()
{
    blink.On(2000);
    blink.Off(1000);
    TEST_ASSERT_EQUAL(2000, blink.On());
    TEST_ASSERT_EQUAL(1000, blink.Off());
    testActivity(&blinker, 4);

    blink.On(100);
    blink.Off(900);
    TEST_ASSERT_EQUAL(100, blink.On());
    TEST_ASSERT_EQUAL(900, blink.Off());

    testActivity(&blinker, 10);

    blink.On(2000);
    blink.Off(1000);
    testActivity(&blinker, 4);
}

void testBlinkActivitiesSetup()
{
    Activity::Cycle();
    blink.Setup();
    blinker.Setup();
    blinkerT.Setup();
    blinkerC.Setup();
}

void testBlinkActivities()
{
    RUN_TEST(testBlinkActivitiesSetup);
    RUN_TEST(testBlinkActivity);
    RUN_TEST(testBlinkActivityCounter);
    RUN_TEST(testBlinkActivityTimer);
}
