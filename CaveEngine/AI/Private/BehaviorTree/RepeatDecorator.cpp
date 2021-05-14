/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/RepeatDecorator.h"

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
    RepeatDecorator::RepeatDecorator(const char* nodeName, int repeatCount)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetChild(NULL);
        SetCount(repeatCount);
    }
    void RepeatDecorator::SetCount(int repeatCount)
    {
        mRepeatCount = repeatCount;
    }
}
