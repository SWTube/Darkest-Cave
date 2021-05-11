/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/Selector.h"

namespace cave
{
    Selector::Selector()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
    Selector::Selector(const char* nodeName)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
}
