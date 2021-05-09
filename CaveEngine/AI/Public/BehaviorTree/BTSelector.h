/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "BTCompositeNode.h"

namespace cave
{
    class BTSelector: public BTCompositeNode
    {
    public:
        BTSelector();
        BTSelector(const char*);

        virtual bool Invoke() override {
            for (const auto& child : GetChildren()) {
                if (child->Invoke()) {
                    return true;
                }
            }
            return false;
        }
    private:
        
    };
}
