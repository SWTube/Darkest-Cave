/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#ifdef __WIN32__
import RootNode;
#else

#include <vector>
#include "Sequencer.h"

namespace cave
{
    class RootNode : public Sequencer
    {
    public:
        RootNode();
        RootNode(const char*);
        ~RootNode();
    private:
    };
}
#endif