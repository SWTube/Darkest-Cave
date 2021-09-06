/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#define _CRT_SECURE_NO_WARNINGS
module;

#ifdef CAVE_BUILD_DEBUG

#include "Utils/Crt.h"
#include "Debug/Log.h"

#endif

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module cave.Core.Containers.BinarySearchTree;

#ifdef CAVE_BUILD_DEBUG

import cave.Core.String;

#endif


export namespace cave
{
	enum class eBinarySearchTreeColor : bool
	{
		RED,
		BLACK
	};

	struct BinarySearchTreeNode
	{
		void* mItem;
		eBinarySearchTreeColor mColor;
		BinarySearchTreeNode* mLeftChild;
		BinarySearchTreeNode* mRightChild;
		BinarySearchTreeNode* mParent;

		constexpr BinarySearchTreeNode()
		{
			mItem = nullptr;
			mColor = eBinarySearchTreeColor::BLACK;
			mLeftChild = nullptr;
			mRightChild = nullptr;
			mParent = nullptr;
		}
	};

	class BinarySearchTree final
	{
	public:
		constexpr BinarySearchTree();
		constexpr BinarySearchTree(MemoryPool& pool);

		~BinarySearchTree();

		constexpr bool Insert(void* item);
		constexpr bool Delete(void* item);
		constexpr bool Search(void* item);

		constexpr size_t GetSize() const;

#ifdef CAVE_BUILD_DEBUG
		void PrintInt32();
		constexpr bool ColorCheck();
		size_t GetHeight();
#endif

	private:
		constexpr BinarySearchTreeNode* GetNextNode(BinarySearchTreeNode* node);
		constexpr BinarySearchTreeNode* GetItemNode(void* item);
		constexpr void LeftRotation(BinarySearchTreeNode* node);
		constexpr void RightRotation(BinarySearchTreeNode* node);
		constexpr void InsertColorFix(BinarySearchTreeNode* node);
		constexpr void DeleteColorFix(BinarySearchTreeNode* node, BinarySearchTreeNode* parentNode);

#ifdef CAVE_BUILD_DEBUG
		void PrintInt32Recursive(BinarySearchTreeNode* node, size_t space, size_t height);
		constexpr int32_t ColorCheckRecursive(BinarySearchTreeNode* node, bool& colorCheck);
		size_t GetHeightRecursive(BinarySearchTreeNode* node);
#endif

	private:
		MemoryPool* mPool;
		BinarySearchTreeNode* mRootNode;
		static BinarySearchTreeNode msNilNode;
		size_t mSize;
	};

	BinarySearchTreeNode BinarySearchTree::msNilNode = BinarySearchTreeNode();

	constexpr BinarySearchTree::BinarySearchTree()
		: BinarySearchTree(gCoreMemoryPool)
	{ }

	constexpr BinarySearchTree::BinarySearchTree(MemoryPool& pool)
		: mPool(&pool)
		, mRootNode(nullptr)
		, mSize(0)
	{ }

	BinarySearchTree::~BinarySearchTree()
	{
		BinarySearchTreeNode* tempNode = mRootNode;

		if (tempNode == nullptr)
		{
			return;
		}

		while (tempNode != mRootNode || (tempNode->mLeftChild != &msNilNode) || (tempNode->mRightChild != &msNilNode))
		{
			if (tempNode->mLeftChild != &msNilNode)
			{
				tempNode = tempNode->mLeftChild;
			}
			else if (tempNode->mRightChild != &msNilNode)
			{
				tempNode = tempNode->mRightChild;
			}
			else
			{
				BinarySearchTreeNode* deleteNode = tempNode;
				tempNode = tempNode->mParent;

				if (tempNode->mLeftChild == deleteNode)
				{
					tempNode->mLeftChild = &msNilNode;
				}
				else
				{
					tempNode->mRightChild = &msNilNode;
				}

				mPool->Deallocate(deleteNode, sizeof(BinarySearchTreeNode));
			}
		}

		mPool->Deallocate(tempNode, sizeof(BinarySearchTreeNode));
		mRootNode = nullptr;
	}

