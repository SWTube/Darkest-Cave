/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/Sequencer.h"

#ifdef __UNIX__
namespace cave
{
    Sequencer::Sequencer()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
    Sequencer::Sequencer(const char* nodeName)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
    }
    Sequencer::~Sequencer()
    {
        
    }
}
#endif
