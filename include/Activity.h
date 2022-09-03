// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Monitor.h"
#include "State.h"
#include "Source.h"
#include "Target.h"
#include "Link.h"

namespace glow
{
    class Activity : public Monitor
    {
    private:
        State state = 0;
        Source *source = NULL;
        Target *target = NULL;

    public:
        Activity *next = NULL;

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
            bool result = false;
            Activity *current = this;
            while (current != NULL)
            {
                bool b = current->pulse();
                if (result == false)
                    result = b;
                current = current->next;
            }
            return result;
        }

        inline bool pulse()
        {
            if (Ready())
            {
                if (source != NULL)
                {
                    uint32_t updated = source->Update();
                    if (state.pack != updated)
                    {
                        state = updated;
                        if (target != NULL)
                        {
                            updated = target->Update(state.pack);
                        }
                    }
                    return true;
                }
            }
            return false;
        }

        inline void Link(Activity *activity)
        {
            LinkTo(this, activity);
        }

        inline void UnLink()
        {
            UnLinkFrom(this);
        }
    };
}
