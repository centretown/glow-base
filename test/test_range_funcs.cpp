// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "Range.h"

using glow::Range;

typedef struct
{
    uint16_t index;
    uint8_t value;
    inline void Put(uint16_t i, uint8_t v)
    {
        index = i;
        value = v;
    }
    void Update() {}
} TestPut;

typedef struct
{
    uint16_t index;
    inline uint16_t Map(uint16_t i)
    {
        index = i * 2;
        return index;
    }
} TestMap;

void testRangeSpin()
{
    Range range(5, 20);
    TestPut putter;
    range.Spin(putter, (uint8_t)0);
    TEST_ASSERT_EQUAL(range.End() - 1, putter.index);
    TEST_ASSERT_EQUAL(0, putter.value);

    range.Resize(999, 22);
    TEST_ASSERT_EQUAL(range.Begin(), 22);
    TEST_ASSERT_EQUAL(range.End(), 999);

    range.Spin(putter, (uint8_t)0);
    TEST_ASSERT_EQUAL(range.End() - 1, putter.index);
    TEST_ASSERT_EQUAL(0, putter.value);
}

void testRangeSpinMap()
{
    Range range(5, 20);
    TestPut putter;
    TestMap mapper;

    range.Spin(putter, mapper, (uint8_t)0);
    TEST_ASSERT_EQUAL((range.End() - 1) * 2, putter.index);
    TEST_ASSERT_EQUAL((range.End() - 1) * 2, mapper.index);
    TEST_ASSERT_EQUAL(0, putter.value);

    range.Resize(999, 22);
    TEST_ASSERT_EQUAL(range.Begin(), 22);
    TEST_ASSERT_EQUAL(range.End(), 999);

    range.Spin(putter, mapper, (uint8_t)0);
    TEST_ASSERT_EQUAL((range.End() - 1) * 2, putter.index);
    TEST_ASSERT_EQUAL((range.End() - 1) * 2, mapper.index);
    TEST_ASSERT_EQUAL(0, putter.value);
}

void testRangeSpinMapReverse()
{
    Range range(5, 20);
    TestPut putter;
    TestMap mapper;

    range.Spin(putter, mapper, (uint8_t)0, true);
    TEST_ASSERT_EQUAL(range.Begin() * 2, putter.index);
    TEST_ASSERT_EQUAL(range.Begin() * 2, mapper.index);
    TEST_ASSERT_EQUAL(0, putter.value);

    range.Resize(999, 22);
    TEST_ASSERT_EQUAL(range.Begin(), 22);
    TEST_ASSERT_EQUAL(range.End(), 999);

    range.Spin(putter, mapper, (uint8_t)0, true);
    TEST_ASSERT_EQUAL(range.Begin() * 2, putter.index);
    TEST_ASSERT_EQUAL(range.Begin() * 2, mapper.index);
    TEST_ASSERT_EQUAL(0, putter.value);
}

void testRangeReverseSpin()
{
    Range range(0, 20);
    TestPut t;
    range.Spin(t, (uint8_t)0, true);
    TEST_ASSERT_EQUAL(range.Begin(), t.index);
    TEST_ASSERT_EQUAL(0, t.value);

    range.Resize(555, 43);
    TEST_ASSERT_EQUAL(range.Begin(), 43);
    TEST_ASSERT_EQUAL(range.End(), 555);

    range.Spin(t, (uint8_t)255, true);
    TEST_ASSERT_EQUAL(range.Begin(), t.index);
    TEST_ASSERT_EQUAL(255, t.value);
}

void testRangeSpinValues()
{
    Range range(5, 20);
    TestPut putter;
    TestMap mapper;
    range.SpinValues(putter, mapper);
    auto expected = range.End() - 1;
    TEST_ASSERT_EQUAL(expected, putter.index);
    TEST_ASSERT_EQUAL(expected * 2, putter.value);

    range.SpinValues(putter, mapper, mapper);
    expected = (range.End() - 1) * 2;
    TEST_ASSERT_EQUAL(expected, putter.index);
    TEST_ASSERT_EQUAL(expected, putter.value);
}

void testRangeUpdate()
{
    Range range(5, 20);
    uint16_t position = 0;
    position = range.Update(position);
    TEST_ASSERT_EQUAL(range.Begin(), position);
    position = range.Update(0, true);
    TEST_ASSERT_EQUAL(range.End() - 1, position);

    position = range.Update(21);
    TEST_ASSERT_EQUAL(range.End() - 1, position);
    position = range.Update(21, true);
    TEST_ASSERT_EQUAL(range.Begin(), position);
    position = range.Update(21, true, true);
    TEST_ASSERT_EQUAL(range.End() - 1, position);

    position = range.Update(5);
    TEST_ASSERT_EQUAL(5, position);
    position = range.Update(19);
    TEST_ASSERT_EQUAL(19, position);
    position = range.Update(10);
    TEST_ASSERT_EQUAL(10, position);
}

void testRangeFuncs()
{
    RUN_TEST(testRangeUpdate);
    RUN_TEST(testRangeSpin);
    RUN_TEST(testRangeReverseSpin);
    RUN_TEST(testRangeSpinMap);
    RUN_TEST(testRangeSpinMapReverse);
    RUN_TEST(testRangeSpinValues);
}
