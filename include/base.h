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
#define INPUT 0
#define OUTPUT 1
uint64_t millis();
void set_millis_rate(uint16_t r);
void set_real_time(bool v);
#endif

typedef uint32_t feature_base;
const char *FMT32 = (sizeof(int) > 16) ? "%u" : "%lu";
