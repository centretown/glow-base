// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

class Feature
{
public:
    static const char *U32_FORMAT;

public:
    Feature() {}
    virtual ~Feature() {}
    virtual const char *Label() = 0;
    virtual feature_base Get() = 0;
    virtual feature_base High() = 0;
    virtual feature_base Low() = 0;
    virtual feature_base Filtered() = 0;
    virtual void Set(feature_base v) = 0;
    virtual char *Format(char *buffer, size_t bufLen) = 0;
};

// const char *Feature::U32_FORMAT = (sizeof(int) > 16) ? "%u" : "%lu";
