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

namespace glow
{
    class PinDevice
    {
    private:
        uint8_t pin;
        uint8_t mode;

    public:
        PinDevice(uint8_t pin = BLINK_PIN, uint8_t mode = OUTPUT)
            : pin(pin), mode(mode) {}
        ~PinDevice() {}

        inline uint8_t Pin() { return pin; }
        inline uint8_t Mode() { return mode; }

        inline void Write(BlinkState state)
        {
#ifdef ARDUINO
            digitalWrite(pin, state);
#else
            const char *text = (state == BLINK_ON) ? "OFF" : "ON";
            printf("pin:%u %s\n", pin, text);
#endif
        }

        void Setup();
    };
}
