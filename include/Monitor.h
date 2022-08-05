// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
namespace glow
{
    class Monitor
    {
    protected:
        static uint64_t now;

    public:
        virtual void Reset() = 0;
        virtual bool Ready() = 0;
        virtual bool Done() = 0;

    public:
        static void Cycle() { now = millis(); }
        static uint64_t Now() { return now; }
        static uint32_t Now32() { return (uint32_t)(now & 0xffffffff); }
    };
}
