/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "Node.h"

namespace cave
{
    class Decorator : public Node
    {
    public:
        Decorator();
        Decorator(const char*);

        // return child node at given index
        Node* GetChild() const;
        // set child node
        void SetChild(Node*);
    private:
        Node* mChild;
    };
}
