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
using glow::print_line;

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

void testMathBench()
{
    sum += testDiv(0x0010, "divMod", divMod);
    sum += testDiv(0x0010, "divFunc", divFunc);
    sum += testDiv(0x0010, "divMul", divMul);
    sum += testDiv(0x0010, "DivMod", DivMod);
}

static uint16_t dividend[15] = {
    0, 12, 200, 623, 1601,             //
    1733, 2011, 6600, 7232, 8990,      //
    12445, 20222, 31433, 46301, 64203, //
};

static uint16_t divisor[15] = {
    13, 12, 200, 63, 161,        //
    173, 11, 99, 1232, 2300,     //
    3445, 222, 2133, 11301, 103, //
};

void testMathCompare()
{
    char buffer[64];
    Point pointMod;
    Point pointMul;
    Point pointFunc;
    Point pointDefault;

    for (uint16_t i = 0; i < sizeof(dividend) / sizeof(dividend[0]); i++)
    {
        pointMod = divMod(dividend[i], divisor[i]);
        pointMul = divMul(dividend[i], divisor[i]);
        pointFunc = divFunc(dividend[i], divisor[i]);
        pointDefault = DivMod(dividend[i], divisor[i]);

        snprintf(buffer, sizeof(buffer),
                 "mod:%u,%u mul:%u,%u func:%u,%u def:%u,%u\n",
                 pointMod.x, pointMod.y,
                 pointMul.x, pointMul.y,
                 pointFunc.x, pointFunc.y,
                 pointDefault.x, pointDefault.y);
        print_line(buffer);

        TEST_ASSERT_EQUAL(pointMod.x, pointMul.x);
        TEST_ASSERT_EQUAL(pointMod.y, pointMul.y);
        TEST_ASSERT_EQUAL(pointMod.x, pointFunc.x);
        TEST_ASSERT_EQUAL(pointMod.y, pointFunc.y);
        TEST_ASSERT_EQUAL(pointMod.x, pointDefault.x);
        TEST_ASSERT_EQUAL(pointMod.y, pointDefault.y);
    }
}

void testMath()
{
    RUN_TEST(testMathCompare);
    RUN_TEST(testMathBench);
}