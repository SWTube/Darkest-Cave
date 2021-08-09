/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <vector>
#include <cstdlib>

#include "CompositeNode.h"
#include "Assertion/Assert.h"

export module RandomNode;

export namespace cave
{
    class RandomNode : public CompositeNode
    {
    public:
        RandomNode()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetMaxRandomCount(0);
        }
        RandomNode(const char* nodeName, uint32_t maxRandomCount)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetMaxRandomCount(maxRandomCount);
        }
        virtual ~RandomNode()
        {

        } 
        virtual bool Run(GameObject& gameObject) override {
            if (mMaxRandomCount >= GetChildrenCount()) {
                mMaxRandomCount = GetChildrenCount();
            }

            assert(mMaxRandomCount > 0);

            uint32_t randomNumber = std::rand() % mMaxRandomCount;
            return GetChildren()[randomNumber]->Run(gameObject);
        }
        void SetMaxRandomCount(uint32_t maxRandomCount)
        {
            mMaxRandomCount = maxRandomCount;
        }
    private:
        uint32_t mMaxRandomCount;
    };
}