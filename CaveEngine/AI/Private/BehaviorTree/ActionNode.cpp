/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/ActionNode.h"

namespace cave
{
    ActionNode::ActionNode()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetNodeFunction(NULL);
    }
    ActionNode::ActionNode(const char* nodeName, void (*nodeFunction)())
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetNodeFunction(nodeFunction);
    }
    void ActionNode::SetNodeFunction(void (*nodeFunction)())
    {
        mNodeFunction = nodeFunction;
    }
}
