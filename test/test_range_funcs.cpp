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

void testSimpleSweepers()
{
    RUN_TEST(testSimpleSweeper);
}