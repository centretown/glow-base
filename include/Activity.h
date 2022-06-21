// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "Monitor.h"

namespace glow
{
    class Activity : public Monitor
    {
    protected:
        static uint64_t now;

    public:
        inline bool Pulse()
        {
            if (Ready())
            {
                Update();
                return true;
            }
            return false;
        }

        virtual void Update() = 0;

    public:
        static void Cycle();
        static uint64_t Now();
    };
}
