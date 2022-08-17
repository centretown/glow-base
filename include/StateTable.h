// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "State.h"
#include "StateHandler.h"
#include "Range.h"

namespace glow
{
    template <typename SOURCE, typename TARGET>
    struct Entry
    {
        SOURCE *source;
        TARGET *target;
        StateHandler handler;

        void Handle()
        {
            handler.Handle(*source, *target);
        }
    };

    const size_t entry_depth = 16;
    Entry<> entries[entry_depth];

} // namespace glow
