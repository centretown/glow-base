// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "State.h"
#include "Link.h"

namespace glow
{
    class Target
    {
    public:
        Target *next = NULL;
        State state;

    public:
        uint32_t Update(uint32_t pack)
        {
            State updated(pack);
            Target *current = this;
            while (current != NULL)
            {
                if (current->state != updated)
                {
                    current->state = updated;
                    current->UpdateTarget(pack);
                }
                current = current->next;
            }
            return updated.pack;
        }

        inline void Link(Target *target)
        {
            LinkTo(this, target);
        }

        inline void UnLink()
        {
            UnLinkFrom(this);
        }

        virtual uint32_t UpdateTarget(uint32_t pack) = 0;
    };

} // namespace glow
