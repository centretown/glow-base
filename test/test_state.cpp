// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>

#include "State.h"
#include "Benchmark.h"
#include "Updater.h"

using glow::print_line;
using glow::Source;
using glow::State;
using glow::Target;

class X : public Source
{
public:
    State state;
    uint32_t Update()
    {
        state.status++;
        state.position++;
        return state.pack;
    }
};

class Y : public Target
{
public:
    State state;
    uint32_t Update(uint16_t s, uint16_t p)
    {
        state.status = s;
        state.position = p;
        return state.pack;
    }
};

void testStateHandler()
{
    char buffer[32];
    State stateA;
    TEST_ASSERT_EQUAL(0, stateA.Status());
    TEST_ASSERT_EQUAL(0, stateA.Position());
    TEST_ASSERT_EQUAL(0, stateA.Pack());

    State stateB(1, 100);
    TEST_ASSERT_EQUAL(1, stateB.Status());
    TEST_ASSERT_EQUAL(100, stateB.Position());
    TEST_ASSERT_EQUAL_HEX(0x00010064, stateB.Pack());

    TEST_ASSERT(stateA != stateB);
    // stateA.Pack(stateB.Pack());
    stateA = stateB;
    TEST_ASSERT(stateA == stateB);
    TEST_ASSERT_EQUAL(1, stateA.Status());
    TEST_ASSERT_EQUAL(100, stateA.Position());
    TEST_ASSERT_EQUAL_HEX(0x00010064, stateA.Pack());

    stateA(55, 99);
    TEST_ASSERT(stateA != stateB.Pack());
    stateB = stateA.Pack();
    TEST_ASSERT(stateA == stateB.Pack());
}

void testState()
{
    RUN_TEST(testStateHandler);
}