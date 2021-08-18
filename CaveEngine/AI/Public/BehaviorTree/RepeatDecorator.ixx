/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#include <vector>

#include "Decorator.h"

export module RepeatDecorator;

export namespace cave
{
    class RepeatDecorator : public Decorator
    {
    public:
        RepeatDecorator()
        {
            SetNodeName("");
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetChild(NULL);
            SetCount(0);
        }
        RepeatDecorator(const char* nodeName, uint32_t repeatCount)
        {
            SetNodeName(nodeName);
            SetParentNode(NULL);
            SetTreeDepth(0);
            SetChild(NULL);
            SetCount(repeatCount);
        }
        ~RepeatDecorator()
        {

        }

        virtual bool Run(GameObject& gameObject) override
        {
            uint32_t i;
            for (i = 0; i < mRepeatCount; i++)
            {
                GetChild()->Run(gameObject);
            }
            if (i == mRepeatCount)
                return true;
            return false;
        }

        void SetCount(uint32_t repeatCount)
        {
            mRepeatCount = repeatCount;
        }
    private:
        uint32_t mRepeatCount;
    };

}