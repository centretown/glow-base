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

void testRangeSpinner()
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

    range.ReverseSpin(putter, mapper, (uint8_t)0);
    TEST_ASSERT_EQUAL(range.Begin() * 2, putter.index);
    TEST_ASSERT_EQUAL(range.Begin() * 2, mapper.index);
    TEST_ASSERT_EQUAL(0, putter.value);

    range.Resize(999, 22);
    TEST_ASSERT_EQUAL(range.Begin(), 22);
    TEST_ASSERT_EQUAL(range.End(), 999);

    range.ReverseSpin(putter, mapper, (uint8_t)0);
    TEST_ASSERT_EQUAL(range.Begin() * 2, putter.index);
    TEST_ASSERT_EQUAL(range.Begin() * 2, mapper.index);
    TEST_ASSERT_EQUAL(0, putter.value);
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

void testRangeOperators()
{
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
    TEST_ASSERT_EQUAL(51, source.Begin());
    TEST_ASSERT_EQUAL(91, source.End());

    ++source;
    TEST_ASSERT_EQUAL(52, source.Begin());
    TEST_ASSERT_EQUAL(92, source.End());

    --source;
    TEST_ASSERT_EQUAL(51, source.Begin());
    TEST_ASSERT_EQUAL(91, source.End());

    source = 0;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(0, source.End());

    ++source;
    TEST_ASSERT_EQUAL(1, source.Begin());
    TEST_ASSERT_EQUAL(1, source.End());
    TEST_ASSERT_EQUAL(0, source.Length());

    source = Range(10, 100);
    TEST_ASSERT_EQUAL(10, source.Begin());
    TEST_ASSERT_EQUAL(100, source.End());

    target = source + 1;
    TEST_ASSERT_EQUAL(11, target.Begin());
    TEST_ASSERT_EQUAL(101, target.End());

    target = source + 5;
    TEST_ASSERT_EQUAL(15, target.Begin());
    TEST_ASSERT_EQUAL(105, target.End());

    target = source - 5;
    TEST_ASSERT_EQUAL(5, target.Begin());
    TEST_ASSERT_EQUAL(95, target.End());

    target += 5;
    TEST_ASSERT_EQUAL(10, source.Begin());
    TEST_ASSERT_EQUAL(100, source.End());

    target -= 5;
    TEST_ASSERT_EQUAL(5, target.Begin());
    TEST_ASSERT_EQUAL(95, target.End());

    target -= 5;
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(90, target.End());

    // begin less than zero not allowed no effect
    target -= 5;
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(90, target.End());

    // begin less than zero not allowed no effect
    --target;
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(90, target.End());

    // begin less than zero not allowed no effect
    source = target - 1;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(90, source.End());

    ++target;
    TEST_ASSERT_EQUAL(1, target.Begin());
    TEST_ASSERT_EQUAL(91, target.End());

    source = Range(0xff00, 0xffff);
    TEST_ASSERT_EQUAL_HEX(0xff00, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xffff, source.End());

    // end at max no effect
    ++source;
    TEST_ASSERT_EQUAL_HEX(0xff00, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xffff, source.End());

    // end at max no effect
    source += 1;
    TEST_ASSERT_EQUAL_HEX(0xff00, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xffff, source.End());

    // end at max no effect
    target = source + 1;
    TEST_ASSERT_EQUAL_HEX(0xff00, target.Begin());
    TEST_ASSERT_EQUAL_HEX(0xffff, target.End());

    source = Range(25, 50);
    TEST_ASSERT_EQUAL(25, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());

    source >>= 1;
    TEST_ASSERT_EQUAL(26, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());

    source >>= 2;
    TEST_ASSERT_EQUAL(28, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());

    source >>= 20;
    TEST_ASSERT_EQUAL(48, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());

    // no effect begin > end
    source >>= 3;
    TEST_ASSERT_EQUAL(48, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());

    // ok begin == end
    source >>= 2;
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    TEST_ASSERT_EQUAL(0, source.Length());

    source = Range(0xff00, 0xffff);
    source >>= 0xff;
    TEST_ASSERT_EQUAL(0xffff, source.Begin());
    TEST_ASSERT_EQUAL(0xffff, source.End());

    source.Resize(6, 50);
    source <<= 1;
    TEST_ASSERT_EQUAL(6, source.Begin());
    TEST_ASSERT_EQUAL(49, source.End());

    source <<= 42;
    TEST_ASSERT_EQUAL(6, source.Begin());
    TEST_ASSERT_EQUAL(7, source.End());

    // no effect begin > end
    source <<= 2;
    TEST_ASSERT_EQUAL(6, source.Begin());
    TEST_ASSERT_EQUAL(7, source.End());

    // ok equal
    source <<= 1;
    TEST_ASSERT_EQUAL(6, source.Begin());
    TEST_ASSERT_EQUAL(6, source.End());

    // no effect end < begin
    source <<= 1;
    TEST_ASSERT_EQUAL(6, source.Begin());
    TEST_ASSERT_EQUAL(6, source.End());

    source.Resize(0, 5);
    // no effect (new end) > (previous end)
    source <<= 6;
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(5, source.End());

    source.Resize(50, 60);
    target = source >> 1;
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(60, source.End());
    TEST_ASSERT_EQUAL(51, target.Begin());
    TEST_ASSERT_EQUAL(60, target.End());

    target = source >> 5;
    TEST_ASSERT_EQUAL(55, target.Begin());
    TEST_ASSERT_EQUAL(60, target.End());

    target = source >> 10;
    TEST_ASSERT_EQUAL(60, target.Begin());
    TEST_ASSERT_EQUAL(60, target.End());

    // no effect begin > end
    target = source >> 11;
    TEST_ASSERT_EQUAL(50, target.Begin());
    TEST_ASSERT_EQUAL(60, target.End());
    TEST_ASSERT_EQUAL(50, source.Begin());
    TEST_ASSERT_EQUAL(60, source.End());

    source.Resize(0xfff0, 0xffff);
    target = source >> 0x0f;
    TEST_ASSERT_EQUAL_HEX(0xffff, target.Begin());
    TEST_ASSERT_EQUAL_HEX(0xffff, target.End());
    TEST_ASSERT_EQUAL_HEX(0xfff0, source.Begin());
    TEST_ASSERT_EQUAL_HEX(0xffff, source.End());

    // no effect new begin < previous
    target = source >> 0x10;
    TEST_ASSERT_EQUAL(0xfff0, target.Begin());
    TEST_ASSERT_EQUAL(0xffff, target.End());

    source.Resize(0, 50);
    TEST_ASSERT_EQUAL(0, source.Begin());
    TEST_ASSERT_EQUAL(50, source.End());
    target = source << 1;
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(49, target.End());

    target = source << 50;
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(0, target.End());

    // no effect end > previous
    target = source << 51;
    TEST_ASSERT_EQUAL(0, target.Begin());
    TEST_ASSERT_EQUAL(50, target.End());

    source.Resize(322, 111);
    TEST_ASSERT_EQUAL(111, source.Begin());
    TEST_ASSERT_EQUAL(322, source.End());
    target = source << 200;
    TEST_ASSERT_EQUAL(111, target.Begin());
    TEST_ASSERT_EQUAL(122, target.End());

    target = source << 211;
    TEST_ASSERT_EQUAL(111, target.Begin());
    TEST_ASSERT_EQUAL(111, target.End());

    // no effect end < begin
    target = source << 212;
    TEST_ASSERT_EQUAL(111, source.Begin());
    TEST_ASSERT_EQUAL(322, source.End());

    TEST_ASSERT_EQUAL(111, target.Begin());
    TEST_ASSERT_EQUAL(322, target.End());
}

void testRangeFuncs()
{
    RUN_TEST(testSimpleSweeper);
    RUN_TEST(testRangeSpinner);
    RUN_TEST(testRangeReverseSpin);
    RUN_TEST(testRangeSpinMap);
    RUN_TEST(testRangeSpinMapReverse);
    RUN_TEST(testRangeOperators);
}