	constexpr bool BinarySearchTree::Insert(void* item)
	{
		BinarySearchTreeNode* insertNode = nullptr;
		BinarySearchTreeNode* tempNode = mRootNode;
		BinarySearchTreeNode* parentTempNode = tempNode;

		while (tempNode != &msNilNode && tempNode != nullptr)
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
				return false;
			}
		}

		++mSize;
		insertNode = reinterpret_cast<BinarySearchTreeNode*>(mPool->Allocate(sizeof(BinarySearchTreeNode)));
		insertNode->mItem = item;
		insertNode->mLeftChild = &msNilNode;
		insertNode->mRightChild = &msNilNode;
		insertNode->mParent = parentTempNode;
		insertNode->mColor = eBinarySearchTreeColor::RED;

		if (parentTempNode == nullptr)
		{
			insertNode->mColor = eBinarySearchTreeColor::BLACK;
			mRootNode = insertNode;
		}
		else
		{
			if (item < parentTempNode->mItem)
			{
				parentTempNode->mLeftChild = insertNode;
			}
			else if (item > parentTempNode->mItem)
			{
				parentTempNode->mRightChild = insertNode;
			}
		}

		InsertColorFix(insertNode);

		return true;
	}

	constexpr bool BinarySearchTree::Delete(void* item)
	{
		BinarySearchTreeNode* deleteNode = GetItemNode(item);
		BinarySearchTreeNode* childNode = nullptr;

		if (deleteNode == &msNilNode)
		{
			return false;
		}


		if((deleteNode->mLeftChild != &msNilNode) && (deleteNode->mRightChild != &msNilNode))
		{
			deleteNode->mItem = GetNextNode(deleteNode)->mItem;
			deleteNode = GetNextNode(deleteNode);
		}

		if (deleteNode->mLeftChild != &msNilNode)
		{
			childNode = deleteNode->mLeftChild;
		}
		else
		{
			childNode = deleteNode->mRightChild;
		}

		if (deleteNode == mRootNode)
		{
			if (childNode == &msNilNode)
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

			if (childNode != &msNilNode)
			{
				childNode->mParent = deleteNode->mParent;
			}
		}

		if (deleteNode->mColor == eBinarySearchTreeColor::BLACK && mRootNode != nullptr)
		{
			DeleteColorFix(childNode, deleteNode->mParent);
		}

		--mSize;
		mPool->Deallocate(deleteNode, sizeof(BinarySearchTreeNode));

		return true;
	}

	constexpr bool BinarySearchTree::Search(void* item)
	{
		BinarySearchTreeNode* searchNode = GetItemNode(item);

		if (searchNode != &msNilNode)
		{
			return true;
		}

		return false;
	}

	constexpr size_t BinarySearchTree::GetSize() const
	{
		return mSize;
	}

	constexpr BinarySearchTreeNode* BinarySearchTree::GetItemNode(void* item)
	{
		BinarySearchTreeNode* itemNode = mRootNode;

		if (mRootNode == nullptr)
		{
			itemNode = &msNilNode;
		}

		while (itemNode != &msNilNode)
		{
			if (item < itemNode->mItem)
			{
				itemNode = itemNode->mLeftChild;
			}
			else if (item > itemNode->mItem)
			{
				itemNode = itemNode->mRightChild;
			}
			else
			{
				break;
			}
		}

		return itemNode;
	}

	constexpr BinarySearchTreeNode* BinarySearchTree::GetNextNode(BinarySearchTreeNode* node)
	{
		node = node->mRightChild;

		while (node->mLeftChild != &msNilNode)
		{
			node = node->mLeftChild;
		}

		return node;
	}

	constexpr void BinarySearchTree::LeftRotation(BinarySearchTreeNode* node)
	{
		BinarySearchTreeNode* rightChild = node->mRightChild;

		node->mRightChild = rightChild->mLeftChild;
		rightChild->mLeftChild->mParent = node;

		rightChild->mParent = node->mParent;

		if (node == mRootNode)
		{
			mRootNode = rightChild;
		}
		else if (node->mParent->mLeftChild == node)
		{
			node->mParent->mLeftChild = rightChild;
		}
		else
		{
			node->mParent->mRightChild = rightChild;
		}

		rightChild->mLeftChild = node;
		node->mParent = rightChild;
	}

	constexpr void BinarySearchTree::RightRotation(BinarySearchTreeNode* node)
	{
		BinarySearchTreeNode* leftChild = node->mLeftChild;

		node->mLeftChild = leftChild->mRightChild;
		leftChild->mRightChild->mParent = node;

		leftChild->mParent = node->mParent;

		if (node == mRootNode)
		{
			mRootNode = leftChild;
		}
		else if (node->mParent->mLeftChild == node)
		{
			node->mParent->mLeftChild = leftChild;
		}
		else
		{
			node->mParent->mRightChild = leftChild;
		}

		leftChild->mRightChild = node;
		node->mParent = leftChild;
	}

	constexpr void BinarySearchTree::InsertColorFix(BinarySearchTreeNode* node)
	{
		BinarySearchTreeNode* parentNode;
		BinarySearchTreeNode* uncleNode;

		while (node != mRootNode && node->mParent->mColor == eBinarySearchTreeColor::RED)
		{
			parentNode = node->mParent;

			if (parentNode->mParent->mLeftChild == parentNode)
			{
				uncleNode = parentNode->mParent->mRightChild;
			}
			else
			{
				uncleNode = parentNode->mParent->mLeftChild;
			}

			if (uncleNode->mColor == eBinarySearchTreeColor::BLACK)
			{
				bool isParentNodeLeftChild = parentNode == parentNode->mParent->mLeftChild;
				bool isNodeLeftChild = node == parentNode->mLeftChild;

				if (isParentNodeLeftChild)
				{
					if (!isNodeLeftChild)
					{
						LeftRotation(parentNode);
						BinarySearchTreeNode* tempNode = node;
						node = parentNode;
						parentNode = tempNode;
					}

					RightRotation(parentNode->mParent);

					parentNode->mColor = eBinarySearchTreeColor::BLACK;
					parentNode->mRightChild->mColor = eBinarySearchTreeColor::RED;
				}
				else
				{
					if (isNodeLeftChild)
					{
						RightRotation(parentNode);
						BinarySearchTreeNode* tempNode = node;
						node = parentNode;
						parentNode = tempNode;
					}

					LeftRotation(parentNode->mParent);

					parentNode->mColor = eBinarySearchTreeColor::BLACK;
					parentNode->mLeftChild->mColor = eBinarySearchTreeColor::RED;
				}

				break;
			}
			else
			{
				uncleNode->mColor = eBinarySearchTreeColor::BLACK;
				parentNode->mColor = eBinarySearchTreeColor::BLACK;

				parentNode->mParent->mColor = eBinarySearchTreeColor::RED;

				node = parentNode->mParent;
			}
		}

		mRootNode->mColor = eBinarySearchTreeColor::BLACK;
		
	}

	constexpr void BinarySearchTree::DeleteColorFix(BinarySearchTreeNode* node, BinarySearchTreeNode* parentNode)
	{
		BinarySearchTreeNode* cousinNode;

		while (node != mRootNode && node->mColor == eBinarySearchTreeColor::BLACK)
		{
			if (parentNode->mLeftChild == node)
			{
				cousinNode = parentNode->mRightChild;

				if (cousinNode->mColor == eBinarySearchTreeColor::RED)
				{
					cousinNode->mColor = eBinarySearchTreeColor::BLACK;
					parentNode->mColor = eBinarySearchTreeColor::RED;
					LeftRotation(parentNode);

					cousinNode = parentNode->mRightChild;
				}

				if (cousinNode->mLeftChild->mColor == eBinarySearchTreeColor::RED && cousinNode->mRightChild->mColor == eBinarySearchTreeColor::BLACK)
				{
					cousinNode->mColor = eBinarySearchTreeColor::RED;
					cousinNode->mLeftChild->mColor = eBinarySearchTreeColor::BLACK;
					RightRotation(cousinNode);

					cousinNode = cousinNode->mParent;
				}

				if (cousinNode->mRightChild->mColor == eBinarySearchTreeColor::RED)
				{
					cousinNode->mColor = parentNode->mColor;
					parentNode->mColor = eBinarySearchTreeColor::BLACK;
					cousinNode->mRightChild->mColor = eBinarySearchTreeColor::BLACK;
					LeftRotation(parentNode);

					break;
				}
				else
				{
					cousinNode->mColor = eBinarySearchTreeColor::RED;
					node = parentNode;
					parentNode = parentNode->mParent;
				}
			}
			else
			{
				cousinNode = parentNode->mLeftChild;

				if (cousinNode->mColor == eBinarySearchTreeColor::RED)
				{
					cousinNode->mColor = eBinarySearchTreeColor::BLACK;
					parentNode->mColor = eBinarySearchTreeColor::RED;
					RightRotation(parentNode);

					cousinNode = parentNode->mLeftChild;
				}

				if (cousinNode->mRightChild->mColor == eBinarySearchTreeColor::RED && cousinNode->mLeftChild->mColor == eBinarySearchTreeColor::BLACK)
				{
					cousinNode->mColor = eBinarySearchTreeColor::RED;
					cousinNode->mRightChild->mColor = eBinarySearchTreeColor::BLACK;
					LeftRotation(cousinNode);

					cousinNode = cousinNode->mParent;
				}

				if (cousinNode->mLeftChild->mColor == eBinarySearchTreeColor::RED)
				{
					cousinNode->mColor = parentNode->mColor;
					parentNode->mColor = eBinarySearchTreeColor::BLACK;
					cousinNode->mLeftChild->mColor = eBinarySearchTreeColor::BLACK;
					RightRotation(parentNode);

					break;
				}
				else
				{
					cousinNode->mColor = eBinarySearchTreeColor::RED;
					node = parentNode;
					parentNode = parentNode->mParent;
				}
			}
		}

		node->mColor = eBinarySearchTreeColor::BLACK;
	}

