// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "Activator.h"

DefaultActivator Activator::defaultActivator;
DefaultActivator *Activator::Default() { return &defaultActivator; }
