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
    State stateA;
    TEST_ASSERT_EQUAL(0, stateA.id);
    TEST_ASSERT_EQUAL(0, stateA.position);
    TEST_ASSERT_EQUAL(0, stateA.pack);

    State stateB(0, 1, 100);
    TEST_ASSERT_EQUAL(1, stateB.id);
    TEST_ASSERT_EQUAL(100, stateB.position);

    TEST_ASSERT(stateA != stateB);
    stateA = stateB;
    TEST_ASSERT(stateA == stateB);
    TEST_ASSERT_EQUAL(1, stateA.id);
    TEST_ASSERT_EQUAL(100, stateA.position);

    stateA(0, 55, 99);
    TEST_ASSERT(stateA != stateB.pack);
    stateB = stateA.pack;
    TEST_ASSERT(stateA == stateB.pack);
}

class X : public Source
{
public:
    State state;
    uint32_t Update()
    {
        state.id++;
        state.position++;
        return state.pack;
    }
};

class Y : public Target
{
public:
    State state;
    uint32_t UpdateTarget(uint32_t pack)
    {
        state = pack;
        return state.pack;
    }
};

void testTargetLink()
{
    X source;
    Y targeta, targetb, targetc;
    Activity activity(&source, &targeta);

    State state = targeta.state;
    TEST_ASSERT_EQUAL(0, state.id);
    TEST_ASSERT_EQUAL(0, state.position);

    activity.PulseWidth(0);
    Monitor::Cycle();

    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(1, state.id);
    TEST_ASSERT_EQUAL(1, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(0, state.id);
    TEST_ASSERT_EQUAL(0, state.position);

    targeta.Link(&targetb);
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(2, state.id);
    TEST_ASSERT_EQUAL(2, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(2, state.id);
    TEST_ASSERT_EQUAL(2, state.position);

    targeta.UnLink();
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(3, state.id);
    TEST_ASSERT_EQUAL(3, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(2, state.id);
    TEST_ASSERT_EQUAL(2, state.position);

    targeta.Link(&targetc);
    targeta.Link(&targetb);
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(4, state.id);
    TEST_ASSERT_EQUAL(4, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(4, state.id);
    TEST_ASSERT_EQUAL(4, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(4, state.id);
    TEST_ASSERT_EQUAL(4, state.position);

    targeta.UnLink();
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(5, state.id);
    TEST_ASSERT_EQUAL(5, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(4, state.id);
    TEST_ASSERT_EQUAL(4, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(4, state.id);
    TEST_ASSERT_EQUAL(4, state.position);

    X sourceB;
    Activity activityB(&sourceB, &targetb);
    activityB.PulseWidth(0);
    targetb.Link(&targetc);

    activity.Link(&activityB);
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(6, state.id);
    TEST_ASSERT_EQUAL(6, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(1, state.id);
    TEST_ASSERT_EQUAL(1, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(1, state.id);
    TEST_ASSERT_EQUAL(1, state.position);

    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(7, state.id);
    TEST_ASSERT_EQUAL(7, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(2, state.id);
    TEST_ASSERT_EQUAL(2, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(2, state.id);
    TEST_ASSERT_EQUAL(2, state.position);

    targetb.UnLink();
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(8, state.id);
    TEST_ASSERT_EQUAL(8, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(3, state.id);
    TEST_ASSERT_EQUAL(3, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(2, state.id);
    TEST_ASSERT_EQUAL(2, state.position);

    activity.UnLink();
    activity.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(9, state.id);
    TEST_ASSERT_EQUAL(9, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(3, state.id);
    TEST_ASSERT_EQUAL(3, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(2, state.id);
    TEST_ASSERT_EQUAL(2, state.position);

    targeta.Link(&targetb);
    activityB.AttachTarget(&targetc);
    activityB.Link(&activity);

    activityB.Pulse();
    state = targeta.state;
    TEST_ASSERT_EQUAL(10, state.id);
    TEST_ASSERT_EQUAL(10, state.position);

    state = targetb.state;
    TEST_ASSERT_EQUAL(10, state.id);
    TEST_ASSERT_EQUAL(10, state.position);

    state = targetc.state;
    TEST_ASSERT_EQUAL(4, state.id);
    TEST_ASSERT_EQUAL(4, state.position);
}

void testState()
{
    RUN_TEST(testStateHandler);
    RUN_TEST(testTargetLink);
}