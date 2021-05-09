/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/BTRootNode.h"

namespace cave
{
    BTRootNode::BTRootNode()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
    BTRootNode::BTRootNode(const char* nodeName)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
}
