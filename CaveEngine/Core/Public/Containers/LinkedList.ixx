/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module LinkedList;

import IteratorType;
import Memory;

export namespace cave
{
	template<class ElementType>
	struct LinkedListNode {
		ElementType mElement;
		LinkedListNode* mNext;
		LinkedListNode* mPrev;
	};

	template<class ElementType>
	class LinkedList;

	template<class ElementType>
	class LinkedListConstIterator
	{
	public:
		friend LinkedList<ElementType>;

		constexpr LinkedListConstIterator();
		constexpr LinkedListConstIterator(LinkedList<ElementType>& container, size_t startIndex = 0);
		constexpr LinkedListConstIterator(const LinkedListConstIterator& other);

		constexpr LinkedListConstIterator& operator=(const LinkedListConstIterator& other);

		constexpr LinkedListConstIterator& operator++();
		constexpr LinkedListConstIterator operator++(int);

		constexpr LinkedListConstIterator& operator--();
		constexpr LinkedListConstIterator operator--(int);

		constexpr const ElementType& operator*();

		constexpr bool operator==(const LinkedListConstIterator& other);
		constexpr bool operator!=(const LinkedListConstIterator& other);
	protected:
		constexpr LinkedListConstIterator(LinkedListNode<ElementType>* node);

	private:
		LinkedListNode<ElementType>* mNode;
	};

	template<class ElementType>
	class LinkedListIterator : public LinkedListConstIterator<ElementType>
	{
	public:
		friend LinkedList<ElementType>;

		using Base = LinkedListConstIterator<ElementType>;

		constexpr LinkedListIterator();
		constexpr LinkedListIterator(LinkedList<ElementType>& container, size_t startIndex = 0);
		constexpr LinkedListIterator(const LinkedListConstIterator<ElementType>& other);

		constexpr LinkedListIterator& operator=(const LinkedListConstIterator<ElementType>& other);

		constexpr LinkedListIterator& operator++();
		constexpr LinkedListIterator operator++(int);

		constexpr LinkedListIterator& operator--();
		constexpr LinkedListIterator operator--(int);

		constexpr ElementType& operator*();

	protected:
		constexpr LinkedListIterator(LinkedListNode<ElementType>* node);
	};

	template<class ElementType>
	class LinkedList final
	{
	public:
		using ConstIterator = LinkedListConstIterator<ElementType>;
		using Iterator = LinkedListIterator<ElementType>;

		constexpr LinkedList(MemoryPool& pool = gCoreMemoryPool);
		constexpr LinkedList(size_t count, const ElementType& element, MemoryPool& pool = gCoreMemoryPool);
		template<class IteratorType>
		requires IteratorInputAble<IteratorType, ElementType>
		constexpr LinkedList(IteratorType first, IteratorType last, MemoryPool& pool = gCoreMemoryPool);
		constexpr LinkedList(const LinkedList& other);
		constexpr LinkedList(const LinkedList& other, MemoryPool& pool);
		constexpr LinkedList(LinkedList&& other);
		constexpr LinkedList(std::initializer_list<ElementType> init, MemoryPool& pool = gCoreMemoryPool);

		constexpr LinkedList& operator=(const LinkedList& other);
		constexpr LinkedList& operator=(LinkedList&& other);

		constexpr bool operator==(const LinkedList& other);
		constexpr bool operator!=(const LinkedList& other);

		~LinkedList();

		constexpr bool IsEmpty() const;

		constexpr ElementType& GetFront();
		constexpr const ElementType& GetFront() const;

		constexpr ElementType& GetBack();
		constexpr const ElementType& GetBack() const;

		constexpr size_t GetSize() const;
		constexpr size_t GetMaxSize() const;

		constexpr Iterator begin();
		constexpr Iterator end();

		constexpr Iterator GetBeginIterator();
		constexpr Iterator GetEndIterator();

		constexpr ConstIterator GetBeginConstIterator();
		constexpr ConstIterator GetEndConstIterator();
		
		constexpr void Clear();

		constexpr Iterator Insert(ConstIterator position, const ElementType& element);
		constexpr Iterator Insert(ConstIterator position, size_t count, const ElementType& element);
		template<class IteratorType>
		requires IteratorInputAble<IteratorType, ElementType>
		constexpr Iterator Insert(ConstIterator position, IteratorType first, IteratorType last);

