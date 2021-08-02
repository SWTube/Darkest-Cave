/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "BehaviorTreeNode.h"

namespace cave
{
    class ActionNode : public BehaviorTreeNode
    {
    public:
        ActionNode();
        ActionNode(const char*, std::function<void(GameObject&)>);
        ~ActionNode();

        virtual bool Run(GameObject& gameObject) override
        {
            mNodeFunction(gameObject);
            return true;
        }

        void SetNodeFunction(std::function<void(GameObject&)>);
        virtual void Clear() override;
    private:
        std::function<void(GameObject&)> mNodeFunction;
    };
}
