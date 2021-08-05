/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Memory/Memory.h"
#include "Memory/MemoryPool.h"
#include "CoreGlobals.h"

export module TLinkedList;

import IteratorType;

export namespace cave
{
	template<class ElementType>
	struct TLinkedListNode {
		ElementType mElement;
		TLinkedListNode* mNext;
		TLinkedListNode* mPrev;

		TLinkedListNode(const ElementType& element)
			: mElement(element)
			, mNext(nullptr)
			, mPrev(nullptr)
		{ }
	};

	template<class ElementType>
	class TLinkedList;

	template<class ElementType>
	class TLinkedListConstIterator
	{
		friend TLinkedList<ElementType>;

		TLinkedListConstIterator();
		TLinkedListConstIterator(TLinkedList<ElementType>& container, size_t startIndex = 0);
		TLinkedListConstIterator(const TLinkedListConstIterator& other);

		TLinkedListConstIterator& operator=(const TLinkedListConstIterator& other);

		TLinkedListConstIterator& operator++();
		TLinkedListConstIterator operator++(int);

		const ElementType& operator*();

	protected:
		TLinkedListConstIterator(TLinkedListNode<ElementType>& node);

	private:
		TLinkedListNode<ElementType>* mNode;
	};

	template<class ElementType>
	class TLinkedListIterator : public TLinkedListConstIterator<ElementType>
	{
		using Base = TLinkedListConstIterator<ElementType>;

		TLinkedListIterator();
		TLinkedListIterator(TLinkedList<ElementType>& container, size_t startIndex = 0);
		TLinkedListIterator(const TLinkedListConstIterator<ElementType>& other);

		TLinkedListIterator& operator=(const TLinkedListConstIterator<ElementType>& other);

		TLinkedListIterator& operator++();
		TLinkedListIterator operator++(int);

		ElementType& operator*();

	protected:
		TLinkedListIterator(TLinkedListNode<ElementType>& node);
	};

	template<class ElementType>
	class TLinkedList
	{
	public:
		using ConstIterator = TLinkedListConstIterator<ElementType>;
		using Iterator = TLinkedListIterator<ElementType>;

		TLinkedList(MemoryPool& pool = gCoreMemoryPool);
		TLinkedList(size_t count, const ElementType& element, MemoryPool& pool = gCoreMemoryPool);
		template<class IteratorType>
		TLinkedList(IteratorType first, IteratorType last, MemoryPool& pool = gCoreMemoryPool);
		TLinkedList(const TLinkedList& other);
		TLinkedList(const TLinkedList& other, MemoryPool& pool);
		TLinkedList(TLinkedList&& other);
		TLinkedList(std::initializer_list<ElementType> init, MemoryPool& pool = gCoreMemoryPool);

		TLinkedList& operator=(const TLinkedList& other);
		TLinkedList& operator=(TLinkedList&& other);

		virtual ~TLinkedList();

		bool IsEmpty() const;

		ElementType& GetFront();
		const ElementType& GetFront() const;

		ElementType& GetBack();
		const ElementType& GetBack() const;

		size_t GetMaxSize() const;

		Iterator begin();
		Iterator end();

		Iterator GetBeginIterator();
		Iterator GetEndIterator();

		ConstIterator GetBeginConstIterator();
		ConstIterator GetEndConstIterator();
		
		void Clear();

		Iterator Insert(ConstIterator position, const ElementType& element);
		Iterator Insert(ConstIterator position, size_t count, const ElementType& element);
		template<class IteratorType>
		Iterator Insert(ConstIterator position, IteratorType first, IteratorType last);

		Iterator Delete(ConstIterator position);
		Iterator Delete(ConstIterator first, ConstIterator last);

		void InsertFront(const ElementType& element);
		void InsertBack(const ElementType& element);

		void DeleteFront();
		void DeleteBack();

		void Swap(const TLinkedList& other);

