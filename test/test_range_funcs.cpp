// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "Range.h"
#include "Sweeper.h"
#include "Mapper.h"

using namespace glow;

void testSimpleSweeper()
{
    Range range(0, 10);
    class sw : public Sweeper<uint16_t *>
    {
    public:
        virtual void Act(uint16_t i, uint16_t *j)
        {
            *j = i;
        }
    };

    uint16_t y;
    sw x;
    x.Sweep(range.Pack(), &y);
    TEST_ASSERT_EQUAL(9, y);
    x.Sweep(range.Pack(), &y, true);
    TEST_ASSERT_EQUAL(0, y);
}

typedef struct
{
    uint16_t index;
    uint8_t value;
    void Put(uint16_t i, uint8_t v)
    {
        index = i;
        value = v;
    }
} TestPut;

void testRangeSpinner()
{
    Range range(5, 20);
    TestPut t;
    range.Spin(t, (uint8_t)0);
    TEST_ASSERT_EQUAL(range.End() - 1, t.index);
    TEST_ASSERT_EQUAL(0, t.value);

    range.Resize(999, 22);
    TEST_ASSERT_EQUAL(range.Begin(), 22);
    TEST_ASSERT_EQUAL(range.End(), 999);

    range.Spin(t, (uint8_t)0);
    TEST_ASSERT_EQUAL(range.End()-1, t.index);
    TEST_ASSERT_EQUAL(0, t.value);
}

void testRangeReverseSpin()
{
    Range range(0, 20);
    TestPut t;
    range.ReverseSpin(t, (uint8_t)0);
    TEST_ASSERT_EQUAL(range.Begin(), t.index);
    TEST_ASSERT_EQUAL(0, t.value);

    range.Resize(555, 43);
    TEST_ASSERT_EQUAL(range.Begin(), 43);
    TEST_ASSERT_EQUAL(range.End(), 555);

    range.ReverseSpin(t, (uint8_t)255);
    TEST_ASSERT_EQUAL(range.Begin(), t.index);
    TEST_ASSERT_EQUAL(255, t.value);
}

void testRangeFuncs()
{
    RUN_TEST(testSimpleSweeper);
    RUN_TEST(testRangeSpinner);
    RUN_TEST(testRangeReverseSpin);
}