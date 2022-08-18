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
        Source *source = NULL;
        Target *target = NULL;

    public:
        Activity(Source *source, Target *target = NULL)
            : source(source),
              target(target) {}

        void AttachSource(Source *src)
        {
            source = src;
        }

        void AttachTarget(Target *tar)
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
