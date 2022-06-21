// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "CompoundActivity.h"

namespace glow
{
    class SerialActivity : public CompoundActivity
    {
    protected:
        size_t current = 0;

    public:
        SerialActivity(size_t length)
            : CompoundActivity(length) {}
        ~SerialActivity() {}

        inline size_t Current() { return current; }

        virtual void Reset()
        {
            activities[current]->Reset();
        }
        virtual bool Ready();
        virtual void Update();
        virtual bool Done();

    private:
        size_t findNext(size_t next);
        size_t nextActivity(size_t next);
    };
}
