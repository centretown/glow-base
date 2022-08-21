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
        State state = 0;
        Source *source = NULL;
        Target *target = NULL;

    public:
        Activity(Source *src = NULL, Target *tar = NULL)
        {
            source = src;
            target = tar;
        }

        void Attach(Source *src, Target *tar)
        {
            source = src;
            target = tar;
        }

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
                if (source != NULL)
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
            }
            return false;
        }
    };

}
