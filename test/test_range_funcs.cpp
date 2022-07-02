// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "SimpleRange.h"
#include "Sweeper.h"
#include "Mapper.h"

using namespace glow;

void testSimpleSweeper()
{
    SimpleRange range(0, 10);
    class sw : public Sweeper<uint16_t*>
    {
    public:
        virtual void Act(uint16_t i, uint16_t *j)
        {
            *j= i;
        }
    };

    uint16_t y;
    sw x;
    x.Sweep(&range, &y);
    TEST_ASSERT_EQUAL(9, y);
    range.Reverse(true);
    x.Sweep(&range, &y);
    TEST_ASSERT_EQUAL(0, y);
}

void testSimpleSweepers()
{
    RUN_TEST(testSimpleSweeper);
}