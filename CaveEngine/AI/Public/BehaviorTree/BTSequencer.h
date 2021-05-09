/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "BTCompositeNode.h"

namespace cave
{
    class BTSequencer : public BTCompositeNode
    {
    public:
        BTSequencer();
        BTSequencer(const char*);

        virtual bool Invoke() override {
            for (const auto& child : GetChildren()) {
                if (!child->Invoke()) {
                    return false;
                }
            }
            return true;
        }
    private:

    };
}
