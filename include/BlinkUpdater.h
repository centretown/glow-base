// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Source.h"
#include "PinDevice.h"

namespace glow
{
    class BlinkUpdater : public Source
    {
    public:
        PinDevice *pin;
        BlinkState blinkState;
        uint16_t on;
        uint16_t off;

    public:
        BlinkUpdater(PinDevice *pin,
                     BlinkState blinkState = BLINK_OFF,
                     uint16_t on = 500,
                     uint16_t off = 500)
            : pin(pin), blinkState(blinkState), on(on), off(off) {}

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
            blinkState = val;
        }
        inline BlinkState State()
        {
            return blinkState;
        }
        inline uint32_t Update()
        {
            pin->Write(blinkState);
            // toggle
            blinkState = (blinkState == BLINK_OFF) ? BLINK_ON : BLINK_OFF;
            return (blinkState == BLINK_ON) ? on : off;
        }
    };
}