/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <functional>
#include <vector>

#include "BehaviorTreeNode.h"
#include "Object/GameObject.h"

export module ActionNode;

export namespace cave
{
    class ActionNode : public BehaviorTreeNode
    {
    public:
        ActionNode()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetNodeFunction(NULL);
        }

        ActionNode(const char* nodeName, std::function<bool(GameObject&)> nodeFunction)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetNodeFunction(nodeFunction);
        }

        ~ActionNode()
        {

        }

        virtual bool Run(GameObject& gameObject) override
        {
            return mNodeFunction(gameObject);
        }

        void SetNodeFunction(std::function<bool(GameObject&)> nodeFunction)
        {
            mNodeFunction = nodeFunction;
        }

        virtual void Clear() override
        {
            delete this;
        }

    private:
        std::function<bool(GameObject&)> mNodeFunction;

    
    };

}