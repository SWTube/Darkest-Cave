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
        ActionNode(const char*, std::function<bool(GameObject&)>);
        ~ActionNode();

        virtual bool Run(GameObject& gameObject) override
        {
            return mNodeFunction(gameObject);
        }

        void SetNodeFunction(std::function<bool(GameObject&)>);
        virtual void Clear() override;
    private:
        std::function<bool(GameObject&)> mNodeFunction;
    };
}