		constexpr Iterator Delete(ConstIterator position);
		constexpr Iterator Delete(ConstIterator first, ConstIterator last);

		constexpr void InsertFront(const ElementType& element);
		constexpr void InsertBack(const ElementType& element);

		constexpr void DeleteFront();
		constexpr void DeleteBack();

		constexpr void Swap(LinkedList& other);

	private:
		MemoryPool& mPool;
		LinkedListNode<ElementType>* mHead;
		LinkedListNode<ElementType>* mTail;
		size_t mSize;
	};

	/*
	*
	* TSinglyListConstIterator
	* 
	*/

	template<class ElementType>
	constexpr LinkedListConstIterator<ElementType>::LinkedListConstIterator()
		: mNode(nullptr)
	{ }

	template<class ElementType>
	constexpr LinkedListConstIterator<ElementType>::LinkedListConstIterator(LinkedList<ElementType>& container, size_t startIndex)
	{
		mNode = container.GetBeginIterator().mNode;

		for (size_t i = 0; i < startIndex; ++i)
		{
			mNode = mNode->mNext;
		}
	}

	template<class ElementType>
	constexpr LinkedListConstIterator<ElementType>::LinkedListConstIterator(LinkedListNode<ElementType>* node)
		: mNode(node)
	{ }

	template<class ElementType>
	constexpr LinkedListConstIterator<ElementType>::LinkedListConstIterator(const LinkedListConstIterator& other)
		: mNode(other.mNode)
	{ }

	template<class ElementType>
	constexpr LinkedListConstIterator<ElementType>& LinkedListConstIterator<ElementType>::operator=(const LinkedListConstIterator& other)
	{
		mNode = other.mNode;

		return *this;
	}

	template<class ElementType>
	constexpr LinkedListConstIterator<ElementType>& LinkedListConstIterator<ElementType>::operator++()
	{
		mNode = mNode->mNext;

		return *this;
	}

	template<class ElementType>
	constexpr LinkedListConstIterator<ElementType> LinkedListConstIterator<ElementType>::operator++(int)
	{
		LinkedListConstIterator returnIterator = *this;
		mNode = mNode->mNext;

		return returnIterator;
	}

	template<class ElementType>
	constexpr LinkedListConstIterator<ElementType>& LinkedListConstIterator<ElementType>::operator--()
	{
		mNode = mNode->mPrev;

		return *this;
	}

	template<class ElementType>
	constexpr LinkedListConstIterator<ElementType> LinkedListConstIterator<ElementType>::operator--(int)
	{
		LinkedListConstIterator returnIterator = *this;
		mNode = mNode->mPrev;

		return returnIterator;
	}

	template<class ElementType>
	constexpr const ElementType& LinkedListConstIterator<ElementType>::operator*()
	{
		return mNode->mElement;
	}

	template<class ElementType>
	constexpr bool LinkedListConstIterator<ElementType>::operator==(const LinkedListConstIterator& other)
	{
		return mNode == other.mNode;
	}

	template<class ElementType>
	constexpr bool LinkedListConstIterator<ElementType>::operator!=(const LinkedListConstIterator& other)
	{
		return mNode != other.mNode;
	}

	/*
	*
	* TSinglyListIterator
	*
	*/

	template<class ElementType>
	constexpr LinkedListIterator<ElementType>::LinkedListIterator()
		: Base()
	{ }

	template<class ElementType>
	constexpr LinkedListIterator<ElementType>::LinkedListIterator(LinkedList<ElementType>& container, size_t startIndex)
		: Base(container, startIndex)
	{ }

	template<class ElementType>
	constexpr LinkedListIterator<ElementType>::LinkedListIterator(LinkedListNode<ElementType>* node)
		: Base(node)
	{ }

	template<class ElementType>
	constexpr LinkedListIterator<ElementType>::LinkedListIterator(const LinkedListConstIterator<ElementType>& other)
		: Base(other)
	{ }

	template<class ElementType>
	constexpr LinkedListIterator<ElementType>& LinkedListIterator<ElementType>::operator=(const LinkedListConstIterator<ElementType>& other)
	{
		Base::operator=(other);

		return *this;
	}

	template<class ElementType>
	constexpr LinkedListIterator<ElementType>& LinkedListIterator<ElementType>::operator++()
	{
		Base::operator++();

		return *this;
	}

