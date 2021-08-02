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
        ~RepeatDecorator();

        virtual bool Run(GameObject& gameObject) override
        {
            int i;
            for(i = 0; i < mRepeatCount; i++)
            {
                GetChild()->Run(gameObject);
            }
            if(i == mRepeatCount)
                return true;
            return false;
        }

        void SetCount(int);
    private:
        int mRepeatCount;
    };
}
