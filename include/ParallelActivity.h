// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "base.h"
#include "CompoundActivity.h"

namespace glow
{
    class ParallelActivity : public CompoundActivity
    {
    private:
        uint16_t readyFlag = 0;

    public:
        ParallelActivity(size_t length)
            : CompoundActivity(length) {}
        ~ParallelActivity() {}

        virtual void Reset() {}
        virtual bool Ready();
        virtual bool Done();
        virtual void Update();
    };
}