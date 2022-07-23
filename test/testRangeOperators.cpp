// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "Range.h"

using glow::Range;

void testRangeOperator()
{
    TEST_ASSERT_EQUAL(sizeof(uint32_t), sizeof(Range));
    Range source(10, 12);
    TEST_ASSERT_EQUAL(10, source.Begin());
    TEST_ASSERT_EQUAL(12, source.End());
    Range target = source;
    TEST_ASSERT_EQUAL(10, target.Begin());
    TEST_ASSERT_EQUAL(12, target.End());

    target = Range(50, 90);
    TEST_ASSERT_EQUAL(50, target.Begin());
    TEST_ASSERT_EQUAL(90, target.End());

    Range target2 = source = target;
    TEST_ASSERT_EQUAL(50, target2.Begin());
    TEST_ASSERT_EQUAL(90, target2.End());
    TEST_ASSERT_EQUAL(50, target.Begin());
    TEST_ASSERT_EQUAL(90, target.End());
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(90, source.End());

    ++source;
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(91, source.End());

    ++source;
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(92, source.End());

    --source;
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(91, source.End());

    source = 0;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(0, source.End());

    ++source;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(1, source.End());
    TEST_ASSERT_EQUAL(1, source.Length());

    source = Range(10, 100);
    TEST_ASSERT_EQUAL(10, source.Begin());
    TEST_ASSERT_EQUAL(100, source.End());

    target = source + 1;
    TEST_ASSERT_EQUAL(10, target.Begin());
    TEST_ASSERT_EQUAL(101, target.End());

    target = source + 5;
    TEST_ASSERT_EQUAL(10, target.Begin());
    TEST_ASSERT_EQUAL(105, target.End());

    target = source - 5;
    TEST_ASSERT_EQUAL(10, target.Begin());
    TEST_ASSERT_EQUAL(95, target.End());

    target = source - 90;
    TEST_ASSERT_EQUAL(10, target.Begin());
    TEST_ASSERT_EQUAL(10, target.End());

    source(25, 50);
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());

    source(0, 0xfff0);
    target = source + 0x0f;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(0xfff0, source.End());
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(0xffff, target.End());

    // effect: end+0x10(1)<end(0xffff) -> end=0xffff
    target = source + 0x10;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(0xfff0, source.End());
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(0xffff, target.End());

    // effect: end-26<begin(25) -> end=begin(25)
    source(25, 50);
    target = source - 26;
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    TEST_ASSERT_EQUAL(25, target.Begin());
    TEST_ASSERT_EQUAL(25, target.End());

    target = source;
    TEST_ASSERT_EQUAL(source.Begin(), target.Begin());
    TEST_ASSERT_EQUAL(source.End(), target.End());
    target += 5;
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    TEST_ASSERT_EQUAL(source.Begin(), target.Begin());
    TEST_ASSERT_EQUAL(source.End() + 5, target.End());

    target = source;
    TEST_ASSERT_EQUAL(source.Begin(), target.Begin());
    TEST_ASSERT_EQUAL(source.End(), target.End());
    target -= 5;
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    TEST_ASSERT_EQUAL(source.Begin(), target.Begin());
    TEST_ASSERT_EQUAL(source.End() - 5, target.End());

    source(0, 0xfff0);
    target = source;
    target += 0x0f;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(0xfff0, source.End());
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(0xffff, target.End());

    // effect: end+0x10(1)<end(0xffff) -> end=0xffff
    target = source;
    target += 0x10;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(0xfff0, source.End());
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(0xffff, target.End());

    // effect: end-26<begin(25) -> end=begin(25)
    source(25, 50);
    target = source;
    target -= 26;
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    TEST_ASSERT_EQUAL(25, target.Begin());
    TEST_ASSERT_EQUAL(25, target.End());

    source(25, 50);
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());

    target = source << 8;
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    TEST_ASSERT_EQUAL(source.Begin() - 8, target.Begin());
    TEST_ASSERT_EQUAL(source.End() - 8, target.End());

    target = source << 25;
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    TEST_ASSERT_EQUAL(source.Begin() - 25, target.Begin());
    TEST_ASSERT_EQUAL(source.End() - 25, target.End());

    // effect: begin-26>begin -> begin(0),end(25)
    target = source << 26;
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    TEST_ASSERT_EQUAL(source.Begin() - 25, target.Begin());
    TEST_ASSERT_EQUAL(source.End() - 25, target.End());

    target = source >> 25;
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    TEST_ASSERT_EQUAL(source.Begin() + 25, target.Begin());
    TEST_ASSERT_EQUAL(source.End() + 25, target.End());

    source(0, 0xfff0);
    target = source >> 0x0f;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xfff0, source.End());
    TEST_ASSERT_EQUAL_HEX(source.Begin() + 0x0f, target.Begin());
    TEST_ASSERT_EQUAL_HEX(source.End() + 0x0f, target.End());

    // effect end>0xffff -> end=0xffff
    target = source >> 0x10;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xfff0, source.End());
    TEST_ASSERT_EQUAL_HEX(source.Begin() + 0x0f, target.Begin());
    TEST_ASSERT_EQUAL_HEX(source.End() + 0x0f, target.End());

    source(50, 1920);
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(1920, source.End());

    source <<= 5;
    TEST_ASSERT_EQUAL(45, source.Begin());
    TEST_ASSERT_EQUAL(1915, source.End());

    source(50, 1920);
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(1920, source.End());

    // effect end>0 -> end=0
    source <<= 55;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(1870, source.End());

    source(50, 1920);
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(1920, source.End());

    source >>= 20;
    TEST_ASSERT_EQUAL(70, source.Begin());
    TEST_ASSERT_EQUAL(1940, source.End());

    source(0, 0xfff0);
    TEST_ASSERT_EQUAL_HEX(0, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xfff0, source.End());
    source >>= 0x0f;
    TEST_ASSERT_EQUAL_HEX(0x0f, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xffff, source.End());

    // effect end>0xffff -> end=0xffff
    source(0, 0xfff0);
    TEST_ASSERT_EQUAL_HEX(0, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xfff0, source.End());
    source >>= 0x10;
    TEST_ASSERT_EQUAL_HEX(0x0f, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xffff, source.End());
}

void testRangeOperators()
{
    RUN_TEST(testRangeOperator);
}
