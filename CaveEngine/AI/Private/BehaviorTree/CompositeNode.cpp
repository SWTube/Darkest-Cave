/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/CompositeNode.h"

namespace cave
{
    CompositeNode::CompositeNode()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
    CompositeNode::CompositeNode(const char* nodeName)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
    void CompositeNode::AddChild(Node* node)
    {
        mChildren.push_back(node);
        mChildrenCount = mChildren.size();

        node->SetParentNode(this);
        node->SetTreeDepth(this->GetTreeDepth() + 1);
    }

    Node* CompositeNode::GetChild(int childNum) const
    {
        return mChildren[childNum];
    }

    std::vector<Node*>& CompositeNode::GetChildren()
    {
        return mChildren;
    }

    int CompositeNode::GetChildrenCount() const
    {
        return mChildrenCount;
    }

    void CompositeNode::Clear()
    {
        for (const auto& node : GetChildren())
        {
            if(node != NULL)
                node->Clear();
        }
        delete this;
    }
}