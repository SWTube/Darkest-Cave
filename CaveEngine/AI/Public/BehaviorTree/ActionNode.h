/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "Node.h"

namespace cave
{
    class ActionNode : public Node
    {
    public:
        ActionNode();
        ActionNode(const char*, void (*)());

        virtual bool Invoke() override 
        {
            mNodeFunction();
            return true;
        }

        void SetNodeFunction(void (*)());
        virtual void Clear() override;
    private:
        void (*mNodeFunction)();
    };
}