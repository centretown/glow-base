// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "base.h"

#ifndef ARDUINO

static bool real_time = false;
static uint16_t millis_rate = 10;
static uint64_t millis_now = 0;
const uint64_t CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

void set_millis_rate(uint16_t r)
{
    millis_rate = r;
}

void set_real_time(bool v)
{
    real_time = v;
}

uint64_t millis()
{
    if (real_time)
    {
        clock_t lms = clock();
        lms /= CLOCKS_PER_MS;
        lms *= millis_rate;
        return static_cast<uint64_t>(lms);
    }
    auto now = millis_now;
    millis_now += millis_rate;
    return now;
}

#endif // not ARDUINO
