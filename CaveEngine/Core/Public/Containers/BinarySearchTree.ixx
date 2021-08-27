/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#ifdef CAVE_BUILD_DEBUG

#include "Utils/Crt.h"
#include "Debug/Log.h"

#endif

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module cave.Core.Containers.BinarySearchTree;

export namespace cave
{
	struct BinarySearchTreeNode
	{
		void* mItem;
		BinarySearchTreeNode* mLeftChild;
		BinarySearchTreeNode* mRightChild;
		BinarySearchTreeNode* mParent;
	};

	class BinarySearchTree final
	{
	public:
		constexpr BinarySearchTree();
		constexpr BinarySearchTree(MemoryPool& pool);

		~BinarySearchTree();

		constexpr void Insert(void* item);
		constexpr void Delete(void* item);
		constexpr bool Search(void* item);

#ifdef CAVE_BUILD_DEBUG

		constexpr void PrintInt32();
		constexpr void PrintInt32Recursive(BinarySearchTreeNode* node);

#endif

	private:
		constexpr BinarySearchTreeNode* GetNextNode(BinarySearchTreeNode* node);

	private:
		MemoryPool* mPool;
		BinarySearchTreeNode* mRootNode;
	};

	constexpr BinarySearchTree::BinarySearchTree()
		: BinarySearchTree(gCoreMemoryPool)
	{ }

	constexpr BinarySearchTree::BinarySearchTree(MemoryPool& pool)
		: mPool(&pool)
		, mRootNode(nullptr)
	{ }

	BinarySearchTree::~BinarySearchTree()
	{
		BinarySearchTreeNode* tempNode = mRootNode;

		if (tempNode == nullptr)
		{
			return;
		}

		while (tempNode != mRootNode || (tempNode->mLeftChild != nullptr) || (tempNode->mRightChild != nullptr))
		{
			if (tempNode->mLeftChild != nullptr)
			{
				tempNode = tempNode->mLeftChild;
			}
			else if (tempNode->mRightChild != nullptr)
			{
				tempNode = tempNode->mRightChild;
			}
			else
			{
				BinarySearchTreeNode* deleteNode = tempNode;
				tempNode = tempNode->mParent;

				if (tempNode->mLeftChild == deleteNode)
				{
					tempNode->mLeftChild = nullptr;
				}
				else
				{
					tempNode->mRightChild = nullptr;
				}

				LOGDF(eLogChannel::CORE_CONTAINER, "-%d", *reinterpret_cast<int32_t*>(deleteNode->mItem));

				mPool->Deallocate(deleteNode, sizeof(BinarySearchTreeNode));
			}
		}

		LOGDF(eLogChannel::CORE_CONTAINER, "-%d", *reinterpret_cast<int32_t*>(tempNode->mItem));
		LOGD(eLogChannel::CORE_CONTAINER, "Deallocate End");
		mPool->Deallocate(tempNode, sizeof(BinarySearchTreeNode));
		mRootNode = nullptr;
	}

	constexpr void BinarySearchTree::Insert(void* item)
	{
		if (mRootNode == nullptr)
		{
			mRootNode = reinterpret_cast<BinarySearchTreeNode*>(mPool->Allocate(sizeof(BinarySearchTreeNode)));
			mRootNode->mItem = item;
			mRootNode->mLeftChild = nullptr;
			mRootNode->mRightChild = nullptr;
			mRootNode->mParent = nullptr;
			LOGDF(eLogChannel::CORE_CONTAINER, "+%d", *reinterpret_cast<int32_t*>(mRootNode->mItem));
			return;
		}

		BinarySearchTreeNode* tempNode = mRootNode;
		BinarySearchTreeNode* parentTempNode = tempNode;

		while (tempNode != nullptr)
		{
			parentTempNode = tempNode;

			if (item < tempNode->mItem)
			{
				tempNode = tempNode->mLeftChild;
			}
			else if (item > tempNode->mItem)
			{
				tempNode = tempNode->mRightChild;
			}
			else
			{
				return;
			}
		}

		tempNode = reinterpret_cast<BinarySearchTreeNode*>(mPool->Allocate(sizeof(BinarySearchTreeNode)));
		tempNode->mItem = item;
		tempNode->mLeftChild = nullptr;
		tempNode->mRightChild = nullptr;
		tempNode->mParent = parentTempNode;

		if (item < parentTempNode->mItem)
		{
			parentTempNode->mLeftChild = tempNode;
		}
		else if (item > parentTempNode->mItem)
		{
			parentTempNode->mRightChild = tempNode;
		}

		LOGDF(eLogChannel::CORE_CONTAINER, "+%d", *reinterpret_cast<int32_t*>(tempNode->mItem));
	}

