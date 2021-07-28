/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "BehaviorTreeNode.h"

namespace cave
{
    class Decorator : public BehaviorTreeNode
    {
    public:
        Decorator();
        Decorator(const char*);
        virtual ~Decorator();

        // return child node at given index
        BehaviorTreeNode* GetChild() const;
        // set child node
        void SetChild(BehaviorTreeNode*);
        // clear node
        virtual void Clear() override;
    private:
        BehaviorTreeNode* mChild;
    };
}
