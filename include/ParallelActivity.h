// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "base.h"
#include "CompoundActivity.h"

class ParallelActivity : public CompoundActivity
{
public:
    ParallelActivity(size_t length)
        : CompoundActivity(length) {}
    ~ParallelActivity() {}

    // virtual bool Ready();
    // virtual bool Done();
    virtual void Update();
};
