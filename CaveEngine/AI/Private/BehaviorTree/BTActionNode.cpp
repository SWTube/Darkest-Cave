/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/BTActionNode.h"

namespace cave
{
    BTActionNode::BTActionNode()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetNodeFunction(NULL);
    }
    BTActionNode::BTActionNode(const char* nodeName, bool (*nodeFunction)())
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetNodeFunction(nodeFunction);
    }
    void BTActionNode::SetNodeFunction(bool (*nodeFunction)()) 
    {
        mNodeFunction = nodeFunction;
    }
}
