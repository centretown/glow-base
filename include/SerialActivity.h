// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "CompoundActivity.h"

namespace glow
{
    class SerialActivity : public CompoundActivity
    {
    protected:
        uint8_t current = 0;

    public:
        SerialActivity(size_t length)
            : CompoundActivity(length) {}
        ~SerialActivity() {}

        inline uint8_t Current() { return current; }
        inline void Current(uint8_t v) { current = v; }

        virtual bool Ready();
        virtual bool Done();
        virtual void Update()
        {
            activities[current]->Update();
        }
    };
}
