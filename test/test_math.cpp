// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"
#include "wait.h"

#include "Math.h"

using glow::Benchmark;
using glow::divFunc;
using glow::DivMod;
using glow::divMod;
using glow::divMul;
using glow::Point;

template <typename POINTFUNC>
uint16_t testDiv(const uint16_t count, const char *title, POINTFUNC func)
{
    set_real_time(true);
    Benchmark mark;
    mark.Begin(title);
    Point point;
    uint16_t sum = 0;

    for (uint16_t length = 1; length < 19; length++)
        for (uint16_t j = 0; j < count; j++)
            for (uint16_t i = 0; i < count; i++)
            {
                point = func(i, length);
                sum += point.x + point.y;
            }

    mark.End();
    set_real_time(false);
    return sum;
}

uint32_t sum = 0;

void math_bench()
{
    sum += testDiv(0x0100, "divMod", divMod);
    sum += testDiv(0x0100, "divFunc", divFunc);
    sum += testDiv(0x0100, "divMul", divMul);
    sum += testDiv(0x0100, "DivMod", DivMod);
}

void testMath()
{
    RUN_TEST(math_bench);
}