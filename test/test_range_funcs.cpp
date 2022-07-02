// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "SimpleRange.h"
#include "Sweeper.h"

using namespace glow;

void testSimpleSweeper()
{
    SimpleRange range(0, 10);
    class sw : public Sweeper
    {
    public:
        uint16_t j;

    public:
        virtual void Act(uint16_t i)
        {
            j = i;
        }
    };

    sw x;
    x.Sweep(&range);
    TEST_ASSERT_EQUAL(9, x.j);
    range.Reverse(true);
    x.Sweep(&range);
    TEST_ASSERT_EQUAL(0, x.j);
}

void testSimpleSweepers()
{
    RUN_TEST(testSimpleSweeper);
}