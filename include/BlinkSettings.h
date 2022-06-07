// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"

#ifdef FMDEVKIT
#define BLINK_PIN 2
#else
#define BLINK_PIN 13
#endif // ARDUINO_ARCH_ESP32

#ifdef SEEED_XIAO
#define BLINK_ON LOW
#define BLINK_OFF HIGH
#else
#define BLINK_ON HIGH
#define BLINK_OFF LOW
#endif // SEEED_XIAO

class BlinkSettings
{
private:
    uint8_t pin;
    uint8_t state;
    uint16_t on;
    uint16_t off;

public:
    BlinkSettings(
        uint8_t pin = BLINK_PIN,
        uint8_t state = BLINK_ON,
        uint16_t on = 100,
        uint16_t off = 500) : pin(pin), state(state), on(on), off(off) {}

    inline uint8_t Pin()
    {
        return pin;
    }

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
    inline void State(uint8_t val)
    {
        state = val;
    }
    inline uint8_t State()
    {
        return state;
    }
    inline uint8_t ToggleState()
    {
        state = (state == BLINK_ON)
                    ? BLINK_OFF
                    : BLINK_ON;
        return state;
    }

    ~BlinkSettings() {}
};
