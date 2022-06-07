// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"

#ifdef ESP32
#define BLINK_PIN 2
#elif ESP32CAM
#define BLINK_PIN 33
#else
#define BLINK_PIN 13
#endif

#ifdef SEEED_XIAO
typedef enum : uint8_t
{
    BLINK_ON = LOW,
    BLINK_OFF = HIGH
} BlinkState;
#else
typedef enum : uint8_t
{
    BLINK_ON = HIGH,
    BLINK_OFF = LOW
} BlinkState;
#endif // SEEED_XIAO

class BlinkSettings
{
private:
    uint8_t pin;
    BlinkState state;
    uint16_t on;
    uint16_t off;

public:
    BlinkSettings(
        uint8_t pin = BLINK_PIN,
        BlinkState state = BLINK_ON,
        uint16_t on = 500,
        uint16_t off = 250) : pin(pin), state(state), on(on), off(off) {}

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
    inline void State(BlinkState val)
    {
        state = val;
    }
    inline BlinkState State()
    {
        return state;
    }
    inline BlinkState ToggleState()
    {
        state = (state == BLINK_ON)
                    ? BLINK_OFF
                    : BLINK_ON;
        return state;
    }

    ~BlinkSettings() {}
};