	private:
		MemoryPool* mPool;
		TLinkedListNode<ElementType>* mHead;
		TLinkedListNode<ElementType>* mTail;
	};

	/*
	*
	* TSinglyListConstIterator
	* 
	*/

	template<class ElementType>
	TLinkedListConstIterator<ElementType>::TLinkedListConstIterator()
		: mNode(nullptr)
	{ }

	template<class ElementType>
	TLinkedListConstIterator<ElementType>::TLinkedListConstIterator(TLinkedList<ElementType>& container, size_t startIndex)
	{
		mNode = container.GetBeginIterator().mNode;

		for (size_t i = 0; i < startIndex; ++i)
		{
			mNode = mNode->mNext;
		}
	}

	template<class ElementType>
	TLinkedListConstIterator<ElementType>::TLinkedListConstIterator(TLinkedListNode<ElementType>& node)
		: mNode(node)
	{ }

	template<class ElementType>
	TLinkedListConstIterator<ElementType>::TLinkedListConstIterator(const TLinkedListConstIterator& other)
		: mNode(other.mNode)
	{ }

	template<class ElementType>
	TLinkedListConstIterator<ElementType>& TLinkedListConstIterator<ElementType>::operator=(const TLinkedListConstIterator& other)
	{
		mNode = other.mNode;

		return *this;
	}

	template<class ElementType>
	TLinkedListConstIterator<ElementType>& TLinkedListConstIterator<ElementType>::operator++()
	{
		mNode = mNode->mNext;

		return *this;
	}

	template<class ElementType>
	TLinkedListConstIterator<ElementType> TLinkedListConstIterator<ElementType>::operator++(int)
	{
		TLinkedListConstIterator temp = *this;
		mNode = mNode->mNext;

		return temp;
	}

	template<class ElementType>
	const ElementType& TLinkedListConstIterator<ElementType>::operator*()
	{
		return mNode->mElement;
	}

	/*
	*
	* TSinglyListIterator
	*
	*/

	template<class ElementType>
	TLinkedListIterator<ElementType>::TLinkedListIterator()
		: Base()
	{ }

	template<class ElementType>
	TLinkedListIterator<ElementType>::TLinkedListIterator(TLinkedList<ElementType>& container, size_t startIndex)
		: Base(container, startIndex)
	{ }

	template<class ElementType>
	TLinkedListIterator<ElementType>::TLinkedListIterator(TLinkedListNode<ElementType>& node)
		: Base(node)
	{ }

	template<class ElementType>
	TLinkedListIterator<ElementType>::TLinkedListIterator(const TLinkedListConstIterator<ElementType>& other)
		: Base(other)
	{ }

	template<class ElementType>
	TLinkedListIterator<ElementType>& TLinkedListIterator<ElementType>::operator=(const TLinkedListConstIterator<ElementType>& other)
	{
		Base::operator=(other);

		return *this;
	}

	template<class ElementType>
	TLinkedListIterator<ElementType>& TLinkedListIterator<ElementType>::operator++()
	{
		Base::operator++();

		return *this;
	}

	template<class ElementType>
	TLinkedListIterator<ElementType> TLinkedListIterator<ElementType>::operator++(int)
	{
		TLinkedListConstIterator temp = *this;
		Base::operator++();

		return temp;
	}

	template<class ElementType>
	ElementType& TLinkedListIterator<ElementType>::operator*()
	{
		return const_cast<ElementType&>(Base::operator*());
	}

	/*
	*
	* TSinglyList
	*
	*/