	template<class ElementType>
	constexpr LinkedListIterator<ElementType> LinkedListIterator<ElementType>::operator++(int)
	{
		LinkedListConstIterator returnIterator = *this;
		Base::operator++();

		return returnIterator;
	}

	template<class ElementType>
	constexpr LinkedListIterator<ElementType>& LinkedListIterator<ElementType>::operator--()
	{
		Base::operator--();

		return *this;
	}

	template<class ElementType>
	constexpr LinkedListIterator<ElementType> LinkedListIterator<ElementType>::operator--(int)
	{
		LinkedListConstIterator returnIterator = *this;
		Base::operator--();

		return returnIterator;
	}

	template<class ElementType>
	constexpr ElementType& LinkedListIterator<ElementType>::operator*()
	{
		return const_cast<ElementType&>(Base::operator*());
	}

	/*
	*
	* TSinglyList
	*
	*/

	template<class ElementType>
	constexpr LinkedList<ElementType>::LinkedList(MemoryPool& pool)
		: mPool(pool)
		, mHead(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mSize(0)
	{
		mHead->mNext = mTail;
		mHead->mPrev = nullptr;

		mTail->mPrev = mHead;
		mTail->mNext = nullptr;
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::LinkedList(size_t count, const ElementType& element, MemoryPool& pool)
		: mPool(pool)
		, mHead(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mSize(count)
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		LinkedListNode<ElementType>* prevNode = mHead;

		for (size_t i = 0; i < count; ++i)
		{
			LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));

			newNode->mElement = element;

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	template<class IteratorType>
	requires IteratorInputAble<IteratorType, ElementType>
	constexpr LinkedList<ElementType>::LinkedList(IteratorType first, IteratorType last, MemoryPool& pool)
		: mPool(pool)
		, mHead(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mSize(0)
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		LinkedListNode<ElementType>* prevNode = mHead;

		for (auto iterator = first; iterator != last; ++iterator)
		{
			LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));

			newNode->mElement = *iterator;

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;

			++mSize;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::LinkedList(const LinkedList& other)
		: mPool(other.mPool)
		, mHead(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mSize(other.mSize)
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		LinkedListNode<ElementType>* otherNode = other.mHead;
		LinkedListNode<ElementType>* prevNode = mHead;

		while (otherNode->mNext != other.mTail)
		{
			otherNode = otherNode->mNext;

			LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));

			newNode->mElement = otherNode->mElement;

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::LinkedList(const LinkedList& other, MemoryPool& pool)
		: mPool(pool)
		, mHead(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mSize(other.mSize)
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		LinkedListNode<ElementType>* otherNode = other.mHead;
		LinkedListNode<ElementType>* prevNode = mHead;

		while (otherNode->mNext != other.mTail)
		{
			otherNode = otherNode->mNext;

			LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));
			
			newNode->mElement = otherNode->mElement;

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::LinkedList(LinkedList&& other)
		: mPool(other.mPool)
		, mHead(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mSize(other.mSize)
	{
		mHead->mNext = other.mHead->mNext;
		mHead->mPrev = nullptr;

		mTail->mPrev = other.mTail->mPrev;
		mTail->mNext = nullptr;

		other.mHead->mNext = other.mTail;
		other.mTail->mPrev = other.mHead;
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::LinkedList(std::initializer_list<ElementType> init, MemoryPool& pool)
		: mPool(pool)
		, mHead(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>))))
		, mSize(0)
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		LinkedListNode<ElementType>* prevNode = mHead;

		for (auto iterator = init.begin(); iterator != init.end(); ++iterator)
		{
			LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));
			
			newNode->mElement = *iterator;

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;

