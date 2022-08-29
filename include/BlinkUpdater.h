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
        BlinkState state;
        uint16_t on;
        uint16_t off;

    public:
        BlinkUpdater(PinDevice *pin,
                     BlinkState state = BLINK_OFF,
                     uint16_t on = 500,
                     uint16_t off = 500)
            : pin(pin), state(state), on(on), off(off) {}

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
        inline uint32_t Update()
        {
            pin->Write(state);
            // toggle
            state = (state == BLINK_OFF) ? BLINK_ON : BLINK_OFF;
            return (state == BLINK_ON) ? on : off;
        }

        inline void Apply(uint8_t s, int16_t i)
        {
            if (state != s)
            {
                state = (s == BLINK_OFF) ? BLINK_ON : BLINK_OFF;
            }
        }
    };
}