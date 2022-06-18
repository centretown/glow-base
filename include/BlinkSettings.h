// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "PinDevice.h"

class BlinkSettings
{
    PinDevice *pin;
    BlinkState state;
    uint16_t on;
    uint16_t off;

public:
    BlinkSettings(PinDevice *pin,
                  BlinkState state = BLINK_OFF,
                  uint16_t on = 500,
                  uint16_t off = 500)
        : pin(pin), state(state), on(on), off(off) {}
    ~BlinkSettings() {}

    // inline PinDevice *Pin() { return pin; }

    inline void On(uint16_t val)
    {
        on = val;
    }
    inline uint16_t On()
    {
        return on;
    }
    inline void Off(uint16_t val)
    {
        off = val;
    }
    inline uint16_t Off()
    {
        return off;
    }
    inline void State(BlinkState val)
    {
        state = val;
    }
    inline BlinkState State()
    {
        return state;
    }
    inline void ToggleState()
    {
        pin->Write(state);
        state = (state == BLINK_ON) ? BLINK_OFF : BLINK_ON;
    }
};
