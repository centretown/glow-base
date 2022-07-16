// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include <ArduinoJson.h>

namespace glow
{
    void print_line(const char *message, bool crlf = false);

    const int capacity = JSON_OBJECT_SIZE(4);

    class BenchMark
    {
    public:
        const char *name;
        char text[32];
        uint32_t begin;
        uint32_t end;

        static const char *ENV;

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
        const char *title()
        {
            snprintf(text, sizeof(text), "%s:%s", ENV, name);
            return text;
        }

    private:
        static StaticJsonDocument<capacity> doc;
    };
} // namespace glow
