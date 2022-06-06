// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#ifdef ARDUINO
#include <Arduino.h>
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
uint64_t millis();
void set_millis_rate(uint16_t r);
#endif

typedef uint32_t feature_base;
