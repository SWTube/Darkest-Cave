/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#ifdef CAVE_BUILD_DEBUG

#include <list>
#include "Utils/Crt.h"

#endif

#include "CoreGlobals.h"
#include "Debug/Log.h"
#include "Memory/MemoryPool.h"


import cave.Core.Memory.Memory;

namespace cave
{

	struct LinkedListNode {
		void* mItem;
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

		constexpr const void* operator*() const;
		constexpr const void** operator->() const;

		constexpr bool operator==(const LinkedListConstIterator& other) const;
		constexpr bool operator!=(const LinkedListConstIterator& other) const;
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
		constexpr const void* operator*() const;

		constexpr void** operator->();
		constexpr const void** operator->() const;

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
		LinkedList(void* item);
		LinkedList(void* item, MemoryPool& pool);
		LinkedList(const LinkedList& other);
		LinkedList(const LinkedList& other, MemoryPool& pool);
		LinkedList(LinkedList&& other);

		constexpr LinkedList& operator=(const LinkedList& other);
		constexpr LinkedList& operator=(LinkedList&& other);

		constexpr bool operator==(const LinkedList& other);
		constexpr bool operator!=(const LinkedList& other);

		~LinkedList();

		constexpr void Clear();

		constexpr void Swap(LinkedList& other);

		Iterator Insert(ConstIterator position, void* item);

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

		constexpr ConstIterator begin() const;
		constexpr ConstIterator end() const;

		constexpr Iterator GetBeginIterator();
		constexpr Iterator GetEndIterator();

		constexpr ConstIterator GetBeginConstIterator() const;
		constexpr ConstIterator GetEndConstIterator() const;

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


	constexpr const void* LinkedListConstIterator::operator*() const
	{
		return const_cast<const void*>(mNode->mItem);
	}

	constexpr const void** LinkedListConstIterator::operator->() const
	{
		return const_cast<const void**>(&mNode->mItem);
	}


	constexpr bool LinkedListConstIterator::operator==(const LinkedListConstIterator& other) const
	{
		return mNode == other.mNode;
	}


	constexpr bool LinkedListConstIterator::operator!=(const LinkedListConstIterator& other) const
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

	constexpr const void* LinkedListIterator::operator*() const
	{
		return Base::operator*();
	}

	constexpr void** LinkedListIterator::operator->()
	{
		return const_cast<void**>(Base::operator->());
	}

	constexpr const void** LinkedListIterator::operator->() const
	{
		return Base::operator->();
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

	LinkedList::LinkedList(void* item)
		: LinkedList(item, gCoreMemoryPool)
	{ }

	LinkedList::LinkedList(void* item, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mTail(reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode))))
		, mSize(1)
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));

		newNode->mItem = item;

		newNode->mPrev = mHead;
		newNode->mNext = mTail;

		mTail->mPrev = newNode;
		mHead->mNext = newNode;

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

			newNode->mItem = otherNode->mItem;

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
		, mSize(0)
	{
		mHead->mNext = mTail;
		mHead->mPrev = nullptr;

		mTail->mPrev = mHead;
		mTail->mNext = nullptr;

		Swap(other);
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

				setElementNode->mItem = getElementNode->mItem;
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

					newNode->mItem = getElementNode->mItem;

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

		return mHead->mNext->mItem;
	}


	constexpr const void* LinkedList::GetFront() const
	{
		assert(!IsEmpty());

		return mHead->mNext->mItem;
	}


	constexpr void* LinkedList::GetBack()
	{
		assert(!IsEmpty());

		return mTail->mPrev->mItem;
	}


	constexpr const void* LinkedList::GetBack() const
	{
		assert(!IsEmpty());

		return mTail->mPrev->mItem;
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

	constexpr LinkedList::ConstIterator LinkedList::begin() const
	{
		return ConstIterator(mHead->mNext);
	}


	constexpr LinkedList::ConstIterator LinkedList::end() const
	{
		return ConstIterator(mTail);
	}


	constexpr LinkedList::Iterator LinkedList::GetBeginIterator()
	{
		return Iterator(mHead->mNext);
	}


	constexpr LinkedList::Iterator LinkedList::GetEndIterator()
	{
		return Iterator(mTail);
	}


	constexpr LinkedList::ConstIterator LinkedList::GetBeginConstIterator() const
	{
		return ConstIterator(mHead->mNext);
	}


	constexpr LinkedList::ConstIterator LinkedList::GetEndConstIterator() const
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

		newNode->mItem = element;

		positionNode->mPrev->mNext = newNode;
		newNode->mPrev = positionNode->mPrev;

		positionNode->mPrev = newNode;
		newNode->mNext = positionNode;

		++mSize;

		return Iterator(newNode);
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

		newNode->mItem = item;

		mHead->mNext->mPrev = newNode;
		newNode->mNext = mHead->mNext;

		mHead->mNext = newNode;
		newNode->mPrev = mHead;

		++mSize;
	}


	void LinkedList::InsertBack(void* item)
	{
		LinkedListNode* newNode = reinterpret_cast<LinkedListNode*>(mPool->Allocate(sizeof(LinkedListNode)));

		newNode->mItem = item;

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

		tempNode->mNext->mPrev = mHead;
		mHead->mNext = tempNode->mNext;

		mPool->Deallocate(tempNode, sizeof(LinkedListNode));

		--mSize;
	}


	void LinkedList::DeleteBack()
	{
		assert(!IsEmpty());

		LinkedListNode* tempNode = mTail->mPrev;

		tempNode->mPrev->mNext = mTail;
		mTail->mPrev = tempNode->mPrev;

		mPool->Deallocate(tempNode, sizeof(LinkedListNode));

		--mSize;
	}


	constexpr void LinkedList::Swap(LinkedList& other)
	{
		LinkedListNode* tempHead = mHead;
		LinkedListNode* tempTail = mTail;
		size_t tempSize = mSize;
		MemoryPool* tempPool = mPool;

		mHead = other.mHead;
		mTail = other.mTail;
		mSize = other.mSize;
		mPool = other.mPool;

		other.mHead = tempHead;
		other.mTail = tempTail;
		other.mSize = tempSize;
		other.mPool = tempPool;
	}

