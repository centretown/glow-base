// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "Activity.h"

namespace glow
{
    class CompoundActivity : public Activity
    {
    protected:
        size_t maximum = 0;
        size_t length = 0;
        Activity **activities = NULL;

    public:
        CompoundActivity(size_t maximum);
        ~CompoundActivity();

        inline size_t Maximum() { return maximum; }
        inline size_t Length() { return length; }
        void Add(Activity *activity);

        virtual void Setup();
        virtual void Reset();

        // virtual bool Ready() { return true; }
        // virtual bool Done() { return false; }
        // virtual void Update() = 0;
    };
}
