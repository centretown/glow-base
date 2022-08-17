// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Range.h"
#include "State.h"

namespace glow
{
    class Filter
    {
    private:
        Filter *next = NULL;
        Range range;
        State state;

    public:
        void Apply(uint8_t state, uint16_t index)
        {
            Filter *current = this;
            for (uint8_t i = 0; i < state; i++)
            {
                if (current->next == NULL)
                {
                    break;
                }
                current = current->next;
            }
  
            current->apply(state, index);
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