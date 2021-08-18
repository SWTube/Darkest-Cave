/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include "stddef.h"

#include "BehaviorTreeNode.h"

export module Decorator;

export namespace cave
{
    class Decorator : public BehaviorTreeNode
    {
    public:
        Decorator()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetChild(NULL);
        }
        Decorator(const char* nodeName)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetChild(NULL);
        }
        virtual ~Decorator()
        {

        }
        BehaviorTreeNode* GetChild() const
        {
            return mChild;
        }
        void SetChild(BehaviorTreeNode* child)
        {
            mChild = child;
        }
        virtual void Clear() override
        {
            if (GetChild() != NULL)
            {
                GetChild()->Clear();
            }
            delete this;
        }
    private:
        BehaviorTreeNode* mChild;
    };
}