#ifdef CAVE_BUILD_DEBUG

	void BinarySearchTree::PrintInt32()
	{
		LOGD(eLogChannel::CORE_CONTAINER, "");
		PrintInt32Recursive(mRootNode, 0, 10);
		LOGD(eLogChannel::CORE_CONTAINER, "");
	}

	void BinarySearchTree::PrintInt32Recursive(BinarySearchTreeNode* node, size_t space, size_t height)
	{
		// Base case
		if (node == &msNilNode) {
			return;
		}

		String outputString;

		// increase distance between levels
		space += height;

		// print right child first
		PrintInt32Recursive(node->mRightChild, space, 10);
		LOGD(eLogChannel::CORE_CONTAINER, "");

		// print the current node after padding with spaces
		for (int i = height; i < space; i++) {
			outputString += ' ';
		}

		LOGDF(eLogChannel::CORE_CONTAINER, "%s%d", outputString.GetCString(), *reinterpret_cast<int32_t*>(node->mItem));

		PrintInt32Recursive(node->mLeftChild, space, 10);
	}

	size_t BinarySearchTree::GetHeight()
	{
		return GetHeightRecursive(mRootNode);
	}

	size_t BinarySearchTree::GetHeightRecursive(BinarySearchTreeNode* node)
	{
		if (node == &msNilNode)
		{
			return 0;
		}

		size_t leftHeight = GetHeightRecursive(node->mLeftChild);
		size_t rightHeight = GetHeightRecursive(node->mRightChild);
		if (leftHeight > rightHeight)
		{
			return leftHeight + 1;
		}
		else
		{
			return rightHeight + 1;
		}
	}
	
	constexpr bool BinarySearchTree::ColorCheck()
	{
		bool colorCheck = true;

		ColorCheckRecursive(mRootNode, colorCheck);

		return colorCheck;
	}

	constexpr int32_t BinarySearchTree::ColorCheckRecursive(BinarySearchTreeNode* node, bool& colorCheck)
	{
		int32_t leftBlackCount;

		if (node == &msNilNode)
		{
			return 1;
		}

		if (!colorCheck)
		{
			return 0;
		}

		if (node->mParent != nullptr && node->mParent->mColor == eBinarySearchTreeColor::RED && node->mColor == eBinarySearchTreeColor::RED)
		{
			colorCheck = false;
			return 0;
		}

		leftBlackCount = ColorCheckRecursive(node->mLeftChild, colorCheck);
		colorCheck = leftBlackCount == ColorCheckRecursive(node->mRightChild, colorCheck);

		if (node->mColor == eBinarySearchTreeColor::BLACK)
		{
			return leftBlackCount + 1;
		}
		
		return leftBlackCount;
	}

