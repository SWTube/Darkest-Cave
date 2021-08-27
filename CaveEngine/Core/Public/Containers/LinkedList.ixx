/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module cave.Core.Containers.LinkedList;

import IteratorType;
import cave.Core.Memory.Memory;

export namespace cave
{
	
	struct LinkedListNode {
		void* mElement;
		LinkedListNode* mNext;
		LinkedListNode* mPrev;
	};

	class LinkedList;
	
	class LinkedListConstIterator
	{
	public:
		friend class LinkedList;

		constexpr LinkedListConstIterator();
		constexpr LinkedListConstIterator(LinkedList& container, size_t startIndex);
		constexpr LinkedListConstIterator(const LinkedListConstIterator& other);

		constexpr LinkedListConstIterator& operator=(const LinkedListConstIterator& other);

		constexpr LinkedListConstIterator& operator++();
		constexpr LinkedListConstIterator operator++(int);

		constexpr LinkedListConstIterator& operator--();
		constexpr LinkedListConstIterator operator--(int);

		constexpr const void* operator*();

		constexpr bool operator==(const LinkedListConstIterator& other);
		constexpr bool operator!=(const LinkedListConstIterator& other);
	protected:
		constexpr LinkedListConstIterator(LinkedListNode* node);

	private:
		LinkedListNode* mNode;
	};

	
	class LinkedListIterator final : public LinkedListConstIterator
	{
	public:
		friend class LinkedList;

		using Base = LinkedListConstIterator;

		constexpr LinkedListIterator();
		constexpr LinkedListIterator(LinkedList& container, size_t startIndex);
		constexpr LinkedListIterator(const LinkedListConstIterator& other);

		constexpr LinkedListIterator& operator=(const LinkedListConstIterator& other);

		constexpr LinkedListIterator& operator++();
		constexpr LinkedListIterator operator++(int);

		constexpr LinkedListIterator& operator--();
		constexpr LinkedListIterator operator--(int);

		constexpr void* operator*();

	protected:
		constexpr LinkedListIterator(LinkedListNode* node);
	};

	
	class LinkedList final
	{
	public:
		using ConstIterator = LinkedListConstIterator;
		using Iterator = LinkedListIterator;

		LinkedList();
		LinkedList(MemoryPool& pool);
		LinkedList(size_t count, void* item);
		LinkedList(size_t count, void* item, MemoryPool& pool);
		LinkedList(const LinkedList& other);
		LinkedList(const LinkedList& other, MemoryPool& pool);
		LinkedList(LinkedList&& other);
		LinkedList(std::initializer_list<void*> initializerList);
		LinkedList(std::initializer_list<void*> initializerList, MemoryPool& pool);

		constexpr LinkedList& operator=(const LinkedList& other);
		constexpr LinkedList& operator=(LinkedList&& other);

		constexpr bool operator==(const LinkedList& other);
		constexpr bool operator!=(const LinkedList& other);

		~LinkedList();
		
		constexpr void Clear();

		constexpr void Swap(LinkedList& other);

		Iterator Insert(ConstIterator position, void* item);
		Iterator Insert(ConstIterator position, size_t count, void* item);

		Iterator Delete(ConstIterator position);
		Iterator Delete(ConstIterator first, ConstIterator last);

		void InsertFront(void* item);
		void InsertBack(void* item);

		void DeleteFront();
		void DeleteBack();

		constexpr bool IsEmpty() const;

		constexpr void* GetFront();
		constexpr const void* GetFront() const;

		constexpr void* GetBack();
		constexpr const void* GetBack() const;

		constexpr size_t GetSize() const;
		constexpr size_t GetMaxSize() const;

		constexpr Iterator begin();
		constexpr Iterator end();

		constexpr ConstIterator cbegin();
		constexpr ConstIterator cend();

		constexpr Iterator GetBeginIterator();
		constexpr Iterator GetEndIterator();

		constexpr ConstIterator GetBeginConstIterator();
		constexpr ConstIterator GetEndConstIterator();

	private:
		MemoryPool* mPool;
		LinkedListNode* mHead;
		LinkedListNode* mTail;
		size_t mSize;
	};

