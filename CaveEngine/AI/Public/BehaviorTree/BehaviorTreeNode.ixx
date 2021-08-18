module;

#include <functional>
/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Object/GameObject.h"

export module BehaviorTreeNode;

export namespace cave
{
    class BehaviorTreeNode
    {
    public:
		BehaviorTreeNode()
		{
			mNodeName = "";
			mParentNode = NULL;
			mTreeDepth = 0;
		}
		BehaviorTreeNode(const char* nodeName)
		{
			mNodeName = nodeName;
			mParentNode = NULL;
			mTreeDepth = 0;
		}
		virtual ~BehaviorTreeNode()
		{
			// delete mNodeName;
		}

		virtual bool Run(GameObject& gameObject) = 0;

		const char* GetNodeName() const
		{
			return mNodeName;
		}
		uint32_t GetTreeDepth() const
		{
			return mTreeDepth;
		}
		void SetNodeName(const char* nodeName)
		{
			mNodeName = nodeName;
		}
		void SetParentNode(BehaviorTreeNode* parentNode)
		{
			mParentNode = parentNode;
		}
		void SetTreeDepth(uint32_t treeDepth)
		{
			mTreeDepth = treeDepth;
		}
		virtual void Clear()
		{
			delete this;
		}
    private:
        BehaviorTreeNode* mParentNode = NULL;
        const char* mNodeName = "";
        uint32_t mTreeDepth = 0;
    };

}