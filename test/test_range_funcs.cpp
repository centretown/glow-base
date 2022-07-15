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

void testRangeFuncs()
{
    RUN_TEST(testSimpleSweeper);
    RUN_TEST(testRangeSpinner);
    RUN_TEST(testRangeReverseSpin);
    RUN_TEST(testRangeSpinMap);
    RUN_TEST(testRangeSpinMapReverse);
    RUN_TEST(testRangeOperators);
}