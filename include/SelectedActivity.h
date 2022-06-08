// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "CompoundActivity.h"

template <class T>
class SelectedActivity : public CompoundActivity<T>
{
protected:
    uint8_t selection = 0;

public:
    SelectedActivity(
        size_t length, T &settings) : CompoundActivity<T>(length, settings) {}
    ~SelectedActivity() {}

    inline uint8_t Selected()
    {
        return selection;
    }

    inline void Select(uint8_t val)
    {
        if (val < count)
        {
            selection = val;
        }
    }

    virtual bool Pulse(uint64_t &now)
    {
        if (selection < count)
        {
            return activities[selection]->Pulse(now);
        }
        return false;
    }
};
