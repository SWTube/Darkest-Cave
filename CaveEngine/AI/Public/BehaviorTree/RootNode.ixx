/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <vector>

#include "Sequencer.h"

export module RootNode;

export namespace cave
{
    class RootNode : public Sequencer
    {
    public:
        RootNode()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
        }
        RootNode(const char* nodeName)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
        }
        ~RootNode()
        {

        }
    private:
    };

}