/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/BehaviorTreeNode.h"

namespace cave
{
	BehaviorTreeNode::BehaviorTreeNode()
	{
		mNodeName = "";
		mParentNode = NULL;
		mTreeDepth = 0;
	}
	BehaviorTreeNode::BehaviorTreeNode(const char* nodeName)
	{
		mNodeName = nodeName;
		mParentNode = NULL;
		mTreeDepth = 0;
	}
	BehaviorTreeNode::~BehaviorTreeNode()
	{
		// delete mNodeName;
	}
	const char* BehaviorTreeNode::GetNodeName() const
	{
		return mNodeName;
	}
	uint32_t BehaviorTreeNode::GetTreeDepth() const
	{
		return mTreeDepth;
	}
	void BehaviorTreeNode::SetNodeName(const char* nodeName)
	{
		mNodeName = nodeName;
	}
	void BehaviorTreeNode::SetParentNode(BehaviorTreeNode* parentNode)
	{
		mParentNode = parentNode;
	}
	void BehaviorTreeNode::SetTreeDepth(uint32_t treeDepth)
	{
		mTreeDepth = treeDepth;
	}
	void BehaviorTreeNode::Clear()
	{
		delete this;
	}
}
