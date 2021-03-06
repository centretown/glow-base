// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    template <typename T>
    class Filter
    {
    private:
        Filter<T> *next = NULL;

    public:
        T &Apply(T &source, T &destination)
        {
            T worker(source);
            for (Filter<T> *current = this;
                 current != NULL;
                 current = current->next)
            {
                current->apply(worker, worker);
            }

            destination.Copy(worker);
            return destination;
        }

        inline void Link(Filter<T> *filter)
        {
            Filter<T> *link = this;
            for (Filter<T> *current = this;
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
            for (Filter<T> *current = this;
                 current != NULL;)
            {
                Filter<T> *hold = current->next;
                current->next = NULL;
                current = hold;
            }
        }

    private:
        virtual void apply(T &source, T &destination) = 0;
    };
}