/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/BTNode.h"

namespace cave
{
	BTNode::BTNode()
	{
		mNodeName = "";
		mParentNode = NULL;
		mTreeDepth = 0;
	}
	BTNode::BTNode(const char* nodeName)
	{
		mNodeName = nodeName;
		mParentNode = NULL;
		mTreeDepth = 0;
	}
	const char* BTNode::GetNodeName() const
	{
		return mNodeName;
	}
	int BTNode::GetTreeDepth() const
	{
		return mTreeDepth;
	}
	void BTNode::SetNodeName(const char* nodeName)
	{
		mNodeName = nodeName;
	}
	void BTNode::SetParentNode(BTNode* parentNode)
	{
		mParentNode = parentNode;
	}
	void BTNode::SetTreeDepth(int treeDepth)
	{
		mTreeDepth = treeDepth;
	}
}
