// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "SerialActivity.h"

namespace glow
{
    bool SerialActivity::Done()
    {
        Activity *activity;
        bool done = false;
        size_t next = current;
        do
        {
            activity = activities[next];
            done = activity->Done();
            if (!done)
            {
                break;
            }

            next++;
            if (next >= Length())
            {
                next = 0;
            }
        } while (next != current);

        if (next != current)
        {
            current = next;
            Setup();
        }
        return done;
    }

}