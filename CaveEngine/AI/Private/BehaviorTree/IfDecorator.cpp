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
    IfDecorator::IfDecorator(const char* nodeName, std::function<bool(GameObject& gameObject)> condition)
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

    void IfDecorator::SetCondition(std::function<bool(GameObject& gameObject)> condition)
    {
        mCondition = condition;
    }
}
