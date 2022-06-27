// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "Sort.h"
using namespace glow;

void testSortU8()
{
    uint8_t ordered[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t unordered[10]{3, 1, 9, 2, 5, 6, 7, 0, 8, 4};
    Sort(unordered, sizeof(unordered));
    TEST_ASSERT_EQUAL_CHAR_ARRAY(ordered, unordered, sizeof(unordered));
}

void testSort()
{
    RUN_TEST(testSortU8);
}