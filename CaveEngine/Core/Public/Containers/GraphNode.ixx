/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <queue>
#include <unordered_set>
#include "Debug/Log.h"

export module cave.Core.Containers.GraphNode;

import cave.Core.Containers.Array;
import cave.Core.Containers.Stack;

namespace cave
{
	export class GraphNode final
	{
	public:
		//constexpr explicit GraphNode(const void* data);
		explicit GraphNode(const void* data);

		//constexpr static void SearchDepthFirst(const GraphNode& node);
		static void SearchDepthFirst(const GraphNode* node);
		//constexpr static void SearchBreadthFirst(const GraphNode& node);
		static void SearchBreadthFirst(const GraphNode* node);

		constexpr const void* GetData() const;
		constexpr Array& GetNeightbors();
	private:
		const void* mData;
		Array mNeightbors;
	};

	//constexpr GraphNode::GraphNode(const void* data)
	GraphNode::GraphNode(const void* data)
		: mData(data)
		, mNeightbors()
	{
	}
	
	//constexpr void GraphNode::SearchDepthFirst(const GraphNode& node)
	void GraphNode::SearchDepthFirst(const GraphNode* node)
	{
		std::unordered_set<const GraphNode*> discovered;
		ConstantStack stack;

		discovered.insert(node);
		stack.Push(node);

		while (!stack.IsEmpty())
		{
			const GraphNode* next = reinterpret_cast<const GraphNode*>(stack.GetTop());
			stack.Pop();

			//for (const GraphNode& child : next.mNeightbors)
			//{
			//	if (discovered.contains(child))
			//	{
			//		continue;
			//	}

			//	discovered.insert(child);
			//	stack.Push(child);
			//}

			for (auto iter = next->mNeightbors.GetBeginConstIterator(); iter != next->mNeightbors.GetEndConstIterator(); ++iter)
			{
				if (discovered.contains(reinterpret_cast<const GraphNode*>(*iter)))
				{
					continue;
				}

				discovered.insert(reinterpret_cast<const GraphNode*>(*iter));
				stack.Push(*iter);
			}
		}
	}

	//constexpr void GraphNode::SearchBreadthFirst(const GraphNode& node)
	void GraphNode::SearchBreadthFirst(const GraphNode* node)
	{
		std::unordered_set<const GraphNode*> discovered;
		std::queue<const GraphNode*> queue;

		discovered.insert(node);
		queue.push(node);

		while (!queue.empty())
		{
			const GraphNode* next = queue.back();
			queue.pop();

			//for (const GraphNode& child : mNeightbors)
			//{
			//	if (discovered.contains(child))
			//	{
			//		continue;
			//	}

			//	discovered.insert(child);
			//	queue.push(child);
			//}

			for (auto iter = next->mNeightbors.GetBeginConstIterator(); iter != next->mNeightbors.GetEndConstIterator(); ++iter)
			{
				if (discovered.contains(reinterpret_cast<const GraphNode*>(*iter)))
				{
					continue;
				}

				discovered.insert(reinterpret_cast<const GraphNode*>(*iter));
				queue.push(reinterpret_cast<const GraphNode*>(*iter));
			}
		}
	}
	
	constexpr const void* GraphNode::GetData() const
	{
		return mData;
	}

	
	constexpr Array& GraphNode::GetNeightbors()
	{
		return mNeightbors;
	}
}