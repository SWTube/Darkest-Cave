/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/WhileDecorator.h"

namespace cave
{
    WhileDecorator::WhileDecorator()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetChild(NULL);
        SetCondition(NULL);
    }
    WhileDecorator::WhileDecorator(const char* nodeName, bool condition)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetChild(NULL);
        SetCondition(condition);
    }
    WhileDecorator::~WhileDecorator()
    {

    }
    void WhileDecorator::SetCondition(bool condition)
    {
        mCondition = condition;
    }

}