	/*
	*
	* TSinglyListConstIterator
	* 
	*/

	
	constexpr LinkedListConstIterator::LinkedListConstIterator()
		: mNode(nullptr)
	{ }

	
	constexpr LinkedListConstIterator::LinkedListConstIterator(LinkedList& container, size_t startIndex)
	{
		mNode = container.GetBeginIterator().mNode;

		for (size_t i = 0; i < startIndex; ++i)
		{
			mNode = mNode->mNext;
		}
	}

	
	constexpr LinkedListConstIterator::LinkedListConstIterator(LinkedListNode* node)
		: mNode(node)
	{ }

	
	constexpr LinkedListConstIterator::LinkedListConstIterator(const LinkedListConstIterator& other)
		: mNode(other.mNode)
	{ }

	
	constexpr LinkedListConstIterator& LinkedListConstIterator::operator=(const LinkedListConstIterator& other)
	{
		mNode = other.mNode;

		return *this;
	}

	
	constexpr LinkedListConstIterator& LinkedListConstIterator::operator++()
	{
		mNode = mNode->mNext;

		return *this;
	}

	
	constexpr LinkedListConstIterator LinkedListConstIterator::operator++(int)
	{
		LinkedListConstIterator returnIterator = *this;
		mNode = mNode->mNext;

		return returnIterator;
	}

	
	constexpr LinkedListConstIterator& LinkedListConstIterator::operator--()
	{
		mNode = mNode->mPrev;

		return *this;
	}

	
	constexpr LinkedListConstIterator LinkedListConstIterator::operator--(int)
	{
		LinkedListConstIterator returnIterator = *this;
		mNode = mNode->mPrev;

		return returnIterator;
	}

	
	constexpr const void* LinkedListConstIterator::operator*()
	{
		return mNode->mElement;
	}

	
	constexpr bool LinkedListConstIterator::operator==(const LinkedListConstIterator& other)
	{
		return mNode == other.mNode;
	}

	
	constexpr bool LinkedListConstIterator::operator!=(const LinkedListConstIterator& other)
	{
		return mNode != other.mNode;
	}

	/*
	*
	* TSinglyListIterator
	*
	*/

	
	constexpr LinkedListIterator::LinkedListIterator()
		: Base()
	{ }

	
	constexpr LinkedListIterator::LinkedListIterator(LinkedList& container, size_t startIndex)
		: Base(container, startIndex)
	{ }

	
	constexpr LinkedListIterator::LinkedListIterator(LinkedListNode* node)
		: Base(node)
	{ }

	
	constexpr LinkedListIterator::LinkedListIterator(const LinkedListConstIterator& other)
		: Base(other)
	{ }

	
	constexpr LinkedListIterator& LinkedListIterator::operator=(const LinkedListConstIterator& other)
	{
		Base::operator=(other);

		return *this;
	}

	
	constexpr LinkedListIterator& LinkedListIterator::operator++()
	{
		Base::operator++();

		return *this;
	}

	
	constexpr LinkedListIterator LinkedListIterator::operator++(int)
	{
		LinkedListConstIterator returnIterator = *this;
		Base::operator++();

		return returnIterator;
	}

	
	constexpr LinkedListIterator& LinkedListIterator::operator--()
	{
		Base::operator--();

		return *this;
	}

	
	constexpr LinkedListIterator LinkedListIterator::operator--(int)
	{
		LinkedListConstIterator returnIterator = *this;
		Base::operator--();

		return returnIterator;
	}

	
	constexpr void* LinkedListIterator::operator*()
	{
		return const_cast<void*>(Base::operator*());
	}

	/*
	*
	* TSinglyList
	*
	*/

	
	LinkedList::LinkedList()
		: LinkedList(gCoreMemoryPool)
	{ }

