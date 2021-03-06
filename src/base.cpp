// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "base.h"

uint16_t millis_rate = 10;
uint64_t millis_now = 0;
bool real_time = false;

uint32_t millis32()
{
    uint64_t lms = millis();
    return (uint32_t)(lms & 0xffffffff);
}

uint32_t micros32()
{
    uint64_t lms = micros();
    return (uint32_t)(lms & 0xffffffff);
}

void set_real_time(bool v)
{
    real_time = v;
    return;
}

#ifndef ARDUINO // not ARDUINO

void set_millis_rate(uint16_t r)
{
    millis_rate = r;
}

uint64_t micros()
{
    return clock();
}

uint64_t millis()
{
    if (real_time)
    {
        clock_t lms = clock();
        lms /= clocks_ms;
        return lms;
    }
    auto now = millis_now;
    millis_now += millis_rate;
    return now;
}

#endif // not ARDUINO
