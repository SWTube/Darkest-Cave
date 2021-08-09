/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/RepeatDecorator.h"

#ifdef __UNIX__
namespace cave
{
    RepeatDecorator::RepeatDecorator()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetChild(NULL);
        SetCount(0);
    }
    RepeatDecorator::RepeatDecorator(const char* nodeName, uint32_t repeatCount)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetChild(NULL);
        SetCount(repeatCount);
    }
    RepeatDecorator::~RepeatDecorator()
    {

    }
    void RepeatDecorator::SetCount(uint32_t repeatCount)
    {
        mRepeatCount = repeatCount;
    }
}

#endif