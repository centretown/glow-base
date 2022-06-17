// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "base.h"

#ifndef ARDUINO

static uint16_t millis_rate = 10;
static uint64_t millis_now = 0;

void set_millis_rate(uint16_t r)
{
    millis_rate = r;
}

uint64_t millis()
{
    auto now = millis_now;
    millis_now += millis_rate;
    return now;
}

#endif // not ARDUINO
