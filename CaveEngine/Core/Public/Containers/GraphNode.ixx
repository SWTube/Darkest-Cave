/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "Containers/Array.h"
#include "Containers/TStack.h"
#include "Debug/Log.h"

export module GraphNode;

import std.core;

namespace cave
{
	export template <typename T>
		class GraphNode final
	{
	public:
		constexpr explicit GraphNode(const T& data);

		constexpr static void SearchDepthFirst(const GraphNode& node);
		constexpr static void SearchBreadthFirst(const GraphNode& node);

		constexpr const T& GetData() const;
		constexpr TArray<T>& GetNeightbors();
	private:
		const T mData;
		TArray<T> mNeightbors;
	};

	template <typename T>
	constexpr GraphNode<T>::GraphNode(const T& data)
		: mData(data)
		, mNeightbors()
	{
	}

	template <typename T>
	constexpr void GraphNode<T>::SearchDepthFirst(const GraphNode& node)
	{
		std::unordered_set<const GraphNode&> discovered;
		TStack<const GraphNode&> stack;

		discovered.insert(node);
		stack.Push(node);

		while (!stack.IsEmpty())
		{
			const GraphNode& next = stack.GetTop();
			stack.Pop();

			for (const GraphNode& child : mNeightbors)
			{
				if (discovered.contains(child))
				{
					continue;
				}

				discovered.insert(child);
				stack.Push(child);
			}
		}
	}

	template <typename T>
	constexpr void GraphNode<T>::SearchBreadthFirst(const GraphNode& node)
	{
		std::unordered_set<const GraphNode&> discovered;
		std::queue<const GraphNode&> queue;

		discovered.insert(node);
		queue.push(node);

		while (!queue.empty())
		{
			const GraphNode& next = queue.back();
			queue.pop();

			for (const GraphNode& child : mNeightbors)
			{
				if (discovered.contains(child))
				{
					continue;
				}

				discovered.insert(child);
				queue.push(child);
			}
		}
	}

	template <typename T>
	constexpr const T& GraphNode<T>::GetData() const
	{
		return mData;
	}

	template <typename T>
	constexpr TArray<T>& GraphNode<T>::GetNeightbors()
	{
		return mNeightbors;
	}
}