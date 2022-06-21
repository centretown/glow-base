// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Monitor.h"

namespace glow
{
    uint64_t Monitor::now = millis();
    uint64_t Monitor::Now() { return now; }
    void Monitor::Cycle() { now = millis(); }
}