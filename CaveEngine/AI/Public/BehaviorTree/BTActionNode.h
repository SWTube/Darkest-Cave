/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "BTNode.h"

namespace cave
{
    class BTActionNode : public BTNode
    {
    public:
        BTActionNode();
        BTActionNode(const char*, bool (*)());

        virtual bool Invoke() override {
            return mNodeFunction();
        }

        void SetNodeFunction(bool (*)());
    private:
        bool (*mNodeFunction)();
    };
}
