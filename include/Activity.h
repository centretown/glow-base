// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"

class Activity;

class ActivityMonitor
{
private:
    static ActivityMonitor simple;

public:
    virtual bool Active(Activity *activity) { return true;}
    virtual bool Dead(Activity *activity) { return false; }
    static ActivityMonitor *Simple();
};

class Activity
{
protected:
    uint16_t interval = 500;
    uint64_t next = 0;
    ActivityMonitor *monitor = ActivityMonitor::Simple();

protected:
    static uint64_t now;

public:
    Activity(uint16_t interval = 500) : interval(interval) {}
    ~Activity() {}

    inline void Interval(uint16_t i) { interval = i; }
    inline uint16_t Interval() { return interval; }
    inline uint64_t Next() { return next; }
    inline void Monitor(ActivityMonitor *a) { monitor = a; }

    inline bool Active() { return monitor->Active(this); }
    inline bool Dead() { return monitor->Dead(this); }

    virtual bool Pulse();
    virtual void Setup() {}
    virtual void Reset() {}
    virtual void Tick() = 0;

public:
    static void Cycle();
    static uint64_t Now();
};
