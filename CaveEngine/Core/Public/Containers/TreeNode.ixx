/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <queue>
#include "Debug/Log.h"

export module cave.Core.Containers.TreeNode;

import cave.Core.Containers.Array;
import cave.Core.Containers.Stack;

namespace cave
{
	export class TreeNode final
	{
	public:
		//constexpr explicit TreeNode(const void* data);
		explicit TreeNode(const void* data);

		//constexpr static void SearchDepthFirst(const TreeNode& node);
		static void SearchDepthFirst(const TreeNode* node);
		//constexpr static void SearchBreadthFirst(const TreeNode& node);
		static void SearchBreadthFirst(const TreeNode* node);

		constexpr const void* GetData() const;
		constexpr Array& GetChildren();
	private:
		const void* mData;
		Array mChildren;
	};

	//constexpr TreeNode::TreeNode(const void* data)
	TreeNode::TreeNode(const void* data)
		: mData(data)
		, mChildren()
	{
	}

	//constexpr void TreeNode::SearchDepthFirst(const TreeNode& node)
	void TreeNode::SearchDepthFirst(const TreeNode* node)
	{
		ConstantStack stack;

		stack.Push(node);

		while (!stack.IsEmpty())
		{
			const TreeNode* next = reinterpret_cast<const TreeNode*>(stack.GetTop());
			stack.Pop();

			/*for (const void* child : next.mChildren)
			{
				stack.Push(child);
			}*/
			for (auto iter = next->mChildren.GetBeginConstIterator(); iter != next->mChildren.GetEndConstIterator(); ++iter)
			{
				stack.Push(*iter);
			}
		}
	}

	//constexpr void TreeNode::SearchBreadthFirst(const TreeNode& node)
	void TreeNode::SearchBreadthFirst(const TreeNode* node)
	{
		std::queue<const TreeNode*> queue;

		queue.push(node);

		while (!queue.empty())
		{
			const TreeNode* next = queue.back();
			queue.pop();

			//for (const TreeNode& child : next.mChildren)
			//{
			//	queue.push(child);
			//}
			for (auto iter = next->mChildren.GetBeginConstIterator(); iter != next->mChildren.GetEndConstIterator(); ++iter)
			{
				queue.push(reinterpret_cast<const TreeNode*>(*iter));
			}
		}
	}

	constexpr const void* TreeNode::GetData() const
	{
		return mData;
	}

	constexpr Array& TreeNode::GetChildren()
	{
		return mChildren;
	}
}