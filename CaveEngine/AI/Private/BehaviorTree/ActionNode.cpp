/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/ActionNode.h"

#ifdef __UNIX__
namespace cave
{
    ActionNode::ActionNode()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetNodeFunction(NULL);
    }
    ActionNode::ActionNode(const char* nodeName, std::function<bool(GameObject&)> nodeFunction)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetNodeFunction(nodeFunction);
    }
    ActionNode::~ActionNode()
    {

    }
    void ActionNode::SetNodeFunction(std::function<bool(GameObject&)> nodeFunction)
    {
        mNodeFunction = nodeFunction;
    }
    void ActionNode::Clear()
    {
        delete this;
    }
} // namespace cave
#endif