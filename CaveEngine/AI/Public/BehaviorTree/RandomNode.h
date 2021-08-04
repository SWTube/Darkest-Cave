/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include <cstdlib>
#include "CompositeNode.h"
#include "Assertion/Assert.h"

namespace cave
{
    class RandomNode : public CompositeNode
    {
    public:
        RandomNode();
        RandomNode(const char*, uint32_t);
        virtual ~RandomNode();

        virtual bool Run(GameObject& gameObject) override {
            if (mMaxRandomCount >= GetChildrenCount()) {
                mMaxRandomCount = GetChildrenCount();
            }

            assert(mMaxRandomCount > 0);

            uint32_t randomNumber = std::rand() % mMaxRandomCount;
            return GetChildren()[randomNumber]->Run(gameObject);
        }

        void SetMaxRandomCount(uint32_t);
    private:
        uint32_t mMaxRandomCount;
    };
}
