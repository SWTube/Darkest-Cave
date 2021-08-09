/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <vector>

#include "BehaviorTreeNode.h"
#include "CompositeNode.h"
#include "Object/GameObject.h"

export module Selector;

export namespace cave
{
    class Selector : public CompositeNode
    {
    public:
        Selector()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
        }
        Selector(const char* nodeName)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
        }
        ~Selector()
        {

        }

        virtual bool Run(GameObject& gameObject) override {
            for (const auto& child : GetChildren()) {
                if (child->Run(gameObject)) {
                    return true;
                }
            }
            return false;
        }
    private:
    };

}