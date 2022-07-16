// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include <ArduinoJson.h>

void print_line(const char *message, bool crlf = false);

const int capacity = JSON_OBJECT_SIZE(4);

class Bench
{
public:
    const char *text;
    uint32_t begin;
    uint32_t end;

public:
    Bench(const char *text) : text(text) {}

    void Print();

private:
    uint32_t elapsed() { return end - begin; }
    const char *title()
    {
        return text;
    }

private:
    static StaticJsonDocument<capacity> doc;
};
