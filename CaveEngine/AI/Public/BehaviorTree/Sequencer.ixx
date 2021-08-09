/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <vector>

#include "BehaviorTreeNode.h"
#include "CompositeNode.h"
#include "Object/GameObject.h"

export module Sequencer;

export namespace cave
{
    class Sequencer : public CompositeNode
    {
    public:
        Sequencer()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
        }
        Sequencer(const char* nodeName)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
        }
        ~Sequencer()
        {

        }

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