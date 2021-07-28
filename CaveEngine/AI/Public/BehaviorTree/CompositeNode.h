/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "BehaviorTreeNode.h"

namespace cave
{
    class CompositeNode: public BehaviorTreeNode
    {
    public:
        CompositeNode();
        CompositeNode(const char*);
        ~CompositeNode();

        // Add child back or at position
        void AddChild(BehaviorTreeNode*);
        // return child node at given index
        BehaviorTreeNode* GetChild(int) const;
        // return children 
        std::vector<BehaviorTreeNode*>& GetChildren();
        // return children count
        int GetChildrenCount() const;
        // Clear node
        virtual void Clear() override;

    private:
        std::vector<BehaviorTreeNode*> mChildren;
        int mChildrenCount = 0;
    };
}
