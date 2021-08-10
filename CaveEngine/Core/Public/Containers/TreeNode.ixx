/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "Containers/Array.h"
#include "Containers/TStack.h"
#include "Debug/Log.h"

export module TreeNode;

import std.core;

namespace cave
{
	export template <typename T>
		class TreeNode final
	{
	public:
		constexpr explicit TreeNode(const T& data);

		constexpr static void SearchDepthFirst(const TreeNode& node);
		constexpr static void SearchBreadthFirst(const TreeNode& node);

		constexpr const T& GetData() const;
		constexpr TArray<T>& GetChildren();
		constexpr const TArray<T>& GetChildren() const;
	private:
		const T mData;
		TArray<T> mChildren;
	};

	template <typename T>
	constexpr TreeNode<T>::TreeNode(const T& data)
		: mData(data)
		, mChildren()
	{
	}

	template <typename T>
	constexpr void TreeNode<T>::SearchDepthFirst(const TreeNode& node)
	{
		TStack<const TreeNode&> stack;

		stack.Push(node);

		while (!stack.IsEmpty())
		{
			const TreeNode& next = stack.GetTop();
			stack.Pop();

			for (const TreeNode& child : mChildren)
			{
				stack.Push(child);
			}
		}
	}

	template <typename T>
	constexpr void TreeNode<T>::SearchBreadthFirst(const TreeNode& node)
	{
		std::queue<const TreeNode&> queue;

		queue.push(node);

		while (!queue.empty())
		{
			const TreeNode& next = queue.back();
			queue.pop();

			for (const TreeNode& child : mChildren)
			{
				queue.push(child);
			}
		}
	}

	template <typename T>
	constexpr const T& TreeNode<T>::GetData() const
	{
		return mData;
	}

	template <typename T>
	constexpr TArray<T>& TreeNode<T>::GetChildren()
	{
		return mChildren;
	}
}