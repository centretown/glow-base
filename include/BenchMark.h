// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include <ArduinoJson.h>

namespace glow
{
    void print_line(const char *message, bool crlf = false);

    const int capacity = JSON_OBJECT_SIZE(3);

    class BenchMark
    {
    public:
        const char *name;
        uint32_t begin;
        uint32_t end;

        static const char *device;

    public:
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

        inline uint32_t Duration() { return end - begin; }

    private:
        static StaticJsonDocument<capacity> doc;
    };
} // namespace glow