#ifdef CAVE_BUILD_DEBUG
	namespace LinkedListTest
	{
		constexpr size_t DEFAULT_CONTAINER_SIZE = 10;

		constexpr uint8_t TEST_ALL = 0b11111111;
		constexpr uint8_t TEST_CONSTRUCTOR = 0b00000001;
		constexpr uint8_t TEST_ASSIGN = 0b00000010;
		constexpr uint8_t TEST_ACCESS = 0b00000100;
		constexpr uint8_t TEST_INSERT = 0b00001000;
		constexpr uint8_t TEST_MOVE = 0b00001000;
		constexpr uint8_t TEST_DELETE = 0b00010000;
		constexpr uint8_t TEST_COMPARE = 0b00010000;
		constexpr uint8_t TEST_ITERATOR = 0b00100000;
		constexpr uint8_t TEST_OTHER = 0b01000000;

		std::list<int32_t> stdList;

		int32_t*** insertTable;
		size_t** insertTableCount;

		size_t** deleteTable;

		void Test(uint8_t constIteratorTestCase, size_t constIteratorTestCount, uint8_t iteratorTestCase, size_t iteratorTestCount, uint8_t containerTestCase, size_t containerTestCount);
		const int32_t Toint32_t(const void* item);
		void PrintLinkedList(const LinkedList& list);
		void CheckEqual(const LinkedList& list);
		void ConstIteratorTest(uint8_t constIteratorTestCase, LinkedList& caveLinkedList);
		void IteratorTest(uint8_t iteratorTestCase, LinkedList& caveLinkedList);
		void ContainerTest(uint8_t containerTestCase, LinkedList& caveLinkedList);

		namespace ConstIterator
		{
			void Constructor(LinkedList& caveLinkedList);
			void AssignOperator(LinkedList& caveLinkedList);
			void AccessOperator(LinkedList& caveLinkedList);
			void MoveOperator(LinkedList& caveLinkedList);
			void CompareOperator(LinkedList& caveLinkedList);

			void Constructor(LinkedList& caveLinkedList)
			{
				size_t offset = rand() % caveLinkedList.GetSize();

				LinkedListConstIterator defaultConstructor;
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedListConstIterator() Success");

				LinkedListConstIterator containerConstructor(caveLinkedList, offset);
				LOGDF(eLogChannel::CORE_CONTAINER, "LinkedListConstIterator(LinkedList, %d) Success", offset);

				LinkedListConstIterator copyConstructor(containerConstructor);
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedListConstIterator(LinkedListConstIterator) Success");
			}

			void AssignOperator(LinkedList& caveLinkedList)
			{
				size_t offset = rand() % caveLinkedList.GetSize();

				LinkedListConstIterator containerConstructor(caveLinkedList, offset);

				LinkedListConstIterator copyAssign = containerConstructor;
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedListConstIterator = LinkedListConstIterator Success");
			}

			void AccessOperator(LinkedList& caveLinkedList)
			{
				size_t offset = rand() % caveLinkedList.GetSize();

				LinkedListConstIterator iterator(caveLinkedList, offset);

				LOGDF(eLogChannel::CORE_CONTAINER, "offset %d: %d", offset, Toint32_t(*iterator));
			}

			void MoveOperator(LinkedList& caveLinkedList)
			{
				size_t offset = rand() % (caveLinkedList.GetSize() - 2);

				auto caveIterator = caveLinkedList.GetBeginConstIterator();
				auto stdIterator = stdList.cbegin();

				for (size_t i = 0; i < offset; ++i)
				{
					++caveIterator;
					++stdIterator;
				}

				assert(Toint32_t(*caveIterator) == *stdIterator);
				assert(Toint32_t(*++caveIterator) == *++stdIterator);

				assert(Toint32_t(*caveIterator) == *stdIterator);
				assert(Toint32_t(*caveIterator++) == *stdIterator++);

				assert(Toint32_t(*caveIterator) == *stdIterator);
				assert(Toint32_t(*--caveIterator) == *--stdIterator);

				assert(Toint32_t(*caveIterator) == *stdIterator);
				assert(Toint32_t(*caveIterator--) == *stdIterator--);

				assert(Toint32_t(*caveIterator) == *stdIterator);

			}

			void CompareOperator(LinkedList& caveLinkedList)
			{
				size_t leftOffset = rand() % caveLinkedList.GetSize();
				size_t rightOffset = rand() % caveLinkedList.GetSize();

				auto caveLeftIterator = caveLinkedList.GetBeginConstIterator();
				auto caveRightIterator = caveLinkedList.GetBeginConstIterator();

				auto stdLeftIterator = stdList.cbegin();
				auto stdRightIterator = stdList.cbegin();

				for (size_t i = 0; i < leftOffset; ++i)
				{
					++caveLeftIterator;
					++stdLeftIterator;
				}

				for (size_t i = 0; i < rightOffset; ++i)
				{
					++caveRightIterator;
					++stdRightIterator;
				}

				assert((caveLeftIterator == caveRightIterator) == (stdLeftIterator == stdRightIterator));
				assert((caveLeftIterator != caveRightIterator) == (stdLeftIterator != stdRightIterator));
			}
		}

		namespace Iterator
		{
			void Constructor(LinkedList& caveLinkedList);
			void AssignOperator(LinkedList& caveLinkedList);
			void AccessOperator(LinkedList& caveLinkedList);
			void MoveOperator(LinkedList& caveLinkedList);

			void Constructor(LinkedList& caveLinkedList)
			{
				size_t offset = rand() % caveLinkedList.GetSize();

				LinkedListIterator defaultConstructor;
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedListConstIterator() Success");

				LinkedListIterator containerConstructor(caveLinkedList, offset);
				LOGDF(eLogChannel::CORE_CONTAINER, "LinkedListConstIterator(LinkedList, %d) Success", offset);

				LinkedListIterator copyConstructor(containerConstructor);
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedListConstIterator(LinkedListConstIterator) Success");
			}

			void AssignOperator(LinkedList& caveLinkedList)
			{
				size_t offset = rand() % caveLinkedList.GetSize();

				LinkedListIterator containerConstructor(caveLinkedList, offset);

				LinkedListIterator copyAssign = containerConstructor;
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedListConstIterator = LinkedListConstIterator Success");
			}

			void AccessOperator(LinkedList& caveLinkedList)
			{
				size_t offset = rand() % caveLinkedList.GetSize();

				LinkedListIterator iterator(caveLinkedList, offset);

				LOGDF(eLogChannel::CORE_CONTAINER, "offset %d: %d", offset, Toint32_t(*iterator));
			}

			void MoveOperator(LinkedList& caveLinkedList)
			{
				size_t offset = rand() % (caveLinkedList.GetSize() - 2);

				auto caveIterator = caveLinkedList.GetBeginIterator();
				auto stdIterator = stdList.begin();

				for (size_t i = 0; i < offset; ++i)
				{
					++caveIterator;
					++stdIterator;
				}

				assert(Toint32_t(*caveIterator) == *stdIterator);
				assert(Toint32_t(*++caveIterator) == *++stdIterator);

				assert(Toint32_t(*caveIterator) == *stdIterator);
				assert(Toint32_t(*caveIterator++) == *stdIterator++);

				assert(Toint32_t(*caveIterator) == *stdIterator);
				assert(Toint32_t(*--caveIterator) == *--stdIterator);

				assert(Toint32_t(*caveIterator) == *stdIterator);
				assert(Toint32_t(*caveIterator--) == *stdIterator--);

				assert(Toint32_t(*caveIterator) == *stdIterator);
			}
		}

		namespace Container
		{
			void Constructor();
			void AssignOperator(const LinkedList& caveLinkedList);
			void AccessOperator(LinkedList& caveLinkedList);
			void Insert(LinkedList& caveLinkedList, size_t index);
			void Delete(LinkedList& caveLinkedList, size_t index);
			void Iterator(LinkedList& caveLinkedList);
			void Other(LinkedList& caveLinkedList);

			LinkedList CreateTempLinkedList(const LinkedList& list);

			void Constructor()
			{
				int32_t item = rand();

				LinkedList defaultConstructor;
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedList() Success");
				PrintLinkedList(defaultConstructor);

				LinkedList itemConstructor(&item);
				LOGDF(eLogChannel::CORE_CONTAINER, "LinkedList(item(%d)) Success", item);
				PrintLinkedList(itemConstructor);

				LinkedList copyConstructor(itemConstructor);
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedList(LinkedList) Success");
				PrintLinkedList(copyConstructor);

				LinkedList moveConstructor(CreateTempLinkedList(itemConstructor));
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedList(LinkedList) Success");
				PrintLinkedList(moveConstructor);

			}

			void AssignOperator(const LinkedList& caveLinkedList)
			{
				LinkedList copyAssign;
				copyAssign = caveLinkedList;
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedList = LinkedList Success");
				PrintLinkedList(copyAssign);

				LinkedList moveAssign;
				moveAssign = CreateTempLinkedList(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "LinkedList = LinkedList() Success");
				PrintLinkedList(moveAssign);
			}

			void AccessOperator(LinkedList& caveLinkedList)
			{
				if (!caveLinkedList.IsEmpty())
				{
					assert(Toint32_t(caveLinkedList.GetFront()) == stdList.front());
					assert(Toint32_t(caveLinkedList.GetBack()) == stdList.back());
					assert(caveLinkedList.GetSize() == stdList.size());
				}

				LOGDF(eLogChannel::CORE_CONTAINER, "GetMaxSize: %d", caveLinkedList.GetMaxSize());
			}

			void Insert(LinkedList& caveLinkedList, size_t index)
			{
				for (size_t i = 0; i < insertTableCount[index][0]; ++i)
				{
					size_t offset;
					auto caveIterator = caveLinkedList.GetBeginIterator();
					auto stdIterator = stdList.begin();

					if (caveLinkedList.IsEmpty())
					{
						offset = 0;
					}
					else
					{
						offset = rand() % caveLinkedList.GetSize();
					}

					for (size_t i = 0; i < offset; ++i)
					{
						++caveIterator;
						++stdIterator;
					}

					caveLinkedList.Insert(caveIterator, &insertTable[index][0][i]);
					stdList.insert(stdIterator, insertTable[index][0][i]);
				}

				for (size_t i = 0; i < insertTableCount[index][1]; ++i)
				{
					caveLinkedList.InsertBack(&insertTable[index][1][i]);
					stdList.push_back(insertTable[index][1][i]);
				}

				CheckEqual(caveLinkedList);
			}

			void Delete(LinkedList& caveLinkedList, size_t index)
			{
				for (size_t i = 0; i < deleteTable[index][0]; ++i)
				{
					size_t offset = rand() % caveLinkedList.GetSize();
					auto caveIterator = caveLinkedList.GetBeginIterator();
					auto stdIterator = stdList.begin();

					for (size_t i = 0; i < offset; ++i)
					{
						++caveIterator;
						++stdIterator;
					}

					caveLinkedList.Delete(caveIterator);
					stdList.erase(stdIterator);
				}

				for (size_t i = 0; i < deleteTable[index][1]; ++i)
				{
					caveLinkedList.DeleteBack();
					stdList.pop_back();
				}

				CheckEqual(caveLinkedList);
			}

			void Iterator(LinkedList& caveLinkedList)
			{
				if (!caveLinkedList.IsEmpty())
				{
					assert(Toint32_t(*caveLinkedList.GetBeginConstIterator()) == *stdList.cbegin());
					assert(Toint32_t(*caveLinkedList.GetBeginIterator()) == *stdList.begin());
					assert(Toint32_t(*--caveLinkedList.GetEndConstIterator()) == *--stdList.cend());
					assert(Toint32_t(*--caveLinkedList.GetEndIterator()) == *--stdList.end());
				}
			}

			void Other(LinkedList& caveLinkedList)
			{
				int32_t item = rand();

				LinkedList tempList(&item);

				caveLinkedList.Swap(tempList);
				LOGD(eLogChannel::CORE_CONTAINER, "Swap() Success");

				LOGD(eLogChannel::CORE_CONTAINER, "caveLinkedList");
				PrintLinkedList(caveLinkedList);

				LOGD(eLogChannel::CORE_CONTAINER, "tempList");
				PrintLinkedList(tempList);

				caveLinkedList.Swap(tempList);

				assert(caveLinkedList.IsEmpty() == stdList.empty());

				caveLinkedList.Clear();
				stdList.clear();

				LOGD(eLogChannel::CORE_CONTAINER, "Clear() Success");
				PrintLinkedList(caveLinkedList);

				assert(caveLinkedList.IsEmpty() == stdList.empty());
			}

			LinkedList CreateTempLinkedList(const LinkedList& list)
			{
				LinkedList tempLinkedList = list;

				return tempLinkedList;
			}
		}

		const int32_t Toint32_t(const void* item)
		{
			return *reinterpret_cast<const int32_t*>(item);
		}

		void PrintLinkedList(const LinkedList& list)
		{
			size_t i = 0;

			LOGDF(eLogChannel::CORE_CONTAINER, "size: %d", list.GetSize());

			for (const auto& item : list)
			{
				LOGDF(eLogChannel::CORE_CONTAINER, "%d: %d", i, Toint32_t(item));
				++i;
			}
		}

		void CheckEqual(const LinkedList& list)
		{
			auto caveIterator = list.GetBeginConstIterator();
			auto stdIterator = stdList.cbegin();

			assert(list.GetSize() == stdList.size());

			for (int i = 0; i < list.GetSize(); ++i)
			{
				assert(Toint32_t(*caveIterator) == *stdIterator);
			}
		}

		void Test(uint8_t constIteratorTestCase, size_t constIteratorTestCount, uint8_t iteratorTestCase, size_t iteratorTestCount, uint8_t containerTestCase, size_t containerTestCount)
		{
			srand(time(NULL));

			LinkedList caveLinkedList;

			int32_t inputArray[DEFAULT_CONTAINER_SIZE];

			for (size_t i = 0; i < DEFAULT_CONTAINER_SIZE; ++i)
			{
				inputArray[i] = rand();
				caveLinkedList.InsertBack(&inputArray[i]);
				stdList.push_back(inputArray[i]);
			}

			LOGD(eLogChannel::CORE_CONTAINER, "====LinkedList Test====");

			LOGD(eLogChannel::CORE_CONTAINER, "caveLinkedList");
			PrintLinkedList(caveLinkedList);

			for (size_t i = 0; i < constIteratorTestCount; ++i)
			{
				ConstIteratorTest(constIteratorTestCase, caveLinkedList);
			}

			for (size_t i = 0; i < iteratorTestCount; ++i)
			{
				IteratorTest(iteratorTestCase, caveLinkedList);
			}

			insertTable = reinterpret_cast<int32_t***>(gCoreMemoryPool.Allocate(sizeof(int32_t**) * containerTestCount));
			insertTableCount = reinterpret_cast<size_t**>(gCoreMemoryPool.Allocate(sizeof(size_t*) * containerTestCount));

			deleteTable = reinterpret_cast<size_t**>(gCoreMemoryPool.Allocate(sizeof(size_t*) * containerTestCount));


			for (size_t i = 0; i < containerTestCount; ++i)
			{
				insertTableCount[i] = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * 2));
				insertTableCount[i][0] = rand() % 16 + 1;
				insertTableCount[i][1] = rand() % 16 + 1;
				insertTable[i] = reinterpret_cast<int32_t**>(gCoreMemoryPool.Allocate(sizeof(int32_t*) * 2));
				insertTable[i][0] = reinterpret_cast<int32_t*>(gCoreMemoryPool.Allocate(sizeof(int32_t) * insertTableCount[i][0]));
				insertTable[i][1] = reinterpret_cast<int32_t*>(gCoreMemoryPool.Allocate(sizeof(int32_t) * insertTableCount[i][1]));

				deleteTable[i] = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * 2));
				deleteTable[i][0] = rand() % (caveLinkedList.GetSize() / 2 + 1);
				deleteTable[i][1] = rand() % (caveLinkedList.GetSize() / 2 + 1);


				for (size_t j = 0; j < insertTableCount[i][0]; ++j)
				{
					insertTable[i][0][j] = rand();
				}

				for (size_t j = 0; j < insertTableCount[i][1]; ++j)
				{
					insertTable[i][1][j] = rand();
				}

				ContainerTest(containerTestCase, caveLinkedList);
			}

			for (size_t i = 0; i < containerTestCount; ++i)
			{
				gCoreMemoryPool.Deallocate(insertTable[i][0], sizeof(int32_t) * insertTableCount[i][0]);
				gCoreMemoryPool.Deallocate(insertTable[i][1], sizeof(int32_t) * insertTableCount[i][1]);
				gCoreMemoryPool.Deallocate(insertTable[i], sizeof(int32_t*) * 2);
				gCoreMemoryPool.Deallocate(insertTableCount[i], sizeof(size_t) * 2);

				gCoreMemoryPool.Deallocate(deleteTable[i], sizeof(size_t) * 2);
			}

			gCoreMemoryPool.Deallocate(insertTable, sizeof(int32_t**) * containerTestCount);
			gCoreMemoryPool.Deallocate(insertTableCount, sizeof(size_t*) * containerTestCount);

			gCoreMemoryPool.Deallocate(deleteTable, sizeof(size_t*) * containerTestCount);
		}

		void ConstIteratorTest(uint8_t constIteratorTestCase, LinkedList& caveLinkedList)
		{
			static size_t testCount = 0;
			LOGDF(eLogChannel::CORE_CONTAINER, "====ConstIterator Test#%d====", ++testCount);

			if (constIteratorTestCase & TEST_CONSTRUCTOR)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Start");
				ConstIterator::Constructor(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Success");
			}

			if (constIteratorTestCase & TEST_ASSIGN)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Start");
				ConstIterator::AssignOperator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Success");
			}

			if (constIteratorTestCase & TEST_ACCESS)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Start");
				ConstIterator::AccessOperator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Success");
			}

			if (constIteratorTestCase & TEST_MOVE)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_MOVE Start");
				ConstIterator::MoveOperator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_MOVE Success");
			}

			if (constIteratorTestCase & TEST_COMPARE)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_COMPARE Start");
				ConstIterator::CompareOperator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_COMPARE Success");
			}
		}

		void IteratorTest(uint8_t iteratorTestCase, LinkedList& caveLinkedList)
		{
			static size_t testCount = 0;
			LOGDF(eLogChannel::CORE_CONTAINER, "====Iterator Test#%d====", ++testCount);

			if (iteratorTestCase & TEST_CONSTRUCTOR)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Start");
				Iterator::Constructor(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Success");
			}

			if (iteratorTestCase & TEST_ASSIGN)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Start");
				Iterator::AssignOperator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Success");
			}

			if (iteratorTestCase & TEST_ACCESS)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Start");
				Iterator::AccessOperator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Success");
			}

			if (iteratorTestCase & TEST_MOVE)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_MOVE Start");
				Iterator::MoveOperator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_MOVE Success");
			}
		}

		void ContainerTest(uint8_t containerTestCase, LinkedList& caveLinkedList)
		{
			static size_t testCount = 0;
			LOGDF(eLogChannel::CORE_CONTAINER, "====Container Test#%d====", ++testCount);
			if (containerTestCase & TEST_CONSTRUCTOR)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Start");
				Container::Constructor();
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Success");
			}

			if (containerTestCase & TEST_ASSIGN)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Start");
				Container::AssignOperator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Success");
			}

			if (containerTestCase & TEST_ACCESS)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Start");
				Container::AccessOperator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Success");
			}

			if (containerTestCase & TEST_INSERT)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_INSERT Start");
				Container::Insert(caveLinkedList, testCount - 1);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_INSERT Success");
			}

			if (containerTestCase & TEST_DELETE)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_DELETE Start");
				Container::Delete(caveLinkedList, testCount - 1);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_DELETE Success");
			}

			if (containerTestCase & TEST_ITERATOR)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ITERATOR Start");
				Container::Iterator(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_ITERATOR Success");
			}

			if (containerTestCase & TEST_OTHER)
			{
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_OTHER Start");
				Container::Other(caveLinkedList);
				LOGD(eLogChannel::CORE_CONTAINER, "TEST_OTHER Success");
			}
		}


	}
#endif
}