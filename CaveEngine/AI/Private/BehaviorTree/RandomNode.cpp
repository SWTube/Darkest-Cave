/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/RandomNode.h"

#ifdef __UNIX__
namespace cave
{
    RandomNode::RandomNode()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetMaxRandomCount(0);
    }
    RandomNode::RandomNode(const char* nodeName, uint32_t maxRandomCount)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetMaxRandomCount(maxRandomCount);
    }
    RandomNode::~RandomNode()
    {

    }
    void RandomNode::SetMaxRandomCount(uint32_t maxRandomCount)
    {
        mMaxRandomCount = maxRandomCount;
    }
}
#endif