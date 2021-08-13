/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "Containers/TStack.h"
#include "Debug/Log.h"

export module Tree;

import std.core;
import Array;
import LinkedList;

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
		constexpr Array<T>& GetChildren();
		constexpr const Array<T>& GetChildren() const;
	private:
		const T mData;
		Array<T> mChildren;
	};

	export class AdjacentMatrix
	{
	public:
		AdjacentMatrix() = delete;
		constexpr AdjacentMatrix(size_t size);
		constexpr AdjacentMatrix(size_t size, bool bIsDirected);
		AdjacentMatrix(const AdjacentMatrix& other) = delete;
		AdjacentMatrix(AdjacentMatrix&& other) = delete;
		virtual ~AdjacentMatrix() = default;

		AdjacentMatrix& operator=(const AdjacentMatrix& other) = delete;
		AdjacentMatrix& operator=(AdjacentMatrix&& other) = delete;

		constexpr void ConnectEdge(size_t from, size_t to);
		constexpr void DisconnectEdge(size_t from, size_t to);
	protected:
		bool mbIsDirected;
		Array<Array<bool>> mMatrix;
	};

	export class AdjacentList
	{
	public:
		AdjacentList() = delete;
		constexpr AdjacentList(size_t size);
		constexpr AdjacentList(size_t size, bool bIsDirected);
		AdjacentList(const AdjacentList& other) = delete;
		AdjacentList(AdjacentList&& other) = delete;
		virtual ~AdjacentList() = default;

		AdjacentList& operator=(const AdjacentList& other) = delete;
		AdjacentList& operator=(AdjacentList&& other) = delete;

		constexpr void ConnectEdge(size_t from, size_t to);
		constexpr void DisconnectEdge(size_t from, size_t to);
	protected:
		bool mbIsDirected;
		Array<LinkedList<uint64_t>> mList;
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
	constexpr Array<T>& TreeNode<T>::GetChildren()
	{
		return mChildren;
	}

	constexpr AdjacentMatrix::AdjacentMatrix(size_t size)
		: mMatrix(size, false)
	{
	}

	constexpr AdjacentMatrix::AdjacentMatrix(size_t size, bool bIsDirected)
		: mbIsDirected(bIsDirected)
		, mMatrix()
	{
		for (size_t i = 0; i < size; ++i)
		{
			mMatrix.InsertBack(Array<bool>(size, false));
		}
	}

	constexpr void AdjacentMatrix::ConnectEdge(size_t from, size_t to)
	{
		assert(from < mMatrix.GetSize() && to < mMatrix.GetSize());

		mMatrix[from][to] = true;
		if (!mbIsDirected)
		{
			mMatrix[to][from] = true;
		}
	}

	constexpr void AdjacentMatrix::DisconnectEdge(size_t from, size_t to)
	{
		assert(from < mMatrix.GetSize() && to < mMatrix.GetSize());

		mMatrix[from][to] = false;
		if (!mbIsDirected)
		{
			mMatrix[to][from] = false;
		}
	}


	constexpr AdjacentList::AdjacentList(size_t size)
		: AdjacentList(size, false)
	{
	}

	constexpr AdjacentList::AdjacentList(size_t size, bool bIsDirected)
		: mbIsDirected(bIsDirected)
		, mList()
	{
		for (size_t i = 0; i < size; ++i)
		{
			mList.InsertBack(LinkedList<uint64_t>());
		}
	}

	constexpr void AdjacentList::ConnectEdge(size_t from, size_t to)
	{
		assert(from < mList.GetSize() && to < mList.GetSize());

		mList[from].InsertBack(to);

		if (!mbIsDirected)
		{
			mList[to].InsertBack(from);
		}
	}

	constexpr void AdjacentList::DisconnectEdge(size_t from, size_t to)
	{
		assert(from < mList.GetSize() && to < mList.GetSize());

		for (auto iter = mList[from].GetBeginIterator(); iter != mList[from].GetEndIterator(); ++iter)
		{
			if (*iter == to)
			{
				mList[from].Delete(iter);
			}
		}

		if (!mbIsDirected)
		{
			for (auto iter = mList[to].GetBeginIterator(); iter != mList[to].GetEndIterator(); ++iter)
			{
				if (*iter == from)
				{
					mList[to].Delete(iter);
				}
			}
		}
	}
}