/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "Debug/Log.h"
#include "Memory/MemoryPool.h"

export module Graph;

import std.core;
import Array;
import LinkedList;
import Stack;
import String;

namespace cave
{
	export class GraphNode final
	{
	public:
		constexpr explicit GraphNode(const void* data);

		static void SearchDepthFirst(const GraphNode& node);
		static void SearchBreadthFirst(const GraphNode& node);

		constexpr void AddNext(GraphNode& node);
		constexpr const void* GetData() const;
		constexpr Array<GraphNode*>& GetNeightbors();
		constexpr const Array<GraphNode*>& GetNeightbors() const;
		static LinkedList<const GraphNode*> SortTopologically(const Array<GraphNode*>& nodes);
		static void DestroyGraph(Array<GraphNode*>& nodes, MemoryPool& pool);
		//static void GetTransposeMalloc(Array<GraphNode*>& nodes, MemoryPool& pool, Array<GraphNode*>& outGraph, std::unordered_map<GraphNode*, GraphNode*>& outTable);
		static LinkedList<LinkedList<const GraphNode*>> GetSccList(const Array<GraphNode*>& nodes, const LinkedList<const GraphNode*>& order, const std::unordered_map<GraphNode*, GraphNode*>& transposeTable);
	private:
		static void sortTopologicallyRecursive(const GraphNode& node, LinkedList<const GraphNode*>& outSortedList, std::unordered_set<const GraphNode*>& discovered);
		static void destroyGraphRecursive(GraphNode* node, MemoryPool& pool, std::unordered_set<GraphNode*>& discovered);
		static void getSccListRecursive(const GraphNode* node, LinkedList<LinkedList<const GraphNode*>>& outStronglyConnectedComponents, std::unordered_set<uintptr_t>& outDiscovered);

		const void* mData;
		Array<GraphNode*> mNeighbors;
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

	constexpr GraphNode::GraphNode(const void* data)
		: mData(data)
		, mNeighbors()
	{
	}

	void GraphNode::SearchDepthFirst(const GraphNode& node)
	{
		std::unordered_set<const GraphNode*> discovered;
		Stack stack;

		discovered.insert(&node);
		stack.Push(&node);

		while (!stack.IsEmpty())
		{
			const GraphNode* next = reinterpret_cast<const GraphNode*>(stack.GetTop());
			stack.Pop();

			for (size_t i = 0; i < next->mNeighbors.GetSize(); ++i)
			{
				if (discovered.contains(next->mNeighbors[i]))
				{
					continue;
				}
	
				discovered.insert(next->mNeighbors[i]);
				stack.Push(next->mNeighbors[i]);
			}

			/*
			for (const GraphNode* child : next->mNeighbors)
			{
				if (discovered.contains(child))
				{
					continue;
				}

				discovered.insert(child);
				stack.Push(child);
			}
			*/
		}
	}

	void GraphNode::SearchBreadthFirst(const GraphNode& node)
	{
		std::unordered_set<const GraphNode*> discovered;
		std::queue<const GraphNode*> queue;

		discovered.insert(&node);
		queue.push(&node);

		while (!queue.empty())
		{
			const GraphNode* next = queue.back();
			queue.pop();

			for (size_t i = 0; i < next->mNeighbors.GetSize(); ++i)
			{
				if (discovered.contains(next->mNeighbors[i]))
				{
					continue;
				}

				discovered.insert(next->mNeighbors[i]);
				queue.push(next->mNeighbors[i]);
			}

			/*
			for (const GraphNode* child : next->mNeighbors)
			{
				if (discovered.contains(child))
				{
					continue;
				}

				discovered.insert(child);
				queue.push(child);
			}
			*/
		}
	}

	constexpr void GraphNode::AddNext(GraphNode& node)
	{
		mNeighbors.InsertBack(&node);
	}

	constexpr const void* GraphNode::GetData() const
	{
		return mData;
	}

	constexpr Array<GraphNode*>& GraphNode::GetNeightbors()
	{
		return mNeighbors;
	}
	
