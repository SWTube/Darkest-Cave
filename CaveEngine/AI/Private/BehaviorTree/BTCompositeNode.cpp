/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/BTCompositeNode.h"

namespace cave
{
    BTCompositeNode::BTCompositeNode()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
    BTCompositeNode::BTCompositeNode(const char* nodeName)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
    void BTCompositeNode::AddChild(BTNode* node, int addPos)
    {
        if (addPos == -1) 
        {
            mChildren.push_back(node);
        }
        else if(addPos >= 0 && addPos <= mChildrenCount) 
        {
            mChildren.insert(mChildren.begin() + addPos, node);
        }
        mChildrenCount = mChildren.size();
    }
    void BTCompositeNode::DeleteChild(int startPos, int endPos)
    {
        if (endPos == -1) {
            mChildren.erase(mChildren.begin() + startPos, mChildren.begin() + startPos + 1);
        }
        else {
            mChildren.erase(mChildren.begin() + startPos, mChildren.begin() + endPos);
        }
        mChildrenCount = mChildren.size();
    }

    BTNode* BTCompositeNode::GetChild(int childNum) const
    {
        return mChildren[childNum];
    }

    std::vector<BTNode*>& BTCompositeNode::GetChildren()
    {
        return mChildren;
    }

    int BTCompositeNode::GetChildrenCount() const
    {
        return mChildrenCount;
    }
}
