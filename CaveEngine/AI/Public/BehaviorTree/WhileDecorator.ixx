/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <functional>
#include <vector>

#include "Decorator.h"
#include "Object/GameObject.h"

export module WhileDecorator;

export namespace cave
{
    class WhileDecorator : public Decorator
    {
    public:
        WhileDecorator()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetChild(NULL);
            SetCondition(NULL);
        }
        WhileDecorator(const char* nodeName, std::function<bool(GameObject&)> condition)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetChild(NULL);
            SetCondition(condition);
        }
        ~WhileDecorator()
        {

        }

        virtual bool Run(GameObject& gameObject) override
        {
            while (mCondition)
            {
                GetChild()->Run(gameObject);
            }
            return true;
        }

        void SetCondition(std::function<bool(GameObject&)> condition)
        {
            mCondition = condition;
        }
    private:
        std::function<bool(GameObject&)> mCondition;
    };

}