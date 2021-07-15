/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <iostream>

namespace cave
{
    class Node
    {
        public:
            Node();
            Node(const char*);
            virtual ~Node();

            virtual bool Run() = 0;

            // Get node name
            const char* GetNodeName() const;
            // Get tree depth
            int GetTreeDepth() const;
            // Set node name
            void SetNodeName(const char*);
            // Set parent node
            void SetParentNode(Node*);
            // Set tree depth
            void SetTreeDepth(int);
            // Clear tree
            virtual void Clear();
        private:
    	    Node* mParentNode = NULL;
            const char* mNodeName = "";
            int mTreeDepth = 0;
    };
}