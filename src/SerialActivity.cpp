// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "SerialActivity.h"

namespace glow
{
    bool SerialActivity::Done()
    {
        return activities[current]->Done();
    }

    bool SerialActivity::Ready()
    {
        return activities[current]->Ready();
    }

    void SerialActivity::Update()
    {
        Activity *activity = activities[current];
        activity->Update();
        if (activity->Done())
        {
            if (findNext(current))
            {
                Setup();
            }
        }
    }

    size_t SerialActivity::findNext(size_t next)
    {
        Activity *activity;
        bool done = false;
        next = nextActivity(next);
        while (next != current)
        {
            activity = activities[next];
            done = activity->Done();
            if (!done)
            {
                break;
            }

            next = nextActivity(next);
        }
        current = next;
        return (done == false);
    }
    size_t SerialActivity::nextActivity(size_t next)
    {
        next++;
        if (next >= Length())
        {
            next = 0;
        }
        return next;
    }
}