	constexpr const Array<GraphNode*>& GraphNode::GetNeightbors() const
	{
		return mNeighbors;
	}

	LinkedList<const GraphNode*> GraphNode::SortTopologically(const Array<GraphNode*>& nodes)
	{
		std::unordered_set<const GraphNode*> discovered;
		LinkedList<const GraphNode*> sortedList;

		for (size_t i = 0; i < nodes.GetSize(); ++i)
		{
			if (discovered.contains(nodes[i]))
			{
				continue;
			}

			sortTopologicallyRecursive(*nodes[i], sortedList, discovered);
		}
		/*
		for (const GraphNode& node : nodes)
		{
			if (discovered.contains(&node))
			{
				continue;
			}

			sortTopologicallyRecursive(node, sortedList, discovered);
		}
		*/

		return sortedList;
	}

	void GraphNode::sortTopologicallyRecursive(const GraphNode& node, LinkedList<const GraphNode*>& outSortedList, std::unordered_set<const GraphNode*>& discovered)
	{
		discovered.insert(&node);

		for (size_t i = 0; i < node.mNeighbors.GetSize(); ++i)
		{
			if (discovered.contains(node.mNeighbors[i]))
			{
				continue;
			}

			sortTopologicallyRecursive(*node.mNeighbors[i], outSortedList, discovered);
		}

		outSortedList.InsertFront(&node);
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

	void GraphNode::DestroyGraph(Array<GraphNode*>& nodes, MemoryPool& pool)
	{
		std::unordered_set<GraphNode*> discovered;

		for (size_t i = 0; i < nodes.GetSize(); ++i)
		{
			if (discovered.contains(nodes[i]))
			{
				continue;
			}

			destroyGraphRecursive(nodes[i], pool, discovered);
		}
	}

	void GraphNode::destroyGraphRecursive(GraphNode* node, MemoryPool& pool, std::unordered_set<GraphNode*>& discovered)
	{
		discovered.insert(node);

		for (size_t i = 0; i < node->mNeighbors.GetSize(); ++i)
		{
			if (discovered.contains(node->mNeighbors[i]))
			{
				continue;
			}

			destroyGraphRecursive(node->mNeighbors[i], pool, discovered);
		}

		pool.Deallocate(node, sizeof(GraphNode));
	}

	/*
	void GraphNode::GetTransposeMalloc(Array<GraphNode*>& nodes, MemoryPool& pool, Array<GraphNode*>& outGraph, std::unordered_map<GraphNode*, GraphNode*>& outTable)
	{
		std::unordered_map<uintptr_t, GraphNode*> discovered;

		for (size_t i = 0; i < nodes.GetSize(); ++i)
		{
			if (!discovered.contains(reinterpret_cast<uintptr_t>(nodes[i]->GetData())))
			{
				GraphNode* node = reinterpret_cast<GraphNode*>(pool.Allocate(sizeof(GraphNode)));
				::new(node) GraphNode(nodes[i]->GetData());
				discovered.insert(std::pair<uintptr_t, GraphNode*>(reinterpret_cast<uintptr_t>(nodes[i]->GetData()), node));
				outTable.insert(std::pair<GraphNode*, GraphNode*>(nodes[i], node));
				outGraph.InsertBack(node);
			}

			for (size_t j = 0; j < nodes[i]->mNeighbors.GetSize(); ++j)
			{
				if (!discovered.contains(reinterpret_cast<uintptr_t>(nodes[i]->mNeighbors[j]->GetData())))
				{
					GraphNode* childNode = reinterpret_cast<GraphNode*>(pool.Allocate(sizeof(GraphNode)));
					::new(childNode) GraphNode(nodes[i]->mNeighbors[j]->GetData());
					discovered.insert(std::pair<uintptr_t, GraphNode*>(reinterpret_cast<uintptr_t>(nodes[i]->mNeighbors[j]->GetData()), childNode));
					outTable.insert(std::pair<GraphNode*, GraphNode*>(nodes[i]->mNeighbors[j], childNode));
					outGraph.InsertBack(childNode);
				}

				discovered.at(reinterpret_cast<uintptr_t>(nodes[i]->mNeighbors[j]->GetData()))->AddNext(*discovered.at(reinterpret_cast<uintptr_t>(nodes[i]->GetData())));
			}
		}
	}
	*/

	LinkedList<LinkedList<const GraphNode*>> GraphNode::GetSccList(const Array<GraphNode*>& nodes, const LinkedList<const GraphNode*>& order, const std::unordered_map<GraphNode*, GraphNode*>& transposeTable)
	{
		LinkedList<LinkedList<const GraphNode*>> stronglyConnectedComponents;
		std::unordered_set<uintptr_t> discovered;

		for (size_t i = 0; i < nodes.GetSize(); ++i)
		{
			if (discovered.contains(reinterpret_cast<uintptr_t>(nodes[i]->GetData())))
			{
				continue;
			}

			stronglyConnectedComponents.InsertBack(LinkedList<const GraphNode*>());
			getSccListRecursive(nodes[i], stronglyConnectedComponents, discovered);
		}

		return stronglyConnectedComponents;
	}

	void GraphNode::getSccListRecursive(const GraphNode* node, LinkedList<LinkedList<const GraphNode*>>& outStronglyConnectedComponents, std::unordered_set<uintptr_t>& outDiscovered)
	{
		outDiscovered.insert(reinterpret_cast<uintptr_t>(node->mData));

		for (size_t i = 0; i < node->mNeighbors.GetSize(); ++i)
		{
			if (outDiscovered.contains(reinterpret_cast<uintptr_t>(node->mNeighbors[i]->GetData())))
			{
				continue;
			}

			getSccListRecursive(node->mNeighbors[i], outStronglyConnectedComponents, outDiscovered);
		}

		outStronglyConnectedComponents.GetBack().InsertBack(node);
	}

#ifdef CAVE_BUILD_DEBUG
	namespace GraphTest
	{
		export void Main();

		void Main()
		{
			/*
			{
				GraphNode comp0000("0000: Intro to Programming for Novices and Hobbyists (C#)");
				GraphNode comp1500("1500: Intro to Professional Programming with C#");
				GraphNode comp1000("1000: Math for Software Engineers");
				GraphNode comp1600("1600: Visual Programming with C#");
				GraphNode comp2200("2200: Unmanaged Programming with C");
				GraphNode comp2500("2500: Object Oriented Programming and Design with Java");
				GraphNode comp4700("4700: Database Programming with C#");
				GraphNode comp2300("2300: Assembly");
				GraphNode comp3200("3200: Unmanaged Programming with C++");
				GraphNode comp3500("3500: Algorithm & Data Structure with Java");
				GraphNode comp3000("3000: Computer Architecture (C or Assembly)");
				GraphNode comp4000("4000: Operating Systems (C)");
				GraphNode comp4100("4100: Data Comm (C or C++");

				comp0000.AddNext(comp1500);

				comp1500.AddNext(comp1000);
				comp1500.AddNext(comp1600);
				comp1500.AddNext(comp2200);
				comp1500.AddNext(comp2500);

				comp1000.AddNext(comp1600);
				comp1000.AddNext(comp2200);
				comp1000.AddNext(comp2500);

				comp1600.AddNext(comp4700);

				comp2200.AddNext(comp2300);
				comp2200.AddNext(comp3200);
				comp2200.AddNext(comp3000);

				comp2500.AddNext(comp4700);
				comp2500.AddNext(comp3200);
				comp2500.AddNext(comp3500);

				comp2300.AddNext(comp3000);

				comp3200.AddNext(comp4000);
				comp3200.AddNext(comp4100);

				comp3000.AddNext(comp4000);

				Array<GraphNode*> nodes;

				nodes.InsertBack(&comp0000);
				nodes.InsertBack(&comp1000);
				nodes.InsertBack(&comp1500);
				nodes.InsertBack(&comp1600);
				nodes.InsertBack(&comp2200);
				nodes.InsertBack(&comp2300);
				nodes.InsertBack(&comp2500);
				nodes.InsertBack(&comp3000);
				nodes.InsertBack(&comp3200);
				nodes.InsertBack(&comp3500);
				nodes.InsertBack(&comp4000);
				nodes.InsertBack(&comp4100);
				nodes.InsertBack(&comp4700);

				LinkedList<const GraphNode*> sortedNodes = GraphNode::SortTopologically(nodes);

				while (!sortedNodes.IsEmpty())
				{
					const GraphNode* node = sortedNodes.GetFront();
					sortedNodes.DeleteFront();
					LOGDF(eLogChannel::CORE, "Node: %s", reinterpret_cast<const char*>(node->GetData()));
				}
			}
			*/

			{
				GraphNode comp0000("0000: Intro to Programming for Novices and Hobbyists (C#)");
				GraphNode comp1500("1500: Intro to Professional Programming with C#");
				GraphNode comp1000("1000: Math for Software Engineers");
				GraphNode comp1600("1600: Visual Programming with C#");
				GraphNode comp2200("2200: Unmanaged Programming with C");
				GraphNode comp2500("2500: Object Oriented Programming and Design with Java");
				GraphNode comp4700("4700: Database Programming with C#");
				GraphNode comp2300("2300: Assembly");
				GraphNode comp3200("3200: Unmanaged Programming with C++");
				GraphNode comp3500("3500: Algorithm & Data Structure with Java");
				GraphNode comp3000("3000: Computer Architecture (C or Assembly)");
				GraphNode comp4000("4000: Operating Systems (C)");
				GraphNode comp4100("4100: Data Comm (C or C++");

				comp0000.AddNext(comp1500);

				comp1500.AddNext(comp1000);
				comp1500.AddNext(comp1600);
				comp1500.AddNext(comp2200);
				comp1500.AddNext(comp2500);

				comp1000.AddNext(comp1600);
				comp1000.AddNext(comp2200);
				comp1000.AddNext(comp2500);

				comp1600.AddNext(comp4700);

				comp2200.AddNext(comp2300);
				comp2200.AddNext(comp3200);
				comp2200.AddNext(comp3000);

				comp2500.AddNext(comp4700);
				comp2500.AddNext(comp3200);
				comp2500.AddNext(comp3500);

				comp2300.AddNext(comp3000);

				comp3200.AddNext(comp4000);
				comp3200.AddNext(comp4100);

				comp3000.AddNext(comp4000);

				Array<GraphNode*> nodes;

				nodes.InsertBack(&comp0000);
				nodes.InsertBack(&comp1000);
				nodes.InsertBack(&comp1500);
				nodes.InsertBack(&comp1600);
				nodes.InsertBack(&comp2200);
				nodes.InsertBack(&comp2300);
				nodes.InsertBack(&comp2500);
				nodes.InsertBack(&comp3000);
				nodes.InsertBack(&comp3200);
				nodes.InsertBack(&comp3500);
				nodes.InsertBack(&comp4000);
				nodes.InsertBack(&comp4100);
				nodes.InsertBack(&comp4700);

				LinkedList<const GraphNode*> sortedNodes = GraphNode::SortTopologically(nodes);

				Array<GraphNode*> transposedGraph;
				std::unordered_map<GraphNode*, GraphNode*> transposedTable;
				
				//GraphNode::GetTransposeMalloc(nodes, gCoreMemoryPool, transposedGraph, transposedTable);

				LinkedList<LinkedList<const GraphNode*>> sccList = GraphNode::GetSccList(transposedGraph, sortedNodes, transposedTable);
				
				size_t level = 0;
				while (sccList.GetSize() > 0)
				{
					LinkedList<const GraphNode*>& list = sccList.GetFront();
					sccList.DeleteFront();

					while (list.GetSize() > 0)
					{
						const GraphNode* node = list.GetFront();
						list.DeleteFront();
						LOGDF(eLogChannel::CORE, "Node[%lu]: %s", level, reinterpret_cast<const char*>(node->GetData()));
					}
					++level;
				}
				
				GraphNode::DestroyGraph(transposedGraph, gCoreMemoryPool);
			}
		}
	}
#endif
}