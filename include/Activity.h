// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
namespace glow
{
    class Activity
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

        virtual void Setup() {}

        virtual bool Ready() = 0;
        virtual void Update() = 0;
        virtual bool Done() = 0;

    public:
        static void Cycle();
        static uint64_t Now();
    };
}
