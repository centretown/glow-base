// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "CompoundActivity.h"

class SelectActivity : public CompoundActivity
{
protected:
    size_t select = 0;

public:
    SelectActivity(size_t maximum)
        : CompoundActivity(maximum) {}
    ~SelectActivity() {}

    inline uint8_t Select() { return select; }
    inline void Select(size_t v)
    {
        if (v < length)
        {
            select = v;
        }
    }

    virtual bool Ready()
    {
        return activities[select]->Ready();
    }
    virtual bool Done()
    {
        return activities[select]->Done();
    }
    virtual void Update()
    {
        activities[select]->Update();
    }
};
