// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "PinDevice.h"
#include "BlinkActivity.h"
#include "ActivityTimer.h"
#include "ActivityCounter.h"
#include "SerialActivity.h"

using namespace glow;

static PinDevice blinkPin;

void setUp()
{
    Activity::Cycle();
}

void tearDown() {}

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

void testBlinkActivitySetup()
{
    TEST_ASSERT_EQUAL(BLINK_PIN, blinkPin.Pin());
    TEST_ASSERT_EQUAL(OUTPUT, blinkPin.Mode());
    blinkPin.Setup();
#ifdef ARDUINO
    // for (size_t i = 0; i < 3; i++)
    // {
    //     delay(100);
    //     blinkPin.Write(BLINK_ON);
    //     delay(100);
    //     blinkPin.Write(BLINK_OFF);
    // }
    // delay(100);
#endif
}

uint32_t calc(uint16_t on, uint16_t off, uint32_t duration)
{
    return (duration * 2) / (on + off);
}

void testBlinkActivityTimer()
{
    BlinkSettings blink(&blinkPin);
    BlinkMonitor monitor(&blink);
    ActivityTimer timer(&monitor, 2000);
    BlinkActivity blinker(&timer, &blink);
    blink.On(250);
    blink.Off(250);
    auto c = calc(blink.On(), blink.Off(), timer.Duration());
    auto ticks = testActivity(&blinker, c + 100);
    TEST_ASSERT_UINT_WITHIN(1, Activity::Now(), timer.End());
    TEST_ASSERT_UINT_WITHIN(1, c, ticks);
}

void testBlinkActivityCounter()
{
    BlinkSettings blink(&blinkPin);
    BlinkMonitor monitor(&blink);
    ActivityCounter counter(&monitor, 25);
    BlinkActivity blinker(&counter, &blink);
    blink.On(100);
    blink.Off(100);
    auto ticks = testActivity(&blinker, 40);
    TEST_ASSERT_EQUAL(25, ticks);
}

void testBlinkActivity()
{
    BlinkSettings blink(&blinkPin);
    BlinkMonitor monitor(&blink);
    BlinkActivity blinker(&monitor, &blink);

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

void testBlinkActivitySerial()
{
    BlinkSettings blinkT(&blinkPin);
    BlinkMonitor monitorT(&blinkT);
    ActivityTimer timer(&monitorT, 2000);
    BlinkActivity blinkerT(&timer, &blinkT);
    blinkT.On(250);
    blinkT.Off(250);

    BlinkSettings blinkC(&blinkPin);
    BlinkMonitor monitorC(&blinkC);
    ActivityCounter counter(&monitorC, 100);
    BlinkActivity blinkerC(&counter, &blinkC);
    blinkC.On(50);
    blinkC.Off(50);

    SerialActivity serialActivity(2);
    TEST_ASSERT_EQUAL(2, serialActivity.Maximum());
    serialActivity.Add(&blinkerC);
    TEST_ASSERT_EQUAL(1, serialActivity.Length());
    serialActivity.Add(&blinkerT);
    TEST_ASSERT_EQUAL(2, serialActivity.Length());

    auto c = calc(blinkT.On(), blinkT.Off(), timer.Duration()) +
             counter.Maximum();
    auto ticks = testActivity(&serialActivity, c + 100);
    TEST_ASSERT_UINT_WITHIN(1, c, ticks);
}

void testBlinkActivities()
{
    RUN_TEST(testBlinkActivitySetup);
    // RUN_TEST(testBlinkActivity);
    // RUN_TEST(testBlinkActivityCounter);
    // RUN_TEST(testBlinkActivityTimer);
    RUN_TEST(testBlinkActivitySerial);
}
