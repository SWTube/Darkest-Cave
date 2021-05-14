/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "Decorator.h"

namespace cave
{
    class WhileDecorator : public Decorator
    {
    public:
        WhileDecorator();
        WhileDecorator(const char*, bool (*)());

        virtual bool Invoke() override 
        {
            while (mCondition)
            {
                GetChild()->Invoke();
            }
            return false;
        }

        void SetCondition(bool (*)());
    private:
        bool (*mCondition)();
    };
}
