// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "BenchMark.h"
namespace glow
{
#if defined(NATIVE)
    const char *BenchMark::ENV = "Native";
#elif defined(MEGAATMEGA2560)
    const char *BenchMark::ENV = "MEGA";
#elif defined(ESP32)
    const char *BenchMark::ENV = "ESP32";
#elif defined(ESP32CAM)
    const char *BenchMark::ENV = "ESP32CAM";
#elif defined(SEEED_XIAO)
    const char *BenchMark::ENV = "XIAO";
#else
    const char *BenchMark::ENV = "OTHER";
#endif

    StaticJsonDocument<capacity> BenchMark::doc;
#ifndef ARDUINO // not ARDUINO
    char output[2048];
#endif // not ARDUINO

    const bool format_short = (sizeof(int) > 2);
    const char *fmt = (format_short) ? "%u" : "%lu";

    void BenchMark::Print()
    {
        doc["title"] = title();
        doc["begin"] = begin;
        doc["end"] = end;
        doc["elapsed"] = Duration();
#ifdef ARDUINO
        serializeJsonPretty(doc, Serial);
        Serial.println("");
#else
        serializeJsonPretty(doc, output, sizeof(output));
        printf("%s\n", output);
#endif
    }

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
}