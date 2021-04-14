/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <iostream>
#include <string>

namespace cave
{
    class BTNode
    {
        public:
            BTNode();
            BTNode(std::string);

            // Get node name
            std::string GetNodeName() const;
            // Get tree depth
            int GetTreeDepth() const;
            // Set node name
            void SetNodeName(std::string);
            // Set parent node
            void SetParentNode(BTNode*);
            // Set tree depth
            void SetTreeDepth(int);
        private:
    	    BTNode* mParentNode = NULL;
            std::string mNodeName = "";
            int mTreeDepth = 0;
    };
}