// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "wait.h"

void wait(uint32_t ms)
{
#ifdef ARDUINO
    delay(ms);
#else
    uint32_t begin = millis32();
    uint32_t end = begin + ms;
    while (millis32() < end)
        ;
#endif
}
