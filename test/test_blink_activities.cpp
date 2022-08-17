// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "PinDevice.h"
#include "BlinkActivity.h"

using namespace glow;

static PinDevice blinkPin;
static PinDevice blinkPinB(BLINK_PINB);

void setUp()
{
    Monitor::Cycle();
}

void tearDown() {}

template <typename ACTIVITY>
uint32_t testActivity(ACTIVITY *activity, uint32_t count = 10)
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
}

void testBlinkActivity()
{
    BlinkUpdater blink(&blinkPin);
    BlinkActivity blinker(&blink);

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

void testBlinkActivities()
{
    RUN_TEST(testBlinkActivitySetup);
    RUN_TEST(testBlinkActivity);
}
