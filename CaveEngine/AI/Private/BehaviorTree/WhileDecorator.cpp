/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/WhileDecorator.h"

#ifdef __UNIX__
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
    WhileDecorator::WhileDecorator(const char* nodeName, std::function<bool(GameObject&)> condition)
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
    void WhileDecorator::SetCondition(std::function<bool(GameObject&)> condition)
    {
        mCondition = condition;
    }
}
#endif

