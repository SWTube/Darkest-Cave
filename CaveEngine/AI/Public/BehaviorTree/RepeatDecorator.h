/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "Decorator.h"

namespace cave
{
    class RepeatDecorator : public Decorator
    {
    public:
        RepeatDecorator();
        RepeatDecorator(const char*, int);

        virtual bool Invoke() override 
        {
            for(int i = 0; i < mRepeatCount; i++)
            {
                GetChild()->Invoke();
            }
            return true;
        }

        void SetCount(int);
    private:
        int mRepeatCount;
    };
}
