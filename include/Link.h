// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    template <typename LINK>
    void LinkTo(LINK *link, LINK *attachment)
    {
        for (LINK *current = link;
             current != NULL;
             current = current->next)
        {
            if (attachment == current)
            {
                return;
            }
            link = current;
        }
        link->next = attachment;
    }

    template <typename LINK>
    void UnLinkFrom(LINK *link)
    {
        for (LINK *current = link;
             current != NULL;)
        {
            LINK *hold = current->next;
            current->next = NULL;
            current = hold;
        }
    }
}
