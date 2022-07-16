// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include <ArduinoJson.h>

namespace glow
{
    void print_line(const char *message, bool crlf = false);

    const size_t capacity = JSON_OBJECT_SIZE(8);
    const size_t output_buffer_size = 2048;

    class Benchmark
    {
    public:
        const char *name;
        uint32_t begin;
        uint32_t end;

    public:
        // access
        inline const uint32_t Duration() { return end - begin; }
        inline const char *Name() { return name; }

        // implementation
        inline void Begin(const char *v)
        {
            name = v;
            begin = millis32();
        }

        inline void End()
        {
            end = millis32();
            Print();
        }

        void Print();
        char *TimeStamp();

    public:
        static void Setup()
        {
            buildTimeStamp();
        }

    public:
        static const char *Device() { return device; }
        static void buildTimeStamp();

    private:
        static const char *device;
        static time_t time_stamp;
        static StaticJsonDocument<capacity> doc;
    };
} // namespace glow
