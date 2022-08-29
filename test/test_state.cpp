// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>

#include "State.h"
#include "Benchmark.h"
#include "Source.h"
#include "Target.h"
#include "Monitor.h"
#include "Activity.h"

using glow::Activity;
using glow::Monitor;
using glow::print_line;
using glow::Source;
using glow::State;
using glow::Target;

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
    uint32_t update(uint16_t s, uint16_t p)
    {
        state.status = s;
        state.position = p;
        return state.pack;
    }
};

void testTargetLink()
{
    X source;
    Y targeta, targetb, targetc;
    Activity activity(&source, &targeta);

    State state = targeta.state;
    TEST_ASSERT_EQUAL(0, state.status);
    TEST_ASSERT_EQUAL(0, state.position);

    activity.PulseWidth(0);
    Monitor::Cycle();

    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(1, state.status);
    TEST_ASSERT_EQUAL(1, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(0, state.status);
    TEST_ASSERT_EQUAL(0, state.position);

    targeta.Link(&targetb);
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(2, state.status);
    TEST_ASSERT_EQUAL(2, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(2, state.status);
    TEST_ASSERT_EQUAL(2, state.position);

    targeta.UnLink();
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(3, state.status);
    TEST_ASSERT_EQUAL(3, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(2, state.status);
    TEST_ASSERT_EQUAL(2, state.position);

    targeta.Link(&targetc);
    targeta.Link(&targetb);
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(4, state.status);
    TEST_ASSERT_EQUAL(4, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(4, state.status);
    TEST_ASSERT_EQUAL(4, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(4, state.status);
    TEST_ASSERT_EQUAL(4, state.position);

    targeta.UnLink();
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(5, state.status);
    TEST_ASSERT_EQUAL(5, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(4, state.status);
    TEST_ASSERT_EQUAL(4, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(4, state.status);
    TEST_ASSERT_EQUAL(4, state.position);

    X sourceB;
    Activity activityB(&sourceB, &targetb);
    activityB.PulseWidth(0);
    targetb.Link(&targetc);

    activity.Link(&activityB);
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(6, state.status);
    TEST_ASSERT_EQUAL(6, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(1, state.status);
    TEST_ASSERT_EQUAL(1, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(1, state.status);
    TEST_ASSERT_EQUAL(1, state.position);

    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(7, state.status);
    TEST_ASSERT_EQUAL(7, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(2, state.status);
    TEST_ASSERT_EQUAL(2, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(2, state.status);
    TEST_ASSERT_EQUAL(2, state.position);

    targetb.UnLink();
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(8, state.status);
    TEST_ASSERT_EQUAL(8, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(3, state.status);
    TEST_ASSERT_EQUAL(3, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(2, state.status);
    TEST_ASSERT_EQUAL(2, state.position);

    activity.UnLink();
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(9, state.status);
    TEST_ASSERT_EQUAL(9, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(3, state.status);
    TEST_ASSERT_EQUAL(3, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(2, state.status);
    TEST_ASSERT_EQUAL(2, state.position);

    targeta.Link(&targetb);
    activityB.AttachTarget(&targetc);
    activityB.Link(&activity);

    activityB.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(10, state.status);
    TEST_ASSERT_EQUAL(10, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(10, state.status);
    TEST_ASSERT_EQUAL(10, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(4, state.status);
    TEST_ASSERT_EQUAL(4, state.position);
}

void testState()
{
    RUN_TEST(testStateHandler);
    RUN_TEST(testTargetLink);
}