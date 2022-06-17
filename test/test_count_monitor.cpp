// // Copyright (c) 2022 Dave Marsh. See LICENSE.

// #define UNITY_INCLUDE_PRINT_FORMATTED
// #include <unity.h>
// #include "base.h"
// #include "BlinkActivity.h"
// #include "CountMonitor.h"

// uint32_t testCountActivity(Activity *activity)
// {
//     uint32_t ticks = 0;
//     const uint32_t max_ticks = 10000;

//     TEST_ASSERT(activity->Active());
//     while (ticks < max_ticks)
//     {
//         Activity::Cycle();
//         if (activity->Pulse())
//         {
//             ticks++;
//         }
//     }
//     // TEST_ASSERT(ticks < max_ticks);
//     return ticks;
// }

// void testCountBlink()
// {
//     BlinkSettings blink;
//     blink.On(900);
//     blink.Off(100);

//     CountMonitor counter(4);
//     TEST_ASSERT_EQUAL(0, counter.Count());
//     TEST_ASSERT_EQUAL(4, counter.Extent());

//     BlinkActivity blinker(blink);
//     blinker.Monitor(&counter);
//     blinker.Interval(0);

//     auto ticks = testCountActivity(&blinker);

//     TEST_ASSERT_EQUAL(4, counter.Extent());
//     TEST_ASSERT_EQUAL(4, counter.Count());
//     TEST_ASSERT_EQUAL(4, ticks);
//     TEST_ASSERT_TRUE(counter.Done(&blinker));
// }

// void testCountMonitor()
// {
//     RUN_TEST(testCountBlink);
// }