	template<class ElementType>
	TLinkedList<ElementType>::TLinkedList(MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
	{
		mHead->mNext = mTail;
		mHead->mPrev = nullptr;

		mTail->mPrev = mHead;
		mTail->mNext = nullptr;
	}

	template<class ElementType>
	TLinkedList<ElementType>::TLinkedList(size_t count, const ElementType& element, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TLinkedListNode<ElementType>* prevNode = mHead;

		for (size_t i = 0; i < count; ++i)
		{
			TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
			new(newNode) TLinkedListNode<ElementType>(element);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	template<class IteratorType>
	TLinkedList<ElementType>::TLinkedList(IteratorType first, IteratorType last, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TLinkedListNode<ElementType>* prevNode = mHead;

		for (IteratorType iter = first; iter != last; ++iter)
		{
			TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
			new(newNode) TLinkedListNode<ElementType>(*iter);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	TLinkedList<ElementType>::TLinkedList(const TLinkedList& other)
		: mPool(other.mPool)
		, mHead(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TLinkedListNode<ElementType>* otherNode = other.mHead;
		TLinkedListNode<ElementType>* prevNode = mHead;

		while (otherNode->mNext != other.mTail)
		{
			otherNode = otherNode->mNext;

			TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
			new(newNode) TLinkedListNode<ElementType>(otherNode->mElement);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	TLinkedList<ElementType>::TLinkedList(const TLinkedList& other, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TLinkedListNode<ElementType>* otherNode = other.mHead;
		TLinkedListNode<ElementType>* prevNode = mHead;

		while (otherNode->mNext != other.mTail)
		{
			otherNode = otherNode->mNext;

			TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
			new(newNode) TLinkedListNode<ElementType>(otherNode->mElement);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	TLinkedList<ElementType>::TLinkedList(TLinkedList&& other)
		: mPool(other.mPool)
		, mHead(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
	{
		mHead->mNext = other.mHead->mNext;
		mHead->mPrev = nullptr;

		mTail->mPrev = other.mTail->mPrev;
		mTail->mNext = nullptr;

		other.mHead->mNext = other.mTail;
		other.mTail->mPrev = other.mHead;
	}

	template<class ElementType>
	TLinkedList<ElementType>::TLinkedList(std::initializer_list<ElementType> init, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
		, mTail(reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TLinkedListNode<ElementType>* prevNode = mHead;

		for (auto iter = init.begin(); iter != init.end(); ++iter)
		{
			TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
			new(newNode) TLinkedListNode<ElementType>(*iter);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	TLinkedList<ElementType>& TLinkedList<ElementType>::operator=(const TLinkedList& other)
	{
		if (*this != other)
		{
			TLinkedListNode<ElementType>* setElementNode = mHead;
			TLinkedListNode<ElementType>* getElementNode = other.mHead;

			while (setElementNode->mNext != mTail || getElementNode->mNext != other.mTail)
			{
				setElementNode = setElementNode->mNext;
				getElementNode = getElementNode->mNext;

				setElementNode->mElement = getElementNode->mElement;
			}

			if (setElementNode->mNext != mTail)
			{
				TLinkedListNode<ElementType>* tempNode = setElementNode;

				setElementNode = setElementNode->mNext;

				while (setElementNode != mTail)
				{
					mPool->Deallocate(setElementNode, sizeof(TLinkedListNode<ElementType>));
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

					TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
					new(newNode) TLinkedListNode<ElementType>(getElementNode->mElement);

					newNode->mPrev = setElementNode;
					setElementNode->mNext = newNode;

					setElementNode = newNode;
				}

				mTail->mPrev = setElementNode;
				setElementNode->mNext = mTail;
			}
		}
	}

	template<class ElementType>
	TLinkedList<ElementType>& TLinkedList<ElementType>::operator=(TLinkedList&& other)
	{
		if (*this != other)
		{
			Swap(other);
		}
	}

	template<class ElementType>
	TLinkedList<ElementType>::~TLinkedList()
	{
		TLinkedListNode<ElementType>* tempNode;

		while (mHead != mTail)
		{
			tempNode = mHead;
			mHead = mHead->mNext;
			mPool->Deallocate(tempNode, sizeof(TLinkedListNode<ElementType>));
		}

		mPool->Deallocate(mTail, sizeof(TLinkedListNode<ElementType>));
	}

	template<class ElementType>
	bool TLinkedList<ElementType>::IsEmpty() const
	{
		return (mHead->mNext != mTail);
	}

	template<class ElementType>
	ElementType& TLinkedList<ElementType>::GetFront()
	{
		assert(IsEmpty());

		return mHead->mNext->mElement;
	}

	template<class ElementType>
	const ElementType& TLinkedList<ElementType>::GetFront() const
	{
		assert(IsEmpty());

		return mHead->mNext->mElement;
	}

	template<class ElementType>
	ElementType& TLinkedList<ElementType>::GetBack()
	{
		assert(IsEmpty());

		return mTail->mPrev->mElement;
	}

	template<class ElementType>
	const ElementType& TLinkedList<ElementType>::GetBack() const
	{
		assert(IsEmpty());

		return mTail->mPrev->mElement;
	}

	template<class ElementType>
	size_t TLinkedList<ElementType>::GetMaxSize() const
	{

	}

	template<class ElementType>
	TLinkedList<ElementType>::Iterator TLinkedList<ElementType>::begin()
	{
		return Iterator(mHead->mNext);
	}

	template<class ElementType>
	TLinkedList<ElementType>::Iterator TLinkedList<ElementType>::end()
	{
		return Iterator(mTail);
	}

	template<class ElementType>
	TLinkedList<ElementType>::Iterator TLinkedList<ElementType>::GetBeginIterator()
	{
		return Iterator(mHead->mNext);
	}

	template<class ElementType>
	TLinkedList<ElementType>::Iterator TLinkedList<ElementType>::GetEndIterator()
	{
		return Iterator(mTail);
	}

	template<class ElementType>
	TLinkedList<ElementType>::ConstIterator TLinkedList<ElementType>::GetBeginConstIterator()
	{
		return ConstIterator(mHead->mNext);
	}

	template<class ElementType>
	TLinkedList<ElementType>::ConstIterator TLinkedList<ElementType>::GetEndConstIterator()
	{
		return ConstIterator(mTail);
	}

	template<class ElementType>
	void TLinkedList<ElementType>::Clear()
	{
		while (mHead->mNext != mTail)
		{
			TLinkedListNode<ElementType>* tempNode = mHead->mNext;
			mHead->mNext = mHead->mNext->mNext;

			mPool->Deallocate(tempNode, sizeof(TLinkedListNode<ElementType>));
		}

		mTail->mPrev = mHead;
	}

	template<class ElementType>
	TLinkedList<ElementType>::Iterator TLinkedList<ElementType>::Insert(ConstIterator position, const ElementType& element)
	{
		assert(position.mNode != mHead);

		TLinkedListNode<ElementType>* positionNode = position.mNode;
		TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
		new(newNode) TLinkedListNode<ElementType>(element);

		positionNode->mPrev->mNext = newNode;
		newNode->mPrev = positionNode->mPrev;

		positionNode->mPrev = newNode;
		newNode->mNext = positionNode;

		return Iterator(newNode);
	}

	template<class ElementType>
	TLinkedList<ElementType>::Iterator TLinkedList<ElementType>::Insert(ConstIterator position, size_t count, const ElementType& element)
	{
		assert(position.mNode != mHead);

		if (count = 0)
		{
			return Iterator(position);
		}

		TLinkedListNode<ElementType>* prevNode = position.mNode->mPrev;
		Iterator returnIterator(prevNode);

		for (size_t i = 0; i < count; ++i)
		{
			TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
			new(newNode) TLinkedListNode<ElementType>(element);

			prevNode->mNext = newNode;
			newNode->mPrev = prevNode;

			prevNode = newNode;
		}

		prevNode->mNext = position.mNode;
		position.mNode->mPrev = prevNode;

		return ++returnIterator;
	}

	template<class ElementType>
	template<class IteratorType>
	TLinkedList<ElementType>::Iterator TLinkedList<ElementType>::Insert(ConstIterator position, IteratorType first, IteratorType last)
	{
		assert(position.mNode != mHead);

		if (first == last)
		{
			return Iterator(position);
		}

		TLinkedListNode<ElementType>* prevNode = position.mNode->mPrev;
		Iterator returnIterator(prevNode);

		for (auto iter = first; iter != last; ++iter)
		{
			TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
			new(newNode) TLinkedListNode<ElementType>(*iter);

			prevNode->mNext = newNode;
			newNode->mPrev = prevNode;

			prevNode = newNode;
		}

		prevNode->mNext = position.mNode;
		position.mNode->mPrev = prevNode;

		return ++returnIterator;
	}

	template<class ElementType>
	TLinkedList<ElementType>::Iterator TLinkedList<ElementType>::Delete(ConstIterator position)
	{
		assert(position.mNode != mHead);
		assert(position.mNode != mTail);

		Iterator returnIterator(position.mNode->mPrev);

		position.mNode->mNext->mPrev = position.mNode->mPrev;
		position.mNode->mPrev->mNext = position.mNode->mNext;

		mPool->Deallocate(position.mNode, sizeof(TLinkedListNode<ElementType>));

		return returnIterator;
	}

	template<class ElementType>
	TLinkedList<ElementType>::Iterator TLinkedList<ElementType>::Delete(ConstIterator first, ConstIterator last)
	{
		assert(first.mNode != mHead);

		TLinkedListNode<ElementType>* deleteNode = first.mNode;

		Iterator returnIterator(first.mNode->mPrev);

		first.mNode->mPrev->mNext = last.mNode;
		last.mNode->mPrev = first.mNode->mPrev;

		while (deleteNode != last.mNode)
		{
			TLinkedListNode<ElementType>* tempNode = deleteNode;
			deleteNode = deleteNode->mNext;

			mPool->Deallocate(tempNode, sizeof(TLinkedListNode<ElementType>));
		}

		return returnIterator;
	}

	template<class ElementType>
	void TLinkedList<ElementType>::InsertFront(const ElementType& element)
	{
		TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
		new(newNode) TLinkedListNode<ElementType>(element);

		mHead->mNext->mPrev = newNode;
		newNode->mNext = mHead->mNext;

		mHead->mNext = newNode;
		newNode->mPrev = mHead;
	}

	template<class ElementType>
	void TLinkedList<ElementType>::InsertBack(const ElementType& element)
	{
		TLinkedListNode<ElementType>* newNode = reinterpret_cast<TLinkedListNode<ElementType>*>(mPool->Allocate(sizeof(TLinkedListNode<ElementType>)));
		new(newNode) TLinkedListNode<ElementType>(element);

		mTail->mPrev->mNext = newNode;
		newNode->mPrev = mTail->mPrev;

		mTail->mPrev = newNode;
		newNode->mNext = mTail;
	}
	
	template<class ElementType>
	void TLinkedList<ElementType>::DeleteFront()
	{
		assert(!IsEmpty());

		TLinkedListNode<ElementType>* tempNode = mHead->mNext;

		mHead->mNext->mNext->mPrev = mHead;
		mHead->mNext = mHead->mNext->mNext;

		mPool->Deallocate(tempNode, sizeof(TLinkedListNode<ElementType>));
	}

	template<class ElementType>
	void TLinkedList<ElementType>::DeleteBack()
	{
		assert(!IsEmpty());

		TLinkedListNode<ElementType>* tempNode = mTail->mPrev;

		mTail->mPrev->mPrev->mNext = mTail;
		mTail->mPrev = mTail->mPrev->mPrev;

		mPool->Deallocate(tempNode, sizeof(TLinkedListNode<ElementType>));
	}

	template<class ElementType>
	void TLinkedList<ElementType>::Swap(const TLinkedList& other)
	{
		TLinkedListNode<ElementType>* tempHead = mHead;
		TLinkedListNode<ElementType>* tempTail = mTail;

		mHead = other.mHead;
		mTail = other.mTail;

		other.mHead = tempHead;
		other.mTail = tempTail;
	}
}