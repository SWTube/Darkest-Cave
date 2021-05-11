/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/RootNode.h"

namespace cave
{
    RootNode::RootNode()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
    RootNode::RootNode(const char* nodeName)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
}
