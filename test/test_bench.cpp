// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "bench.h"
#include "wait.h"

void testBenchPrint()
{
    set_real_time(true);

    print_line("CLOCKS_PER_SEC: ");
    print_millis(clocks_sec);

    print_line(" CLOCKS_PER_MS: ");
    print_millis(clocks_ms, true);

    print_elapsed(50, 60);

    uint32_t begin = millis();
    wait(1000);
    uint32_t end = millis();
    print_elapsed(begin, end);

    set_real_time(false);
}

void testBench()
{
    print_line("TESTING BENCH", true);
    RUN_TEST(testBenchPrint);
}
