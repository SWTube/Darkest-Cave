/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#ifdef __WIN32__
import IfDecorator;
#else

#include <vector>
#include "Decorator.h"

namespace cave
{
    class IfDecorator : public Decorator
    {
    public:
        IfDecorator();
        IfDecorator(const char*, std::function<bool(GameObject&)>);
        ~IfDecorator();

        virtual bool Run(GameObject& gameObject) override
        {
            if (mCondition(gameObject))
            {
                return GetChild()->Run(gameObject);
            }
            return true;
        }

        void SetCondition(std::function<bool(GameObject&)>);
    private:
        std::function<bool(GameObject&)> mCondition;
    };
}

#endif