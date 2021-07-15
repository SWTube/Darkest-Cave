/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "BehaviorTree/Node.h"

namespace cave
{
	Node::Node()
	{
		mNodeName = "";
		mParentNode = NULL;
		mTreeDepth = 0;
	}
	Node::Node(const char* nodeName)
	{
		mNodeName = nodeName;
		mParentNode = NULL;
		mTreeDepth = 0;
	}
	Node::~Node()
	{
		// delete mNodeName;
	}
	const char* Node::GetNodeName() const
	{
		return mNodeName;
	}
	int Node::GetTreeDepth() const
	{
		return mTreeDepth;
	}
	void Node::SetNodeName(const char* nodeName)
	{
		mNodeName = nodeName;
	}
	void Node::SetParentNode(Node* parentNode)
	{
		mParentNode = parentNode;
	}
	void Node::SetTreeDepth(int treeDepth)
	{
		mTreeDepth = treeDepth;
	}
	void Node::Clear()
	{
		delete this;
	}
}
