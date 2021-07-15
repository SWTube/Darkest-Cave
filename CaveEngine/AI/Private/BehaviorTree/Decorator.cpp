/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/Decorator.h"

namespace cave
{
    Decorator::Decorator()
    {
        SetNodeName("");
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetChild(NULL);
    }
    Decorator::Decorator(const char* nodeName)
    {
        SetNodeName(nodeName);
        SetParentNode(NULL);
        SetTreeDepth(0);
        SetChild(NULL);
    }
    Decorator::~Decorator()
    {

    }
    Node* Decorator::GetChild() const
    {
        return mChild;
    }
    void Decorator::SetChild(Node* child)
    {
        mChild = child;
    }
    void Decorator::Clear()
    {
        if (GetChild() != NULL)
        {
            GetChild()->Clear();
        }
        delete this;
    }
}
