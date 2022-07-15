// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "bench.h"

#ifndef PIO_UNIT_TESTING // NO PIO_UNIT_TESTING

void print_line(const char *message, bool crlf) {}
void format_buffer(char *buffer, size_t bufsize,
                   uint32_t value) {}
void print_millis(uint32_t, bool crlf) {}
uint32_t print_elapsed(uint32_t, uint32_t) { return 0; }

#else // PIO_UNIT_TESTING

void print_line(const char *message, bool crlf)
{
#ifdef ARDUINO
    if (crlf)
    {
        Serial.println(message);
    }
    else
    {
        Serial.print(message);
    }
#else  // NO ARDUINO
    if (crlf)
    {
        printf("%s\n", message);
    }
    else
    {
        printf("%s", message);
    }
#endif // ARDUINO
}

void format_buffer(char *buffer, const size_t buffer_size, const uint32_t value)
{
    const bool format_short = (sizeof(int) > 2);
    const char *fmt = (format_short) ? "%u" : "%lu";
    snprintf(buffer, buffer_size, fmt, value);
}

void print_millis(uint32_t ms, bool crlf)
{
    char buffer[16] = {0};
    format_buffer(buffer, sizeof(buffer), ms);
    print_line(buffer, crlf);
}

uint32_t print_elapsed(uint32_t begin, uint32_t end)
{
    uint32_t elapsed = end - begin;
    print_line("BEGIN: ");
    print_millis(begin);
    print_line("ms END: ");
    print_millis(end);
    print_line("ms ELAPSED: ");
    print_millis(elapsed);
    print_line("ms", true);
    return elapsed;
}

#endif // PIO_UNIT_TESTING
