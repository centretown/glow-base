// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "CompoundActivity.h"

class SelectActivity : public CompoundActivity
{
protected:
    uint8_t selection = 0;

public:
    SelectActivity(size_t length)
        : CompoundActivity(length) {}
    ~SelectActivity() {}

    inline uint8_t Selected() { return selection; }
    inline void Select(uint8_t val)
    {
        if (val < count)
        {
            selection = val;
        }
    }
    virtual bool Pulse();
};
