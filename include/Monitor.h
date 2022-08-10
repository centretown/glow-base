// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
namespace glow
{
    class Monitor
    {
    protected:
        uint16_t pulseWidth = 20;
        uint32_t next = 0;
        static uint64_t now;

    public:
        inline void Reset()
        {
            next = 0;
        }

        virtual bool Done() { return false; }

        virtual bool Ready()
        {
            auto now = Monitor::Now32();
            if (now >= next)
            {
                next = now + pulseWidth;
                return true;
            }
            return false;
        }

        inline uint16_t PulseWidth() const { return pulseWidth; }
        inline uint16_t PulseWidth(uint16_t v) { return pulseWidth = v; }

    public:
        static void Cycle() { now = millis(); }
        static uint64_t Now() { return now; }
        static uint32_t Now32() { return (uint32_t)(now & 0xffffffff); }
    };
}
