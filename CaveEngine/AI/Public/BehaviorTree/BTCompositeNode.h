/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "BTNode.h"

namespace cave
{
    class BTCompositeNode: public BTNode
    {
    public:
        BTCompositeNode();
        BTCompositeNode(const char*);
        // Add child back or at position
        void AddChild(BTNode*, int = -1);
        // return child node at given index
        BTNode* GetChild(int) const;
        // return children 
        std::vector<BTNode*>& GetChildren();
        // return children count
        int GetChildrenCount() const;

    private:
        std::vector<BTNode*> mChildren;
        int mChildrenCount = 0;
    };
}
