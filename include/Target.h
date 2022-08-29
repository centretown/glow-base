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
        uint32_t Update(uint16_t status, uint16_t position)
        {
            State updated(status, position);
            Target *current = this;
            while (current != NULL)
            {
                if (current->state != updated)
                {
                    current->update(status, position);
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

    private:
        virtual uint32_t update(uint16_t status, uint16_t position) = 0;
    };

} // namespace glow
