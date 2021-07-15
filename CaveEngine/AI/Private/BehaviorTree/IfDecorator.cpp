/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/IfDecorator.h"

namespace cave
{
    IfDecorator::IfDecorator()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetChild(NULL);
        SetCondition(NULL);
    }
    IfDecorator::IfDecorator(const char* nodeName, bool (*condition)())
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetChild(NULL);
        SetCondition(condition);
    }
    IfDecorator::~IfDecorator()
    {

    }

    void IfDecorator::SetCondition(bool (*condition)())
    {
        mCondition = condition;
    }
}
