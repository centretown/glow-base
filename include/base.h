// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#define U32_FORMAT "%lu"
#else
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
uint64_t millis();
#define U32_FORMAT "%u"
#endif

typedef uint32_t feature_base;
