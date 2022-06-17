// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "BlinkActivity.h"

void BlinkActivity::Update()
{
#ifdef ARDUINO
    digitalWrite(blink->Pin(), blink->State());
#else
    const char *text = (blink->State() == BLINK_ON) ? "OFF" : "ON";
    printf("pin:%u %s\n", blink->Pin(), text);
#endif
    blink->ToggleState();
}
