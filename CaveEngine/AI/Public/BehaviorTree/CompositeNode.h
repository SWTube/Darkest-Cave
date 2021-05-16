/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "Node.h"

namespace cave
{
    class CompositeNode: public Node
    {
    public:
        CompositeNode();
        CompositeNode(const char*);
        // Add child back or at position
        void AddChild(Node*);
        // return child node at given index
        Node* GetChild(int) const;
        // return children 
        std::vector<Node*>& GetChildren();
        // return children count
        int GetChildrenCount() const;
        // Clear node
        virtual void Clear() override;

    private:
        std::vector<Node*> mChildren;
        int mChildrenCount = 0;
    };
}
