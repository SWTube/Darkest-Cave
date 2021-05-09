/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <iostream>

namespace cave
{
    class BTNode
    {
        public:
            BTNode();
            BTNode(const char*);

            virtual bool Invoke() = 0;

            // Get node name
            const char* GetNodeName() const;
            // Get tree depth
            int GetTreeDepth() const;
            // Set node name
            void SetNodeName(const char*);
            // Set parent node
            void SetParentNode(BTNode*);
            // Set tree depth
            void SetTreeDepth(int);
        private:
    	    BTNode* mParentNode = NULL;
            const char* mNodeName = "";
            int mTreeDepth = 0;
    };
}