	LinkedList::LinkedList(MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mTail(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mSize(0)
	{
		mHead->mNext = mTail;
		mHead->mPrev = nullptr;

		mTail->mPrev = mHead;
		mTail->mNext = nullptr;
	}

	LinkedList::LinkedList(size_t count, void* item)
		: LinkedList(count, item, gCoreMemoryPool)
	{ }

	LinkedList::LinkedList(size_t count, void* item, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mTail(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mSize(count)
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		LinkedListNode* prevNode = mHead;

		for (size_t i = 0; i < count; ++i)
		{
			LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));

			newNode->mElement = item;

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	LinkedList::LinkedList(const LinkedList& other)
		: LinkedList(other, gCoreMemoryPool)
	{ }

	LinkedList::LinkedList(const LinkedList& other, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mTail(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mSize(other.mSize)
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		LinkedListNode* otherNode = other.mHead;
		LinkedListNode* prevNode = mHead;

		while (otherNode->mNext != other.mTail)
		{
			otherNode = otherNode->mNext;

			LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));
			
			newNode->mElement = otherNode->mElement;

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	LinkedList::LinkedList(LinkedList&& other)
		: mPool(other.mPool)
		, mHead(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mTail(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mSize(other.mSize)
	{
		mHead->mNext = other.mHead->mNext;
		mHead->mPrev = nullptr;

		mTail->mPrev = other.mTail->mPrev;
		mTail->mNext = nullptr;

		other.mHead->mNext = other.mTail;
		other.mTail->mPrev = other.mHead;
	}

	LinkedList::LinkedList(std::initializer_list<void*> initializerList)
		: LinkedList(initializerList, gCoreMemoryPool)
	{ }

	
	LinkedList::LinkedList(std::initializer_list<void*> initializerList, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mTail(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mSize(0)
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		LinkedListNode* prevNode = mHead;

		for (auto iterator = initializerList.begin(); iterator != initializerList.end(); ++iterator)
		{
			LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));
			
			newNode->mElement = *iterator;

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;

			++mSize;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	
	constexpr LinkedList& LinkedList::operator=(const LinkedList& other)
	{
		if (*this != other)
		{
			LinkedListNode* setElementNode = mHead;
			LinkedListNode* getElementNode = other.mHead;

			while (setElementNode->mNext != mTail && getElementNode->mNext != other.mTail)
			{
				setElementNode = setElementNode->mNext;
				getElementNode = getElementNode->mNext;

				setElementNode->mElement = getElementNode->mElement;
			}

			if (setElementNode->mNext != mTail)
			{
				LinkedListNode* tempNode = setElementNode;

				setElementNode = setElementNode->mNext;

				while (setElementNode != mTail)
				{
					mPool->Deallocate(setElementNode, sizeof(LinkedListNode));
					setElementNode = setElementNode->mNext;
				}

				tempNode->mNext = mTail;
				mTail->mPrev = tempNode;
			}
			else
			{
				while (getElementNode->mNext != other.mTail)
				{
					getElementNode = getElementNode->mNext;

					LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));

					newNode->mElement = getElementNode->mElement;

					newNode->mPrev = setElementNode;
					setElementNode->mNext = newNode;

					setElementNode = newNode;
				}

				mTail->mPrev = setElementNode;
				setElementNode->mNext = mTail;
			}
		}

		mSize = other.mSize;

		return *this;
	}

	
	constexpr LinkedList& LinkedList::operator=(LinkedList&& other)
	{
		if (*this != other)
		{
			Swap(other);
		}

		return *this;
	}

	
	constexpr bool LinkedList::operator==(const LinkedList& other)
	{
		return (mHead == other.mHead);
	}

	
	constexpr bool LinkedList::operator!=(const LinkedList& other)
	{
		return (mHead != other.mHead);
	}

	
	LinkedList::~LinkedList()
	{
		LinkedListNode* tempNode;

		while (mHead != mTail)
		{
			tempNode = mHead;
			mHead = mHead->mNext;
			mPool->Deallocate(tempNode, sizeof(LinkedListNode));
		}

		mPool->Deallocate(mTail, sizeof(LinkedListNode));
	}

	
	constexpr bool LinkedList::IsEmpty() const
	{
		return (mHead->mNext == mTail);
	}

	
	constexpr void* LinkedList::GetFront()
	{
		assert(!IsEmpty());

		return mHead->mNext->mElement;
	}

	
	constexpr const void* LinkedList::GetFront() const
	{
		assert(!IsEmpty());

		return mHead->mNext->mElement;
	}

	
	constexpr void* LinkedList::GetBack()
	{
		assert(!IsEmpty());

		return mTail->mPrev->mElement;
	}

	
	constexpr const void* LinkedList::GetBack() const
	{
		assert(!IsEmpty());

		return mTail->mPrev->mElement;
	}

	
	constexpr size_t LinkedList::GetSize() const
	{
		return mSize;
	}

	
	constexpr size_t LinkedList::GetMaxSize() const
	{
		return mPool->GetFreeMemorySize() / sizeof(void*);
	}

	
	constexpr LinkedList::Iterator LinkedList::begin()
	{
		return Iterator(mHead->mNext);
	}

	
	constexpr LinkedList::Iterator LinkedList::end()
	{
		return Iterator(mTail);
	}

	constexpr LinkedList::ConstIterator LinkedList::cbegin()
	{
		return Iterator(mHead->mNext);
	}


	constexpr LinkedList::ConstIterator LinkedList::cend()
	{
		return Iterator(mTail);
	}

	
	constexpr LinkedList::Iterator LinkedList::GetBeginIterator()
	{
		return Iterator(mHead->mNext);
	}

	
	constexpr LinkedList::Iterator LinkedList::GetEndIterator()
	{
		return Iterator(mTail);
	}

	
	constexpr LinkedList::ConstIterator LinkedList::GetBeginConstIterator()
	{
		return ConstIterator(mHead->mNext);
	}

	
	constexpr LinkedList::ConstIterator LinkedList::GetEndConstIterator()
	{
		return ConstIterator(mTail);
	}

	
	constexpr void LinkedList::Clear()
	{
		while (mHead->mNext != mTail)
		{
			LinkedListNode* tempNode = mHead->mNext;
			mHead->mNext = mHead->mNext->mNext;

			mPool->Deallocate(tempNode, sizeof(LinkedListNode));
		}

		mSize = 0;

		mTail->mPrev = mHead;
	}

	
	LinkedList::Iterator LinkedList::Insert(ConstIterator position, void* element)
	{
		assert(position.mNode != mHead);

		LinkedListNode* positionNode = position.mNode;
		LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));
		
		newNode->mElement = element;

		positionNode->mPrev->mNext = newNode;
		newNode->mPrev = positionNode->mPrev;

		positionNode->mPrev = newNode;
		newNode->mNext = positionNode;

		++mSize;

		return Iterator(newNode);
	}

	
	LinkedList::Iterator LinkedList::Insert(ConstIterator position, size_t count, void* element)
	{
		assert(position.mNode != mHead);

		if (count == 0)
		{
			return Iterator(position);
		}

		LinkedListNode* prevNode = position.mNode->mPrev;
		Iterator returnIterator(prevNode);

		for (size_t i = 0; i < count; ++i)
		{
			LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));
			
			newNode->mElement = element;

			prevNode->mNext = newNode;
			newNode->mPrev = prevNode;

			prevNode = newNode;
		}

		prevNode->mNext = position.mNode;
		position.mNode->mPrev = prevNode;

		mSize += count;

		return ++returnIterator;
	}

	
	LinkedList::Iterator LinkedList::Delete(ConstIterator position)
	{
		assert(position.mNode != mHead);
		assert(position.mNode != mTail);

		Iterator returnIterator(position.mNode->mPrev);

		position.mNode->mNext->mPrev = position.mNode->mPrev;
		position.mNode->mPrev->mNext = position.mNode->mNext;

		mPool->Deallocate(position.mNode, sizeof(LinkedListNode));
		--mSize;
		
		return returnIterator;
	}

	
	LinkedList::Iterator LinkedList::Delete(ConstIterator first, ConstIterator last)
	{
		assert(first.mNode != mHead);

		LinkedListNode* deleteNode = first.mNode;

		Iterator returnIterator(first.mNode->mPrev);

		first.mNode->mPrev->mNext = last.mNode;
		last.mNode->mPrev = first.mNode->mPrev;

		while (deleteNode != last.mNode)
		{
			LinkedListNode* tempNode = deleteNode;
			deleteNode = deleteNode->mNext;

			mPool->Deallocate(tempNode, sizeof(LinkedListNode));

			--mSize;
		}

		return returnIterator;
	}

	
	void LinkedList::InsertFront(void* item)
	{
		LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));
		
