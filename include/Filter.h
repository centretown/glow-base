// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    class Filter
    {
    private:
        Filter *next = NULL;

    public:
        void Apply(uint8_t state, uint16_t index)
        {
            for (Filter *current = this;
                 current != NULL;
                 current = current->next)
            {
                current->apply(state, index);
            }
        }

        inline void Link(Filter *filter)
        {
            Filter *link = this;
            for (Filter *current = this;
                 current != NULL;
                 current = current->next)
            {
                // cant't link filter more than once
                if (filter == current)
                {
                    return;
                }
                link = current;
            }
            link->next = filter;
        }

        inline void UnLink()
        {
            for (Filter *current = this;
                 current != NULL;)
            {
                Filter *hold = current->next;
                current->next = NULL;
                current = hold;
            }
        }

        virtual void Setup(){};

    private:
        virtual void apply(uint8_t state, uint16_t index){};
    };
}