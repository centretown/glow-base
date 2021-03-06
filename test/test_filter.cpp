// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Filter.h"

using namespace glow;

class testX
{
private:
    uint16_t x;

public:
    testX(uint16_t x = 0) : x(x) {}
    testX(testX &c) : x(c.x) {}
    void Copy(testX &c) { x = c.x; }
    inline void X(uint16_t v) { x = v; }
    inline uint16_t X() { return x; }
};

class doubleFilter : public Filter<testX>
{
private:
    virtual void apply(testX &source, testX &destination)
    {
        destination.X(2 * source.X());
    }
};

void testFilter()
{
    const uint16_t tx = 0x22;

    testX source(tx), destination;
    doubleFilter filter;
    TEST_ASSERT_EQUAL_HEX(tx, source.X());
    filter.Apply(source, destination);
    TEST_ASSERT_EQUAL_HEX(tx * 2, destination.X());

    doubleFilter filter2;
    filter.Link(&filter2);
    filter.Apply(source, destination);
    TEST_ASSERT_EQUAL_HEX(tx * 4, destination.X());

    filter.UnLink();
    filter.Apply(source, destination);
    TEST_ASSERT_EQUAL_HEX(tx, source.X());
    TEST_ASSERT_EQUAL_HEX(tx * 2, destination.X());
}

void testFilters()
{
    RUN_TEST(testFilter);
}