// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"

class DefaultTrigger;
class Activity;

class Trigger
{
private:
    static DefaultTrigger defaultTrigger;

public:
    virtual bool Active(Activity* activity) = 0;
    static DefaultTrigger *Default();
};

class DefaultTrigger : public Trigger
{
public:
    virtual bool Active(Activity* activity) { return true; }
};

class Activity
{
protected:
    uint16_t interval = 500;
    uint64_t next = 0;
    Trigger *trigger = Trigger::Default();

protected:
    static uint64_t now;

public:
    Activity(uint16_t interval = 500) : interval(interval) {}
    ~Activity() {}

    inline void Interval(uint16_t i) { interval = i; }
    inline uint16_t Interval() { return interval; }
    inline void Attach(Trigger *a) { trigger = a; }

    virtual bool Pulse();
    virtual void Setup() {}
    virtual void Reset() {}
    virtual void Tick() = 0;

public:
    static void Cycle();
    static uint64_t Now();
};

