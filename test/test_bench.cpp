// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "BenchMark.h"
#include "wait.h"
#include <ArduinoJson.h>

using glow::BenchMark;
using glow::print_line;

void test_millis32()
{
    BenchMark benchMark;
    set_real_time(true);

    benchMark.Begin("test_millis32");
    wait(1000);
    benchMark.End();

    set_real_time(false);
}

void testBench()
{
    RUN_TEST(test_millis32);
}
