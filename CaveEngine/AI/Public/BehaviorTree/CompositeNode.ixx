/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <vector>

#include "BehaviorTreeNode.h"

export module CompositeNode;

export namespace cave
{
    class CompositeNode : public BehaviorTreeNode
    {
    public:
        CompositeNode()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
        }
        CompositeNode(const char* nodeName)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
        }
        ~CompositeNode()
        {
            // delete[] mChildren;
        }
        void AddChild(BehaviorTreeNode* node)
        {
            mChildren.push_back(node);
            mChildrenCount = mChildren.size();

            node->SetParentNode(this);
            node->SetTreeDepth(this->GetTreeDepth() + 1);
        }

        BehaviorTreeNode* GetChild(uint32_t childNum) const
        {
            return mChildren[childNum];
        }

        std::vector<BehaviorTreeNode*>& GetChildren()
        {
            return mChildren;
        }

        uint32_t GetChildrenCount() const
        {
            return mChildrenCount;
        }

        virtual void Clear() override
        {
            for (const auto& node : GetChildren())
            {
                if (node != NULL)
                    node->Clear();
            }
            delete this;
        }

    private:
        std::vector<BehaviorTreeNode*> mChildren;
        uint32_t mChildrenCount = 0;
    };

}