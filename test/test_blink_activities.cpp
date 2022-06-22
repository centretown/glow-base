// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "PinDevice.h"
#include "BlinkActivity.h"
#include "TimeMonitor.h"
#include "CountMonitor.h"
#include "SerialActivity.h"
#include "ParallelActivity.h"

using namespace glow;

static PinDevice blinkPin;
static PinDevice blinkPinB(BLINK_PINB);

void setUp()
{
    Monitor::Cycle();
}

void tearDown() {}

uint32_t testActivity(Activity *activity, uint32_t count = 10)
{
    uint32_t ticks = 0;
    do
    {
        Monitor::Cycle();
        if (activity->Pulse())
        {
            ticks++;
        }
    } while (ticks < count && !activity->Done());

    return ticks;
}

void testBlinkActivitySetup()
{
    TEST_ASSERT_EQUAL(OUTPUT, blinkPin.Mode());
    blinkPin.Setup();
    TEST_ASSERT_EQUAL(OUTPUT, blinkPinB.Mode());
    blinkPinB.Setup();
#ifdef ARDUINO
// sanity check
//  for (size_t i = 0; i < 3; i++)
//  {
//      delay(100);
//      blinkPin.Write(BLINK_ON);
//      delay(100);
//      blinkPin.Write(BLINK_OFF);
//  }
//  delay(100);
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
    TimeMonitor timer(&monitor, 2000);
    TEST_ASSERT_EQUAL(0, timer.End());
    TEST_ASSERT_EQUAL(2000, timer.Duration());
    BlinkActivity blinker(&timer, &blink);
    blink.On(250);
    blink.Off(250);
    auto c = calc(blink.On(), blink.Off(), timer.Duration());
    auto end = Monitor::Now() + timer.Duration();
    auto ticks = testActivity(&blinker, c + 100);
    TEST_ASSERT_UINT_WITHIN(10, end, timer.End());
    TEST_ASSERT_UINT_WITHIN(1, Monitor::Now(), timer.End());
    TEST_ASSERT_UINT_WITHIN(1, c, ticks);
}

void testBlinkCountMonitor()
{
    BlinkSettings blink(&blinkPin);
    BlinkMonitor monitor(&blink);
    CountMonitor counter(&monitor, 25);
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

    blink.On(1000);
    blink.Off(500);
    TEST_ASSERT_EQUAL(1000, blink.On());
    TEST_ASSERT_EQUAL(500, blink.Off());
    testActivity(&blinker, 4);

    blink.On(100);
    blink.Off(900);
    TEST_ASSERT_EQUAL(100, blink.On());
    TEST_ASSERT_EQUAL(900, blink.Off());
    testActivity(&blinker, 10);

    blink.On(1000);
    blink.Off(500);
    testActivity(&blinker, 4);
}

void testBlinkActivitySerialSimplified()
{
    BlinkSettings blink(&blinkPin);
    blink.On(50);
    blink.Off(50);
    BlinkMonitor monitor(&blink);
    TimeMonitor timer2000(&monitor, 2000);
    TimeMonitor timer1000(&monitor, 1000);

    BlinkActivity blinker2000(&timer2000, &blink);
    BlinkActivity blinker1000(&timer1000, &blink);
    SerialActivity serialActivity(2);
    serialActivity.Add(&blinker2000);
    serialActivity.Add(&blinker1000);
    auto c = calc(blink.On(), blink.Off(), timer2000.Duration());
    c += calc(blink.On(), blink.Off(), timer1000.Duration());
    auto ticks = testActivity(&serialActivity, c + 100);
    TEST_ASSERT_UINT_WITHIN(2, c, ticks);
}

void testBlinkActivitySerial()
{
    BlinkSettings blinkT(&blinkPinB);
    BlinkMonitor monitorT(&blinkT);
    TimeMonitor timer(&monitorT, 2000);
    BlinkActivity blinkerT(&timer, &blinkT);
    blinkT.On(250);
    blinkT.Off(250);

    BlinkSettings blinkC(&blinkPin);
    BlinkMonitor monitorC(&blinkC);
    CountMonitor counter(&monitorC, 100);
    BlinkActivity blinkerC(&counter, &blinkC);
    blinkC.On(50);
    blinkC.Off(50);

    SerialActivity serialActivity(2);
    TEST_ASSERT_EQUAL(0, serialActivity.Current());
    TEST_ASSERT_EQUAL(2, serialActivity.Maximum());
    serialActivity.Add(&blinkerT);
    TEST_ASSERT_EQUAL(1, serialActivity.Length());
    serialActivity.Add(&blinkerC);
    TEST_ASSERT_EQUAL(2, serialActivity.Length());
    auto c = calc(blinkT.On(), blinkT.Off(), timer.Duration()) +
             counter.Maximum();
    auto ticks = testActivity(&serialActivity, c + 100);
    TEST_ASSERT_UINT_WITHIN(1, c, ticks);

    counter.Reset();
    timer.Reset();
    SerialActivity serialActivityReorder(2);
    TEST_ASSERT_EQUAL(0, serialActivityReorder.Current());
    TEST_ASSERT_EQUAL(2, serialActivityReorder.Maximum());
    serialActivityReorder.Add(&blinkerC);
    TEST_ASSERT_EQUAL(1, serialActivityReorder.Length());
    serialActivityReorder.Add(&blinkerT);
    TEST_ASSERT_EQUAL(2, serialActivityReorder.Length());
    c = calc(blinkT.On(), blinkT.Off(), timer.Duration()) +
        counter.Maximum();
    ticks = testActivity(&serialActivityReorder, c + 100);
    TEST_ASSERT_UINT_WITHIN(1, c, ticks);
}

void testBlinkActivityParallel()
{
    BlinkSettings blinkT(&blinkPinB);
    BlinkMonitor monitorT(&blinkT);
    TimeMonitor timer(&monitorT, 10000);
    BlinkActivity blinkerT(&timer, &blinkT);
    blinkT.On(250);
    blinkT.Off(250);

    BlinkSettings blinkC(&blinkPin);
    BlinkMonitor monitorC(&blinkC);
    CountMonitor counter(&monitorC, 500);
    BlinkActivity blinkerC(&counter, &blinkC);
    blinkC.On(50);
    blinkC.Off(50);

    ParallelActivity parallel(2);
    TEST_ASSERT_EQUAL(2, parallel.Maximum());
    parallel.Add(&blinkerT);
    TEST_ASSERT_EQUAL(1, parallel.Length());
    parallel.Add(&blinkerC);
    TEST_ASSERT_EQUAL(2, parallel.Length());
    auto ticks = testActivity(&parallel, 1000);
    TEST_ASSERT_LESS_THAN(1000, ticks);
}

void testBlinkActivities()
{
    RUN_TEST(testBlinkActivitySetup);
    RUN_TEST(testBlinkActivity);
    RUN_TEST(testBlinkCountMonitor);
    RUN_TEST(testBlinkActivityTimer);
    RUN_TEST(testBlinkActivitySerial);
    RUN_TEST(testBlinkActivitySerialSimplified);
    RUN_TEST(testBlinkActivityParallel);
}
