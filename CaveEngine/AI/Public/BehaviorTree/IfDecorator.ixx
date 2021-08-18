/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <functional>
#include <vector>

#include "Decorator.h"

export module IfDecorator;

export namespace cave
{
    class IfDecorator : public Decorator
    {
    public:
        IfDecorator()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetChild(NULL);
            SetCondition(NULL);
        }
        IfDecorator(const char* nodeName, std::function<bool(GameObject& gameObject)> condition)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetChild(NULL);
            SetCondition(condition);
        }
        ~IfDecorator()
        {

        }

        virtual bool Run(GameObject& gameObject) override
        {
            if (mCondition(gameObject))
            {
                return GetChild()->Run(gameObject);
            }
            return true;
        }

        void SetCondition(std::function<bool(GameObject& gameObject)> condition)
        {
            mCondition = condition;
        }
    private:
        std::function<bool(GameObject&)> mCondition;
    };
}