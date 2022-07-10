// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

template <typename COMPARE, typename PUT, typename INCR, typename RESET>
void Spin(COMPARE compare, PUT put, INCR increment, RESET reset)
{
    while (compare())
    {
        put();
        increment();
    }
    reset();
}
