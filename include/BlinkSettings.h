// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"

#if defined(ESP32)
#define BLINK_PIN 2
#else
#if defined(ESP32CAM)
#define BLINK_PIN 33
#else
#define BLINK_PIN 13
#endif
#endif

#ifdef SEEED_XIAO // BlinkState
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
#endif // BlinkState

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
        uint16_t off = 500)
        : pin(pin), state(state), on(on), off(off) {}
    ~BlinkSettings() {}

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
    inline void ToggleState()
    {
        state = (state == BLINK_ON) ? BLINK_OFF : BLINK_ON;
    }
    void Setup()
    {
#ifdef ARDUINO
        pinMode(Pin(), OUTPUT);
#endif
    }
};
