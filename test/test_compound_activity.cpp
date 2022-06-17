// // Copyright (c) 2022 Dave Marsh. See LICENSE.

// #define UNITY_INCLUDE_PRINT_FORMATTED
// #include <unity.h>
// #include "base.h"
// #include "BlinkActivity.h"
// #include "SerialActivity.h"
// #include "ParallelActivity.h"
// #include "TimeMonitor.h"

// uint32_t testCompoundActivity(Activity *activity)
// {
//     uint32_t ticks = 0;
//     const uint32_t max_ticks = 100000;

//     TEST_ASSERT(!activity->Done());
//     while (!activity->Done() && ticks < max_ticks)
//     {
//         Activity::Cycle();  
//         if (activity->Pulse())
//         {
//             ticks++;
//         }
//     }
//     TEST_ASSERT(ticks < max_ticks);
//     return ticks;
// }

// void testTimedSerialActivity()
// {
//     SerialActivity serial(3);

//     BlinkSettings settingsa;
//     BlinkActivity blinka(settingsa);
//     TimeMonitor timera;
//     // timera.Duration(2);
//     blinka.Monitor(&timera);
//     settingsa.On(250);
//     settingsa.Off(250);

//     BlinkSettings settingsb;
//     BlinkActivity blinkb(settingsb);
//     TimeMonitor timerb;
//     // timerb.Duration(2);
//     blinkb.Monitor(&timerb);
//     settingsb.On(150);
//     settingsb.Off(150);

//     BlinkSettings settingsc;
//     BlinkActivity blinkc(settingsc);
//     TimeMonitor timerc;
//     // timerc.Duration(2);
//     blinkc.Monitor(&timerc);
//     settingsc.On(50);
//     settingsc.Off(50);

//     serial.Add(&blinka);
//     serial.Add(&blinkb);
//     serial.Add(&blinkc);
// }

// void testCompoundActivities()
// {
//     RUN_TEST(testTimedSerialActivity);
// }