// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "SerialActivity.h"

bool SerialActivity::Done()
{
    bool done = false;
    size_t i = current;
    do
    {
        done = activities[i]->Done();
        if (!done)
        {
            break;
        }

        i++;
        if (i >= Length())
        {
            i = 0;
        }
    } while (i != current);

    current = i;
    return done;
}

bool SerialActivity::Ready()
{
    return activities[current]->Ready();
}