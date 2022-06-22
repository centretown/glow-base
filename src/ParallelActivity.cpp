// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "ParallelActivity.h"

namespace glow
{
    bool ParallelActivity::Ready()
    {
        readyFlag = 0;
        for (size_t i = 0; i < Length(); i++)
        {
            uint32_t flag = 1 << i;
            if (activities[i]->Ready())
            {
                readyFlag |= flag;
            }
        }
        return (readyFlag != 0);
    }

    void ParallelActivity::Update()
    {
        for (size_t i = 0; i < Length(); i++)
        {
            uint32_t flag = 1 << i;
            if (readyFlag & flag)
            {
                activities[i]->Update();
            }
        }
    }

    bool ParallelActivity::Done()
    {
        for (size_t i = 0; i < Length(); i++)
        {
            if (!activities[i]->Done())
            {
                return false;
            }
        }
        return true;
    }
}