	constexpr void BinarySearchTree::Delete(void* item)
	{
		BinarySearchTreeNode* deleteNode = mRootNode;
		BinarySearchTreeNode* childNode = nullptr;

		while (deleteNode != nullptr)
		{
			if (item < deleteNode->mItem)
			{
				deleteNode = deleteNode->mLeftChild;
			}
			else if (item > deleteNode->mItem)
			{
				deleteNode = deleteNode->mRightChild;
			}
			else
			{
				break;
			}
		}

		if (deleteNode == nullptr)
		{
			return;
		}


		if((deleteNode->mLeftChild != nullptr) && (deleteNode->mRightChild != nullptr))
		{
			void* tempItem = deleteNode->mItem;

			deleteNode->mItem = GetNextNode(deleteNode)->mItem;
			deleteNode = GetNextNode(deleteNode);

			deleteNode->mItem = tempItem;
		}

		if (deleteNode->mLeftChild != nullptr)
		{
			childNode = deleteNode->mLeftChild;
		}
		else
		{
			childNode = deleteNode->mRightChild;
		}

		if (deleteNode == mRootNode)
		{
			if (childNode == nullptr)
			{
				mRootNode = nullptr;
			}
			else
			{
				mRootNode = childNode;

				mRootNode->mParent = nullptr;
			}
		}
		else
		{
			if (deleteNode->mParent->mLeftChild == deleteNode)
			{
				deleteNode->mParent->mLeftChild = childNode;
			}
			else
			{
				deleteNode->mParent->mRightChild = childNode;
				
			}

			if (childNode != nullptr)
			{
				childNode->mParent = deleteNode->mParent;
			}
		}

		mPool->Deallocate(deleteNode, sizeof(BinarySearchTreeNode));
		LOGDF(eLogChannel::CORE_CONTAINER, "-%d", *reinterpret_cast<int32_t*>(deleteNode->mItem));
	}

	constexpr bool BinarySearchTree::Search(void* item)
	{
		BinarySearchTreeNode* tempNode = mRootNode;

		while (tempNode != nullptr)
		{
			if (item < tempNode->mItem)
			{
				tempNode = tempNode->mLeftChild;
			}
			else if (item > tempNode->mItem)
			{
				tempNode = tempNode->mRightChild;
			}
			else
			{
				return true;
			}
		}

		return false;
	}

	constexpr BinarySearchTreeNode* BinarySearchTree::GetNextNode(BinarySearchTreeNode* node)
	{
		BinarySearchTreeNode* prevNode = node;
		node = node->mRightChild;

		while (node != nullptr)
		{
			prevNode = node;
			node = node->mLeftChild;
		}

		return prevNode;
	}

#ifdef CAVE_BUILD_DEBUG

	constexpr void BinarySearchTree::PrintInt32()
	{
		PrintInt32Recursive(mRootNode);
	}

	constexpr void BinarySearchTree::PrintInt32Recursive(BinarySearchTreeNode* node)
	{
		if (node == nullptr)
		{
			return;
		}

		PrintInt32Recursive(node->mLeftChild);
		LOGDF(eLogChannel::CORE_CONTAINER, "%d", *reinterpret_cast<int32_t*>(node->mItem));
		PrintInt32Recursive(node->mRightChild);
	}
	

#endif

#ifdef CAVE_BUILD_DEBUG
	namespace BinarySearchTreeTest
	{
		int32_t** itemTable;
		size_t* insertCount;

