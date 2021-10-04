/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#ifdef CAVE_BUILD_DEBUG

#include "Debug/Log.h"

#endif

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"
#include "Utils/Crt.h"

import cave.Core.Containers.CompareItemType;
import cave.Core.Containers.Queue;
#ifdef CAVE_BUILD_DEBUG

import cave.Core.String;

#endif


namespace cave
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

		constexpr BinarySearchTreeNode(void* item, BinarySearchTreeNode* parent, BinarySearchTreeNode* nilNode)
		{
			mItem = item;
			mColor = eBinarySearchTreeColor::RED;
			mLeftChild = nilNode;
			mRightChild = nilNode;
			mParent = parent;
		}
	};

	class BinarySearchTree final
	{
	public:
		constexpr BinarySearchTree();
		constexpr BinarySearchTree(CompareItem::Type compareMethod);
		constexpr BinarySearchTree(MemoryPool& pool);
		constexpr BinarySearchTree(CompareItem::Type compareMethod, MemoryPool& pool);
		constexpr BinarySearchTree(const BinarySearchTree& other);
		constexpr BinarySearchTree(const BinarySearchTree& other, CompareItem::Type compareMethod);
		constexpr BinarySearchTree(const BinarySearchTree& other, MemoryPool& pool);
		constexpr BinarySearchTree(const BinarySearchTree& other, CompareItem::Type compareMethod, MemoryPool& pool);
		constexpr BinarySearchTree(BinarySearchTree&& other);

		~BinarySearchTree();

		constexpr BinarySearchTree& operator=(const BinarySearchTree& other);
		constexpr BinarySearchTree& operator=(BinarySearchTree&& other);

		constexpr bool Insert(void* item);
		constexpr bool Delete(void* item);
		constexpr bool Search(void* item);

		constexpr void Clear();

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
		constexpr void ClearSubTree(BinarySearchTreeNode*& node);

#ifdef CAVE_BUILD_DEBUG
		void PrintInt32Recursive(BinarySearchTreeNode* node, size_t space, size_t height);
		constexpr int32_t ColorCheckRecursive(BinarySearchTreeNode* node, bool& colorCheck);
		size_t GetHeightRecursive(BinarySearchTreeNode* node);
#endif
	public:
		static BinarySearchTreeNode msNilNode;

	private:
		MemoryPool* mPool;
		CompareItem::Type mCompareMethod;
		BinarySearchTreeNode* mRootNode;
		size_t mSize;
	};

	BinarySearchTreeNode BinarySearchTree::msNilNode = BinarySearchTreeNode();

	constexpr BinarySearchTree::BinarySearchTree()
		: BinarySearchTree(CompareItem::DefaultFunction, gCoreMemoryPool)
	{ }

	constexpr BinarySearchTree::BinarySearchTree(CompareItem::Type compareMethod)
		: BinarySearchTree(compareMethod, gCoreMemoryPool)
	{ }


	constexpr BinarySearchTree::BinarySearchTree(MemoryPool& pool)
		: BinarySearchTree(CompareItem::DefaultFunction, pool)
	{ }

	constexpr BinarySearchTree::BinarySearchTree(CompareItem::Type compareMethod, MemoryPool& pool)
		: mPool(&pool)
		, mCompareMethod(compareMethod)
		, mRootNode(&msNilNode)
		, mSize(0)
	{ }

	constexpr BinarySearchTree::BinarySearchTree(const BinarySearchTree& other)
		: BinarySearchTree(other, other.mCompareMethod, *other.mPool)
	{ }

	constexpr BinarySearchTree::BinarySearchTree(const BinarySearchTree& other, CompareItem::Type compareMethod)
		: BinarySearchTree(other, compareMethod, *other.mPool)
	{ }

	constexpr BinarySearchTree::BinarySearchTree(const BinarySearchTree& other, MemoryPool& pool)
		: BinarySearchTree(other, other.mCompareMethod, pool)
	{ }

	constexpr BinarySearchTree::BinarySearchTree(const BinarySearchTree& other, CompareItem::Type compareMethod, MemoryPool& pool)
		: mPool(&pool)
		, mCompareMethod(compareMethod)
		, mRootNode(&msNilNode)
		, mSize(other.mSize)
	{
		if (other.mRootNode == &msNilNode)
		{
			return;
		}

		Queue getterNodeQueue;
		Queue setterNodeQueue;

		
		mRootNode = reinterpret_cast<BinarySearchTreeNode*>(mPool->Allocate(sizeof(BinarySearchTreeNode)));
		new(mRootNode) BinarySearchTreeNode(other.mRootNode->mItem, &msNilNode, &msNilNode);

		getterNodeQueue.Enqueue(other.mRootNode);
		setterNodeQueue.Enqueue(mRootNode);

		while (getterNodeQueue.GetSize() > 0)
		{
			BinarySearchTreeNode* getterNode = reinterpret_cast<BinarySearchTreeNode*>(getterNodeQueue.GetTop());
			BinarySearchTreeNode* setterNode = reinterpret_cast<BinarySearchTreeNode*>(setterNodeQueue.GetTop());
			getterNodeQueue.Dequeue();
			setterNodeQueue.Dequeue();

			if (getterNode->mLeftChild != &msNilNode)
			{
				BinarySearchTreeNode* newNode = reinterpret_cast<BinarySearchTreeNode*>(mPool->Allocate(sizeof(BinarySearchTreeNode)));
				new(newNode) BinarySearchTreeNode(getterNode->mLeftChild->mItem, setterNode, &msNilNode);
				setterNode->mLeftChild = newNode;
				getterNodeQueue.Enqueue(getterNode->mLeftChild);
				setterNodeQueue.Enqueue(setterNode->mLeftChild);
			}

			if (getterNode->mRightChild != &msNilNode)
			{
				BinarySearchTreeNode* newNode = reinterpret_cast<BinarySearchTreeNode*>(mPool->Allocate(sizeof(BinarySearchTreeNode)));
				new(newNode) BinarySearchTreeNode(getterNode->mRightChild->mItem, setterNode, &msNilNode);
				setterNode->mRightChild = newNode;
				getterNodeQueue.Enqueue(getterNode->mRightChild);
				setterNodeQueue.Enqueue(setterNode->mRightChild);
			}
		}
	}

	constexpr BinarySearchTree::BinarySearchTree(BinarySearchTree&& other)
		: mPool(other.mPool)
		, mCompareMethod(other.mCompareMethod)
		, mRootNode(other.mRootNode)
		, mSize(other.mSize)
	{
		other.mRootNode = &msNilNode;
		other.mSize = 0;
	}

	BinarySearchTree::~BinarySearchTree()
	{
		Clear();
	}

	constexpr BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other)
	{
		if (this == &other)
		{
			return *this;
		}

		if (other.mRootNode == &msNilNode)
		{
			Clear();
			return *this;
		}

		Queue getterNodeQueue;
		Queue setterNodeQueue;

		if (mRootNode == &msNilNode)
		{
			mRootNode = reinterpret_cast<BinarySearchTreeNode*>(mPool->Allocate(sizeof(BinarySearchTreeNode)));
			new(mRootNode) BinarySearchTreeNode(other.mRootNode->mItem, &msNilNode, &msNilNode);
		}
		else
		{
			mRootNode->mItem = other.mRootNode->mItem;
		}

		getterNodeQueue.Enqueue(other.mRootNode);
		setterNodeQueue.Enqueue(mRootNode);

		while (getterNodeQueue.GetSize() > 0)
		{
			BinarySearchTreeNode* getterNode = reinterpret_cast<BinarySearchTreeNode*>(getterNodeQueue.GetTop());
			BinarySearchTreeNode* setterNode = reinterpret_cast<BinarySearchTreeNode*>(setterNodeQueue.GetTop());
			getterNodeQueue.Dequeue();
			setterNodeQueue.Dequeue();

			if (getterNode->mLeftChild != &msNilNode)
			{
				if (setterNode->mLeftChild != &msNilNode)
				{
					setterNode->mLeftChild->mItem = getterNode->mLeftChild->mItem;
				}
				else
				{
					BinarySearchTreeNode* newNode = reinterpret_cast<BinarySearchTreeNode*>(mPool->Allocate(sizeof(BinarySearchTreeNode)));
					new(newNode) BinarySearchTreeNode(getterNode->mLeftChild->mItem, setterNode, &msNilNode);
					setterNode->mLeftChild = newNode;
				}
				getterNodeQueue.Enqueue(getterNode->mLeftChild);
				setterNodeQueue.Enqueue(setterNode->mLeftChild);
			}
			else if (setterNode->mLeftChild != &msNilNode)
			{
				ClearSubTree(setterNode->mLeftChild);
			}

			if (getterNode->mRightChild != &msNilNode)
			{
				if (setterNode->mRightChild != &msNilNode)
				{
					setterNode->mRightChild->mItem = getterNode->mRightChild->mItem;
				}
				else
				{
					BinarySearchTreeNode* newNode = reinterpret_cast<BinarySearchTreeNode*>(mPool->Allocate(sizeof(BinarySearchTreeNode)));
					new(newNode) BinarySearchTreeNode(getterNode->mRightChild->mItem, setterNode, &msNilNode);
					setterNode->mRightChild = newNode;
				}
				getterNodeQueue.Enqueue(getterNode->mRightChild);
				setterNodeQueue.Enqueue(setterNode->mRightChild);
			}
			else if (setterNode->mRightChild != &msNilNode)
			{
				ClearSubTree(setterNode->mRightChild);
			}
		}

		return *this;
	}

	constexpr BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree&& other)
	{
		if (this == &other)
		{
			return *this;
		}

		MemoryPool* tempPool = mPool;
		CompareItem::Type tempCompareMethod = mCompareMethod;
		BinarySearchTreeNode* tempRootNode = mRootNode;
		size_t tempSize = mSize;

		mPool = other.mPool;
		mCompareMethod = other.mCompareMethod;
		mRootNode = other.mRootNode;
		mSize = other.mSize;

		other.mPool = tempPool;
		other.mCompareMethod = tempCompareMethod;
		other.mRootNode = tempRootNode;
		other.mSize = tempSize;

		return *this;
	}

	constexpr bool BinarySearchTree::Insert(void* item)
	{
		assert(item != nullptr);
		
		BinarySearchTreeNode* insertNode = nullptr;
		BinarySearchTreeNode* tempNode = mRootNode;
		BinarySearchTreeNode* parentTempNode = tempNode;

		while (tempNode != &msNilNode)
		{
			parentTempNode = tempNode;

			if (mCompareMethod(item, tempNode->mItem) == eCompareItem::LESS)
			{
				tempNode = tempNode->mLeftChild;
			}
			else if (mCompareMethod(item, tempNode->mItem) == eCompareItem::GREATER)
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
		new(insertNode) BinarySearchTreeNode(item, parentTempNode, &msNilNode);

		if (parentTempNode == &msNilNode)
		{
			insertNode->mColor = eBinarySearchTreeColor::BLACK;
			mRootNode = insertNode;
		}
		else
		{
			if (mCompareMethod(item, parentTempNode->mItem) == eCompareItem::LESS)
			{
				parentTempNode->mLeftChild = insertNode;
			}
			else if (mCompareMethod(item, parentTempNode->mItem) == eCompareItem::GREATER)
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


		if ((deleteNode->mLeftChild != &msNilNode) && (deleteNode->mRightChild != &msNilNode))
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
				mRootNode = &msNilNode;
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

		if (deleteNode->mColor == eBinarySearchTreeColor::BLACK && mRootNode != &msNilNode)
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

	constexpr void BinarySearchTree::Clear()
	{
		ClearSubTree(mRootNode);
	}

	constexpr size_t BinarySearchTree::GetSize() const
	{
		return mSize;
	}

	constexpr BinarySearchTreeNode* BinarySearchTree::GetItemNode(void* item)
	{
		BinarySearchTreeNode* itemNode = mRootNode;

		while (itemNode != &msNilNode)
		{
			if (mCompareMethod(item, itemNode->mItem) == eCompareItem::LESS)
			{
				itemNode = itemNode->mLeftChild;
			}
			else if (mCompareMethod(item, itemNode->mItem) == eCompareItem::GREATER)
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

	constexpr void BinarySearchTree::ClearSubTree(BinarySearchTreeNode*& node)
	{
		BinarySearchTreeNode* tempNode = node;
		size_t deleteCount = 0;

		if (tempNode == &msNilNode)
		{
			return;
		}

		while (tempNode != node || (tempNode->mLeftChild != &msNilNode) || (tempNode->mRightChild != &msNilNode))
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
				++deleteCount;
			}
		}

		mPool->Deallocate(tempNode, sizeof(BinarySearchTreeNode));
		++deleteCount;
		node = &msNilNode;
		mSize -= deleteCount;
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

		constexpr uint8_t TEST_ALL = 0b11111111;
		constexpr uint8_t TEST_INSERT = 0b00000001;
		constexpr uint8_t TEST_DELETE = 0b00000010;
		constexpr uint8_t TEST_SEARCH = 0b00000100;

		size_t tableSize = 10000;
		size_t testCount = 10;
		uint8_t testCase = TEST_INSERT | TEST_DELETE;
		BinarySearchTree* caveTreePointer = nullptr;

		void Test();

		eCompareItem TestCompareMethod(void* leftItem, void* rightItem)
		{
			int32_t leftInt = *reinterpret_cast<int32_t*>(leftItem);
			int32_t rightInt = *reinterpret_cast<int32_t*>(rightItem);

			if (leftInt < rightInt)
			{
				return eCompareItem::LESS;
			}

			if (leftInt > rightInt)
			{
				return eCompareItem::GREATER;
			}

			return eCompareItem::EQUAL;
		}	

		namespace Container
		{
			void Insert()
			{
				size_t insertCount = rand() % 32 + 1;	

				for (size_t i = 0; i < insertCount; ++i)
				{
					size_t index = rand() % tableSize;

					if (caveTreePointer->Insert(&itemTable[index]))
					{
						//LOGDF(eLogChannel::CORE_CONTAINER, "+%d", itemTable[index]);
					}
				}
			}

			void Delete()
			{
				size_t deleteCount = rand() % 16 + 1;

				for (size_t i = 0; i < deleteCount; ++i)
				{
					size_t index = rand() % tableSize;

					if (caveTreePointer->Delete(&itemTable[index]))
					{
						//LOGDF(eLogChannel::CORE_CONTAINER, "-%d", itemTable[index]);
					}
				}
			}

			void Search()
			{
				size_t searchCount = rand() % 16 + 1; 

				for (size_t i = 0; i < searchCount; ++i)
				{
					size_t index = rand() % tableSize;

					LOGDF(eLogChannel::CORE_CONTAINER, "Search: %d | %d", itemTable[index], caveTreePointer->Search(&itemTable[index]));
				}
			}
		}

		void Test()
		{
			srand(time(NULL));

			BinarySearchTree caveTree(TestCompareMethod);
			caveTreePointer = &caveTree;


			itemTable = reinterpret_cast<int32_t*>(gCoreMemoryPool.Allocate(sizeof(int32_t) * tableSize));

			for (size_t i = 0; i < tableSize; ++i)
			{
				itemTable[i] = i;
			}

			for (size_t i = 0; i < testCount; ++i)
			{
				if (testCase & TEST_INSERT)
				{
					Container::Insert();
				}

				if (testCase & TEST_DELETE)
				{
					Container::Delete();
				}

				if (testCase & TEST_SEARCH)
				{
					Container::Search();
				}

				caveTree.PrintInt32();
				BinarySearchTree copyConstructTree = caveTree;
				copyConstructTree.PrintInt32();
				BinarySearchTree copyAssignTree;
				copyAssignTree = caveTree;
				copyAssignTree.PrintInt32();
				//size_t sizeHeight = 0;
				//for (sizeHeight; (1 << sizeHeight) < tree.GetSize(); ++sizeHeight);

				//LOGDF(eLogChannel::CORE_CONTAINER, "Size: %d, SizeHeight : %d, Height: %d,", tree.GetSize(), sizeHeight, tree.GetHeight());
			}

			gCoreMemoryPool.Deallocate(itemTable, sizeof(int32_t) * tableSize);	
		}
	}
#endif
}