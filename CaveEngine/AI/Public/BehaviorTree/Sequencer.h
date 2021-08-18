/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#ifdef __WIN32__
import Sequencer;
#else

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

        virtual bool Run(GameObject& gameObject) override {
            for (const auto& child : GetChildren()) {
                if (!child->Run(gameObject)) {
                    return false;
                }
            }
            return true;
        }
    private:

    };
}
#endif