		newNode->mElement = item;

		mHead->mNext->mPrev = newNode;
		newNode->mNext = mHead->mNext;

		mHead->mNext = newNode;
		newNode->mPrev = mHead;

		++mSize;
	}

	
	void LinkedList::InsertBack(void* item)
	{
		LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));
		
		newNode->mElement = item;

		mTail->mPrev->mNext = newNode;
		newNode->mPrev = mTail->mPrev;

		mTail->mPrev = newNode;
		newNode->mNext = mTail;

		++mSize;
	}
	
	
	void LinkedList::DeleteFront()
	{
		assert(!IsEmpty());

		LinkedListNode* tempNode = mHead->mNext;

		mHead->mNext->mNext->mPrev = mHead;
		mHead->mNext = mHead->mNext->mNext;

		mPool->Deallocate(tempNode, sizeof(LinkedListNode));

		--mSize;
	}

	
	void LinkedList::DeleteBack()
	{
		assert(!IsEmpty());

		LinkedListNode* tempNode = mTail->mPrev;

		mTail->mPrev->mPrev->mNext = mTail;
		mTail->mPrev = mTail->mPrev->mPrev;

		mPool->Deallocate(tempNode, sizeof(LinkedListNode));

		--mSize;
	}

	
	constexpr void LinkedList::Swap(LinkedList& other)
	{
		LinkedListNode* tempHead = mHead;
		LinkedListNode* tempTail = mTail;
		size_t tempSize = mSize;

		mHead = other.mHead;
		mTail = other.mTail;
		mSize = other.mSize;

		other.mHead = tempHead;
		other.mTail = tempTail;
		other.mSize = tempSize;
	}
}