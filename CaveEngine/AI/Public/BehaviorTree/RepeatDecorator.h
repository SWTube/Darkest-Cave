/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#ifdef __WIN32__
import RepeatDecorator;
#else

#include <vector>
#include "Decorator.h"

namespace cave
{
    class RepeatDecorator : public Decorator
    {
    public:
        RepeatDecorator();
        RepeatDecorator(const char*, uint32_t);
        ~RepeatDecorator();

        virtual bool Run(GameObject& gameObject) override
        {
            uint32_t i;
            for(i = 0; i < mRepeatCount; i++)
            {
                GetChild()->Run(gameObject);
            }
            if(i == mRepeatCount)
                return true;
            return false;
        }

        void SetCount(uint32_t);
    private:
        uint32_t mRepeatCount;
    };
}

#endif