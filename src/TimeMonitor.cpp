// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "TimeMonitor.h"

TimeMonitor::TimeMonitor(uint64_t end, uint64_t begin)
    : end(end), begin(begin) {}

TimeMonitor::TimeMonitor(uint64_t end) : end(end)
{
    begin = Activity::Now();
}

TimeMonitor::TimeMonitor()
{
    begin = Activity::Now();
    end = begin + MONITOR_DEFAULT_DURATION;
}

bool TimeMonitor::Active(Activity *activity)
{
    auto now = Activity::Now();
    return (now >= begin) && (now < end);
}

bool TimeMonitor::Done(Activity *activity)
{
    auto now = Activity::Now();
    return (now > end);
}
