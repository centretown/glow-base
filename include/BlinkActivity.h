// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "ActivitySettings.h"

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
public:
    uint8_t pin;
    uint8_t state;
    uint16_t on;
    uint16_t off;
    BlinkSettings(
        uint8_t pin = BLINK_PIN,
        uint8_t state = BLINK_ON,
        uint16_t on = 250,
        uint16_t off = 1000) : pin(pin), state(state), on(on), off(off) {}

    ~BlinkSettings() {}
};

class BlinkActivity : public ActivitySettings<BlinkSettings>
{
private:
    /* data */
public:
    BlinkActivity(BlinkSettings &settings);
    ~BlinkActivity() {}

    virtual void Setup();
    virtual void Tick();

private:
    inline void updateInterval()
    {
        SetInterval((settings.state == BLINK_ON)
                        ? settings.on
                        : settings.off);
    }
    inline void toggleState()
    {
        settings.state = (settings.state == BLINK_ON)
                             ? BLINK_OFF
                             : BLINK_ON;
    }
};
