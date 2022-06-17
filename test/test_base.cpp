// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"

BlinkSettings blink;
BlinkMonitor monitor(&blink);
BlinkActivity blinker(&monitor, &blink);

void testFeatures();
void testActivities();

void run()
{
    UNITY_BEGIN();
    testFeatures();
    testActivities();
    UNITY_END();
}

#ifdef ARDUINO

void setup()
{
    delay(2000);
    run();
    blinker.Setup();
}

uint64_t now;
void loop()
{
    Activity::Cycle();
    blinker.Pulse();
}

#else
int main(int argc, char **argv)
{
    run();
}
#endif // ARDUINO
