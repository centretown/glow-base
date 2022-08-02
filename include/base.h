// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#ifdef ARDUINO

#include <Arduino.h>
#include <time.h>

#else

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1

uint64_t millis();
uint64_t micros();
void set_millis_rate(uint16_t r);
#endif

const uint32_t clocks_sec = CLOCKS_PER_SEC;
const uint32_t clocks_ms = clocks_sec / 1000;

extern uint16_t millis_rate;
extern uint64_t millis_now;
extern bool real_time;

void set_real_time(bool v);
typedef uint32_t feature_base;
uint32_t millis32();
uint32_t micros32();