#endif

#ifdef CAVE_BUILD_DEBUG
	namespace BinarySearchTreeTest
	{
		int32_t* itemTable;

		size_t* insertCount;
		size_t* deleteCount;
		size_t* searchCount;

		size_t tableSize;

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
					size_t index = rand() % tableSize;

					if (tree.Insert(&itemTable[index]))
					{
						//LOGDF(eLogChannel::CORE_CONTAINER, "+%d", itemTable[index]);
					}
				}
			}

			void Delete(BinarySearchTree& tree, size_t count)
			{
				for (size_t i = 0; i < deleteCount[count]; ++i)
				{
					size_t index = rand() % tableSize;

					if (tree.Delete(&itemTable[index]))
					{
						//LOGDF(eLogChannel::CORE_CONTAINER, "-%d", itemTable[index]);
					}
				}
			}

			void Search(BinarySearchTree& tree, size_t count)
			{
				for (size_t i = 0; i < searchCount[count]; ++i)
				{
					size_t index = rand() % tableSize;

					LOGDF(eLogChannel::CORE_CONTAINER, "Search: %d | %d", itemTable[index], tree.Search(&itemTable[index]));
				}
			}
		}

		void Test(size_t containerTableSize, size_t containerTestCount, uint8_t containerTestCase)
		{
			srand(time(NULL));

			tableSize = containerTableSize;

			BinarySearchTree tree;

			itemTable = reinterpret_cast<int32_t*>(gCoreMemoryPool.Allocate(sizeof(int32_t) * tableSize));

			insertCount = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * containerTestCount));
			deleteCount = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * containerTestCount));
			searchCount = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * containerTestCount));

			for (size_t i = 0; i < containerTestCount; ++i)
			{

				insertCount[i] = rand() % 100 + 1;
				deleteCount[i] = rand() % 200 + 1;
				searchCount[i] = rand() % 1 + 1;
			}

			for (size_t i = 0; i < tableSize; ++i)
			{
				itemTable[i] = rand();
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
				size_t sizeHeight = 0;
				for (sizeHeight; (1 << sizeHeight) < tree.GetSize(); ++sizeHeight);

				LOGDF(eLogChannel::CORE_CONTAINER, "Size: %d, SizeHeight : %d, Height: %d,", tree.GetSize(), sizeHeight, tree.GetHeight());
			}

			gCoreMemoryPool.Deallocate(itemTable, sizeof(int32_t) * tableSize);

			gCoreMemoryPool.Deallocate(insertCount, sizeof(size_t) * containerTestCount);
			gCoreMemoryPool.Deallocate(deleteCount, sizeof(size_t) * containerTestCount);
			gCoreMemoryPool.Deallocate(searchCount, sizeof(size_t) * containerTestCount);
		}
	}
#endif
}