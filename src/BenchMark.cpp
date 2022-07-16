// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "BenchMark.h"
namespace glow
{
#if defined(NATIVE)
    const char *BenchMark::device = "Native";
#elif defined(MEGAATMEGA2560)
    const char *BenchMark::device = "MEGA";
#elif defined(ESP32)
    const char *BenchMark::device = "ESP32";
#elif defined(ESP32CAM)
    const char *BenchMark::device = "ESP32CAM";
#elif defined(SEEED_XIAO)
    const char *BenchMark::device = "XIAO";
#else
    const char *BenchMark::device = "OTHER";
#endif

    StaticJsonDocument<capacity> BenchMark::doc;
#ifndef ARDUINO // not ARDUINO
    char output[2048];
#endif // not ARDUINO

    const bool format_short = (sizeof(int) > 2);
    const char *fmt = (format_short) ? "%u" : "%lu";

    void BenchMark::Print()
    {
        doc["device"] = device;
        doc["test"] = name;
        doc["duration"] = Duration();
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