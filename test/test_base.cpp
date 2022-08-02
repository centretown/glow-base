// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "PinDevice.h"
#include "BlinkActivity.h"
#include "Benchmark.h"

// using namespace glow;

using glow::Benchmark;
using glow::BlinkActivity;
using glow::BlinkMonitor;
using glow::BlinkSettings;
using glow::Monitor;
using glow::PinDevice;

PinDevice blinkPin;
BlinkSettings blink(&blinkPin);
BlinkMonitor monitor(&blink);
BlinkActivity blinker(&monitor, &blink);

void testBench();
void testMath();
void testFeatures();
void testBlinkActivities();
void testSort();
void testFilters();
void testRangeFuncs();
void testRangeOperators();

void run()
{
    UNITY_BEGIN();
    testBench();
    testMath();
    // testFeatures();
    // testFilters();
    testSort();
    testBlinkActivities();
    testRangeFuncs();
    testRangeOperators();
    UNITY_END();
}

#ifdef ARDUINO

void setup()
{
#ifdef ARDUINO
    Serial.begin(115200);
#endif
    delay(2000);
    Benchmark::Setup();
    run();
    blinkPin.Setup();
    blinker.Reset();
}

void loop()
{
    Monitor::Cycle();
    blinker.Pulse();
}

#else // NATIVE

#include "native_main.h"

int main(int argc, char **argv)
{
    run();

    return native_main_test(argc, argv);
}
#endif // ARDUINO
