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

    time_t BenchMark::time_stamp = 0;

    char *BenchMark::TimeStamp()
    {

#if defined(BUILD_TIMESTAMP)

#if defined(NATIVE)
        time_t time_stamp = BUILD_TIMESTAMP;
#else
        // 1970/01/01 00:00:00
        static struct tm base_tm;
        base_tm.tm_sec = 0;
        base_tm.tm_min = 0;
        base_tm.tm_hour = 0;

#ifdef MEGAATMEGA2560
        base_tm.tm_mday = 0;
#else
        base_tm.tm_mday = 1;
#endif

        base_tm.tm_mon = 0;
        base_tm.tm_year = 70;
        time_t base_time = mktime(&base_tm);
        time_t diff_time = difftime(0, base_time);
        time_t time_stamp = BUILD_TIMESTAMP - diff_time;
#endif // NATIVE

#endif // BUILD_TIMESTAMP

        static char buffer[22] = {0};
        struct tm *timeinfo = gmtime(&time_stamp);
        strftime(buffer, sizeof(buffer),
                 "%Y/%m/%d %H:%M:%S",
                 timeinfo);
        return buffer;
    }

    StaticJsonDocument<capacity> BenchMark::doc;

#ifndef ARDUINO // not ARDUINO
    char output[output_buffer_size];
#endif // not ARDUINO

    const char *fmt = (sizeof(int) > 2) ? "%u" : "%lu";

    void BenchMark::Print()
    {
        doc["device"] = device;
        doc["test"] = name;
        doc["time"] = TimeStamp();
        doc["duration"] = Duration();

#ifdef ARDUINO // ARDUINO
        serializeJsonPretty(doc, Serial);
        Serial.println("");
#else
        serializeJsonPretty(doc, output, sizeof(output));
        printf("%s\n", output);
#endif // ARDUINO
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