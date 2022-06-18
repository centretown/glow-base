// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "PinDevice.h"

namespace glow
{
    void PinDevice::Setup()
    {
#ifdef ARDUINO
        pinMode(pin, mode);
#endif
    }
}
