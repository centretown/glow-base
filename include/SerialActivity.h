// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "CompoundActivity.h"

class SerialActivity : public CompoundActivity
{
protected:
    uint8_t current = 0;

public:
    SerialActivity(size_t length)
        : CompoundActivity(length) {}
    ~SerialActivity() {}

    inline uint8_t Current() { return current; }

    virtual bool Pulse();
};
