// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

class DefaultActivator;

class Activator
{
private:
    static DefaultActivator defaultActivator;

public:
    virtual bool Active() = 0;
    static DefaultActivator *Default();
};

class DefaultActivator : public Activator
{
public:
    virtual bool Active() { return true; }
};
