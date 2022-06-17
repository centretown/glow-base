// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"

class Activity
{
protected:
    static uint64_t now;

public:
    bool Pulse();

    virtual void Reset() {}
    virtual void Setup() {}

    virtual bool Ready() { return true; }
    virtual bool Done() { return false; }
    
    virtual void Update() = 0;

public:
    static void Cycle();
    static uint64_t Now();
};
