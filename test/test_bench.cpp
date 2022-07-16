// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "bench.h"
#include "wait.h"
#include <ArduinoJson.h>

void test_millis32()
{
    set_real_time(true);

    Bench results("millis32 test");
    results.begin = millis32();
    wait(1000);
    results.end = millis32();
    results.Print();

    set_real_time(false);
}

void testBench()
{
    print_line("TESTING BENCH", true);
    RUN_TEST(test_millis32);
}
