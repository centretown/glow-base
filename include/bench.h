// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

void print_line(const char *message, bool crlf = false);
void format_buffer(char *buffer, size_t bufsize,
                   uint32_t value);
void print_millis(uint32_t, bool crlf = false);
uint32_t print_elapsed(uint32_t, uint32_t);
