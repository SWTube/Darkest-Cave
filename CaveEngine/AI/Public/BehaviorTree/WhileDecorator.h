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
        WhileDecorator(const char*, std::function<bool(GameObject&)>);
        ~WhileDecorator();

        virtual bool Run(GameObject& gameObject) override
        {
            while (mCondition)
            {
                GetChild()->Run(gameObject);
            }
            return true;
        }

        void SetCondition(std::function<bool(GameObject&)>);
    private:
        std::function<bool(GameObject&)> mCondition;
    };
}
