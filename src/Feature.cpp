// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Feature.h"

namespace glow
{
    const char *Feature::U32_FORMAT = (sizeof(int) > 16) ? "%u" : "%lu";
}
