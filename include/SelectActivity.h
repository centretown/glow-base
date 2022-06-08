// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "CompoundActivity.h"

template <class T>
class SelectActivity : public CompoundActivity
{
protected:
    T settings;
    uint8_t selection = 0;

public:
    SelectActivity(
        size_t length, T &settings) : CompoundActivity(length), settings(settings) {}
    ~SelectActivity() {}

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
