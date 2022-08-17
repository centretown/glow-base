// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"
#include "State.h"
#include "Updater.h"

namespace glow
{
    class Activity : public Monitor
    {
    private:
        State state;

    protected:
        UpdateSource *source = NULL;
        UpdateTarget *target = NULL;

    public:
        Activity(UpdateSource *source, UpdateTarget *target = NULL)
            : source(source),
              target(target) {}

        void AttachSource(UpdateSource *src)
        {
            source = src;
        }

        void AttachTarget(UpdateTarget *tar)
        {
            target = tar;
        }

        inline bool Pulse()
        {
            if (Ready())
            {
                uint32_t current = source->Update();
                if (state.pack != current)
                {
                    state(current);
                    if (target != NULL)
                    {
                        target->Update(state.Status(), state.Position());
                    }
                    else
                    {
                        PulseWidth(state.position);
                    }
                }
                return true;
            }
            return false;
        }
    };

}