		size_t* deleteCount;

		size_t* searchCount;

		constexpr size_t MAX_COUNT = 16;
		size_t testCount;
		constexpr uint8_t TEST_ALL = 0b11111111;
		constexpr uint8_t TEST_INSERT = 0b00000001;
		constexpr uint8_t TEST_DELETE = 0b00000010;
		constexpr uint8_t TEST_SEARCH = 0b00000100;

		void Test(size_t ContainerTestCount, uint8_t containerTestCase);

		namespace Container
		{
			void Insert(BinarySearchTree& tree, size_t count)
			{
				for (size_t i = 0; i < insertCount[count]; ++i)
				{
					size_t row = rand() % testCount;
					size_t col = rand() % MAX_COUNT;

					tree.Insert(&itemTable[row][col]);
					//LOGDF(eLogChannel::CORE_CONTAINER, "Insert: %d", itemTable[count][i]);
				}
			}

			void Delete(BinarySearchTree& tree, size_t count)
			{
				for (size_t i = 0; i < deleteCount[count]; ++i)
				{
					size_t row = rand() % testCount;
					size_t col = rand() % MAX_COUNT;

					tree.Delete(&itemTable[row][col]);
					//LOGDF(eLogChannel::CORE_CONTAINER, "Delete: %d", itemTable[row][col]);
				}
			}

			void Search(BinarySearchTree& tree, size_t count)
			{
				for (size_t i = 0; i < searchCount[count]; ++i)
				{
					size_t row = rand() % (count + 1);
					size_t col = rand() % insertCount[row];

					LOGDF(eLogChannel::CORE_CONTAINER, "Search: %d | %d", itemTable[row][col], tree.Search(&itemTable[row][col]));
				}
			}
		}

		void Test(size_t containerTestCount, uint8_t containerTestCase)
		{
			srand(time(NULL));

			testCount = containerTestCount;

			BinarySearchTree tree;

			itemTable = reinterpret_cast<int32_t**>(gCoreMemoryPool.Allocate(sizeof(int32_t*) * containerTestCount));
			insertCount = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * containerTestCount));

			deleteCount = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * containerTestCount));

			searchCount = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * containerTestCount));

			for (size_t i = 0; i < containerTestCount; ++i)
			{
				itemTable[i] = reinterpret_cast<int32_t*>(gCoreMemoryPool.Allocate(sizeof(int32_t) * MAX_COUNT));

				insertCount[i] = rand() % 4 + 1;
				deleteCount[i] = rand() % 32 + 1;
				searchCount[i] = rand() % insertCount[i] + 1;

				for (size_t j = 0; j < MAX_COUNT; ++j)
				{
					itemTable[i][j] = rand();
				}
			}

			for (size_t i = 0; i < containerTestCount; ++i)
			{
				if (containerTestCase & TEST_INSERT) 
				{
					Container::Insert(tree, i);
				}

				if (containerTestCase & TEST_DELETE)
				{
					Container::Delete(tree, i);
				}

				if (containerTestCase & TEST_SEARCH)
				{
					Container::Search(tree, i);
				}

				//tree.PrintInt32();
			}

			for (size_t i = 0; i < containerTestCount; ++i)
			{
				gCoreMemoryPool.Deallocate(itemTable[i], sizeof(int32_t) * MAX_COUNT);
			}

			gCoreMemoryPool.Deallocate(itemTable, sizeof(int32_t*) * containerTestCount);
			gCoreMemoryPool.Deallocate(insertCount, sizeof(size_t) * containerTestCount);

			gCoreMemoryPool.Deallocate(deleteCount, sizeof(size_t) * containerTestCount);

			gCoreMemoryPool.Deallocate(searchCount, sizeof(size_t) * containerTestCount);
		}
	}
#endif
}