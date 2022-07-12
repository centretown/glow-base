// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
namespace glow

{
    template <typename PUT, typename COMPARE, typename INCR, typename RESET>
    void Spin(PUT put, COMPARE compare, INCR increment, RESET reset)
    {
        for (reset(); compare(); increment())
        {
            put();
        }
    }
} // namespace glow
