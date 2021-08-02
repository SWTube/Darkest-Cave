/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <iostream>
#include <functional>
#include "Object/GameObject.h"

namespace cave
{
    class BehaviorTreeNode
    {
        public:
            BehaviorTreeNode();
            BehaviorTreeNode(const char*);
            virtual ~BehaviorTreeNode();

            virtual bool Run(GameObject& gameObject) = 0;

            // Get node name
            const char* GetNodeName() const;
            // Get tree depth
            int GetTreeDepth() const;
            // Set node name
            void SetNodeName(const char*);
            // Set parent node
            void SetParentNode(BehaviorTreeNode*);
            // Set tree depth
            void SetTreeDepth(int);
            // Clear tree
            virtual void Clear();
        private:
            BehaviorTreeNode* mParentNode = NULL;
            const char* mNodeName = "";
            int mTreeDepth = 0;
    };
}