			++mSize;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>& LinkedList<ElementType>::operator=(const LinkedList& other)
	{
		if (*this != other)
		{
			LinkedListNode<ElementType>* setElementNode = mHead;
			LinkedListNode<ElementType>* getElementNode = other.mHead;

			while (setElementNode->mNext != mTail && getElementNode->mNext != other.mTail)
			{
				setElementNode = setElementNode->mNext;
				getElementNode = getElementNode->mNext;

				setElementNode->mElement = getElementNode->mElement;
			}

			if (setElementNode->mNext != mTail)
			{
				LinkedListNode<ElementType>* tempNode = setElementNode;

				setElementNode = setElementNode->mNext;

				while (setElementNode != mTail)
				{
					mPool.Deallocate(setElementNode, sizeof(LinkedListNode<ElementType>));
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

					LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));

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

	template<class ElementType>
	constexpr LinkedList<ElementType>& LinkedList<ElementType>::operator=(LinkedList&& other)
	{
		if (*this != other)
		{
			Swap(other);
		}

		return *this;
	}

	template<class ElementType>
	constexpr bool LinkedList<ElementType>::operator==(const LinkedList& other)
	{
		return (mHead == other.mHead);
	}

	template<class ElementType>
	constexpr bool LinkedList<ElementType>::operator!=(const LinkedList& other)
	{
		return (mHead != other.mHead);
	}

	template<class ElementType>
	LinkedList<ElementType>::~LinkedList()
	{
		LinkedListNode<ElementType>* tempNode;

		while (mHead != mTail)
		{
			tempNode = mHead;
			mHead = mHead->mNext;
			mPool.Deallocate(tempNode, sizeof(LinkedListNode<ElementType>));
		}

		mPool.Deallocate(mTail, sizeof(LinkedListNode<ElementType>));
	}

	template<class ElementType>
	constexpr bool LinkedList<ElementType>::IsEmpty() const
	{
		return (mHead->mNext == mTail);
	}

	template<class ElementType>
	constexpr ElementType& LinkedList<ElementType>::GetFront()
	{
		assert(!IsEmpty());

		return mHead->mNext->mElement;
	}

	template<class ElementType>
	constexpr const ElementType& LinkedList<ElementType>::GetFront() const
	{
		assert(!IsEmpty());

		return mHead->mNext->mElement;
	}

	template<class ElementType>
	constexpr ElementType& LinkedList<ElementType>::GetBack()
	{
		assert(!IsEmpty());

		return mTail->mPrev->mElement;
	}

	template<class ElementType>
	constexpr const ElementType& LinkedList<ElementType>::GetBack() const
	{
		assert(!IsEmpty());

		return mTail->mPrev->mElement;
	}

	template<class ElementType>
	constexpr size_t LinkedList<ElementType>::GetSize() const
	{
		return mSize;
	}

	template<class ElementType>
	constexpr size_t LinkedList<ElementType>::GetMaxSize() const
	{
		return mPool.GetFreeMemorySize() / sizeof(ElementType);
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::Iterator LinkedList<ElementType>::begin()
	{
		return Iterator(mHead->mNext);
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::Iterator LinkedList<ElementType>::end()
	{
		return Iterator(mTail);
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::Iterator LinkedList<ElementType>::GetBeginIterator()
	{
		return Iterator(mHead->mNext);
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::Iterator LinkedList<ElementType>::GetEndIterator()
	{
		return Iterator(mTail);
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::ConstIterator LinkedList<ElementType>::GetBeginConstIterator()
	{
		return ConstIterator(mHead->mNext);
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::ConstIterator LinkedList<ElementType>::GetEndConstIterator()
	{
		return ConstIterator(mTail);
	}

	template<class ElementType>
	constexpr void LinkedList<ElementType>::Clear()
	{
		while (mHead->mNext != mTail)
		{
			LinkedListNode<ElementType>* tempNode = mHead->mNext;
			mHead->mNext = mHead->mNext->mNext;

			mPool.Deallocate(tempNode, sizeof(LinkedListNode<ElementType>));
		}

		mSize = 0;

		mTail->mPrev = mHead;
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::Iterator LinkedList<ElementType>::Insert(ConstIterator position, const ElementType& element)
	{
		assert(position.mNode != mHead);

		LinkedListNode<ElementType>* positionNode = position.mNode;
		LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));
		
		newNode->mElement = element;

		positionNode->mPrev->mNext = newNode;
		newNode->mPrev = positionNode->mPrev;

		positionNode->mPrev = newNode;
		newNode->mNext = positionNode;

		++mSize;

		return Iterator(newNode);
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::Iterator LinkedList<ElementType>::Insert(ConstIterator position, size_t count, const ElementType& element)
	{
		assert(position.mNode != mHead);

		if (count == 0)
		{
			return Iterator(position);
		}

		LinkedListNode<ElementType>* prevNode = position.mNode->mPrev;
		Iterator returnIterator(prevNode);

		for (size_t i = 0; i < count; ++i)
		{
			LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));
			
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

	template<class ElementType>
	template<class IteratorType>
	requires IteratorInputAble<IteratorType, ElementType>
	constexpr LinkedList<ElementType>::Iterator LinkedList<ElementType>::Insert(ConstIterator position, IteratorType first, IteratorType last)
	{
		assert(position.mNode != mHead);

		if (first == last)
		{
			return Iterator(position);
		}

		LinkedListNode<ElementType>* prevNode = position.mNode->mPrev;
		Iterator returnIterator(prevNode);

		for (auto iterator = first; iterator != last; ++iterator)
		{
			LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));
			
			newNode->mElement = *iterator;

			prevNode->mNext = newNode;
			newNode->mPrev = prevNode;

			prevNode = newNode;

			++mSize;
		}

		prevNode->mNext = position.mNode;
		position.mNode->mPrev = prevNode;

		return ++returnIterator;
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::Iterator LinkedList<ElementType>::Delete(ConstIterator position)
	{
		assert(position.mNode != mHead);
		assert(position.mNode != mTail);

		Iterator returnIterator(position.mNode->mPrev);

		position.mNode->mNext->mPrev = position.mNode->mPrev;
		position.mNode->mPrev->mNext = position.mNode->mNext;

		mPool.Deallocate(position.mNode, sizeof(LinkedListNode<ElementType>));
		--mSize;
		
		return returnIterator;
	}

	template<class ElementType>
	constexpr LinkedList<ElementType>::Iterator LinkedList<ElementType>::Delete(ConstIterator first, ConstIterator last)
	{
		assert(first.mNode != mHead);

		LinkedListNode<ElementType>* deleteNode = first.mNode;

		Iterator returnIterator(first.mNode->mPrev);

		first.mNode->mPrev->mNext = last.mNode;
		last.mNode->mPrev = first.mNode->mPrev;

		while (deleteNode != last.mNode)
		{
			LinkedListNode<ElementType>* tempNode = deleteNode;
			deleteNode = deleteNode->mNext;

			mPool.Deallocate(tempNode, sizeof(LinkedListNode<ElementType>));

			--mSize;
		}

		return returnIterator;
	}

	template<class ElementType>
	constexpr void LinkedList<ElementType>::InsertFront(const ElementType& element)
	{
		LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));
		
		newNode->mElement = element;

		mHead->mNext->mPrev = newNode;
		newNode->mNext = mHead->mNext;

		mHead->mNext = newNode;
		newNode->mPrev = mHead;

		++mSize;
	}

	template<class ElementType>
	constexpr void LinkedList<ElementType>::InsertBack(const ElementType& element)
	{
		LinkedListNode<ElementType>* newNode = reinterpret_cast<LinkedListNode<ElementType>*>(mPool.Allocate(sizeof(LinkedListNode<ElementType>)));
		
		newNode->mElement = element;

		mTail->mPrev->mNext = newNode;
		newNode->mPrev = mTail->mPrev;

		mTail->mPrev = newNode;
		newNode->mNext = mTail;

		++mSize;
	}
	
	template<class ElementType>
	constexpr void LinkedList<ElementType>::DeleteFront()
	{
		assert(!IsEmpty());

		LinkedListNode<ElementType>* tempNode = mHead->mNext;

		mHead->mNext->mNext->mPrev = mHead;
		mHead->mNext = mHead->mNext->mNext;

		mPool.Deallocate(tempNode, sizeof(LinkedListNode<ElementType>));

		--mSize;
	}

	template<class ElementType>
	constexpr void LinkedList<ElementType>::DeleteBack()
	{
		assert(!IsEmpty());

		LinkedListNode<ElementType>* tempNode = mTail->mPrev;

		mTail->mPrev->mPrev->mNext = mTail;
		mTail->mPrev = mTail->mPrev->mPrev;

		mPool.Deallocate(tempNode, sizeof(LinkedListNode<ElementType>));

		--mSize;
	}

	template<class ElementType>
	constexpr void LinkedList<ElementType>::Swap(LinkedList& other)
	{
		LinkedListNode<ElementType>* tempHead = mHead;
		LinkedListNode<ElementType>* tempTail = mTail;
		size_t tempSize = mSize;

		mHead = other.mHead;
		mTail = other.mTail;
		mSize = other.mSize;

		other.mHead = tempHead;
		other.mTail = tempTail;
		other.mSize = tempSize;
	}
}