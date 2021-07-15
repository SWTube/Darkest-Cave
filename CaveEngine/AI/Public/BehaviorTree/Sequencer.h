/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include "CompositeNode.h"

namespace cave
{
    class Sequencer : public CompositeNode
    {
    public:
        Sequencer();
        Sequencer(const char*);
        virtual ~Sequencer();

        virtual bool Run() override {
            for (const auto& child : GetChildren()) {
                if (!child->Run()) {
                    return false;
                }
            }
            return true;
        }
    private:

    };
}
