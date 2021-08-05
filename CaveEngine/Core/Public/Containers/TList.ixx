/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
export module TList;

#include "Memory/Memory.h"
#include "Memory/MemoryPool.h"
#include "CoreGlobals.h"

import IteratorType;

export namespace cave
{
	template<class ElementType>
	struct TListNode {
		ElementType mElement;
		TListNode* mNext;
		TListNode* mPrev;

		TListNode(const ElementType& element)
			: mElement(element)
			, mNext(nullptr)
			, mPrev(nullptr)
		{ }
	};

	template<class ElementType>
	class TList;

	template<class ElementType>
	class TListConstIterator
	{
		friend TList<ElementType>;

		TListConstIterator();
		TListConstIterator(TList<ElementType>& container, size_t startIndex = 0);
		TListConstIterator(const TListConstIterator& other);

		TListConstIterator& operator=(const TListConstIterator& other);

		TListConstIterator& operator++();
		TListConstIterator operator++(int);

		const ElementType& operator*();

	protected:
		TListConstIterator(TListNode<ElementType>& node);

	private:
		TListNode<ElementType>* mNode;
	};

	template<class ElementType>
	class TListIterator : public TListConstIterator<ElementType>
	{
		using Base = TListConstIterator<ElementType>;

		TListIterator();
		TListIterator(TList<ElementType>& container, size_t startIndex = 0);
		TListIterator(const TListConstIterator<ElementType>& other);

		TListIterator& operator=(const TListConstIterator<ElementType>& other);

		TListIterator& operator++();
		TListIterator operator++(int);

		ElementType& operator*();

	protected:
		TListIterator(TListNode<ElementType>& node);
	};

	template<class ElementType>
	class TList
	{
	public:
		using ConstIterator = TListConstIterator<ElementType>;
		using Iterator = TListIterator<ElementType>;

		TList(MemoryPool& pool = gCoreMemoryPool);
		TList(size_t count, const ElementType& element, MemoryPool& pool = gCoreMemoryPool);
		template<class IteratorType>
		TList(IteratorType first, IteratorType last, MemoryPool& pool = gCoreMemoryPool);
		TList(const TList& other);
		TList(const TList& other, MemoryPool& pool);
		TList(TList&& other);
		TList(std::initializer_list<ElementType> init, MemoryPool& pool = gCoreMemoryPool);

		TList& operator=(const TList& other);
		TList& operator=(TList&& other);

		virtual ~TList();

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

		void Swap(const TList& other);

	private:
		MemoryPool* mPool;
		TListNode<ElementType>* mHead;
		TListNode<ElementType>* mTail;
	};

	/*
	*
	* TSinglyListConstIterator
	* 
	*/

	template<class ElementType>
	TListConstIterator<ElementType>::TListConstIterator()
		: mNode(nullptr)
	{ }

	template<class ElementType>
	TListConstIterator<ElementType>::TListConstIterator(TList<ElementType>& container, size_t startIndex)
	{
		mNode = container.GetBeginIterator().mNode;

		for (size_t i = 0; i < startIndex; ++i)
		{
			mNode = mNode->mNext;
		}
	}

	template<class ElementType>
	TListConstIterator<ElementType>::TListConstIterator(TListNode<ElementType>& node)
		: mNode(node)
	{ }

	template<class ElementType>
	TListConstIterator<ElementType>::TListConstIterator(const TListConstIterator& other)
		: mNode(other.mNode)
	{ }

	template<class ElementType>
	TListConstIterator<ElementType>& TListConstIterator<ElementType>::operator=(const TListConstIterator& other)
	{
		mNode = other.mNode;

		return *this;
	}

	template<class ElementType>
	TListConstIterator<ElementType>& TListConstIterator<ElementType>::operator++()
	{
		mNode = mNode->mNext;

		return *this;
	}

	template<class ElementType>
	TListConstIterator<ElementType> TListConstIterator<ElementType>::operator++(int)
	{
		TListConstIterator temp = *this;
		mNode = mNode->mNext;

		return temp;
	}

	template<class ElementType>
	const ElementType& TListConstIterator<ElementType>::operator*()
	{
		return mNode->mElement;
	}

	/*
	*
	* TSinglyListIterator
	*
	*/

	template<class ElementType>
	TListIterator<ElementType>::TListIterator()
		: Base()
	{ }

	template<class ElementType>
	TListIterator<ElementType>::TListIterator(TList<ElementType>& container, size_t startIndex)
		: Base(container, startIndex)
	{ }

	template<class ElementType>
	TListIterator<ElementType>::TListIterator(TListNode<ElementType>& node)
		: Base(node)
	{ }

	template<class ElementType>
	TListIterator<ElementType>::TListIterator(const TListConstIterator<ElementType>& other)
		: Base(other)
	{ }

	template<class ElementType>
	TListIterator<ElementType>& TListIterator<ElementType>::operator=(const TListConstIterator<ElementType>& other)
	{
		Base::operator=(other);

		return *this;
	}

	template<class ElementType>
	TListIterator<ElementType>& TListIterator<ElementType>::operator++()
	{
		Base::operator++();

		return *this;
	}

	template<class ElementType>
	TListIterator<ElementType> TListIterator<ElementType>::operator++(int)
	{
		TListConstIterator temp = *this;
		Base::operator++();

		return temp;
	}

	template<class ElementType>
	ElementType& TListIterator<ElementType>::operator*()
	{
		return const_cast<ElementType&>(Base::operator*());
	}

	/*
	*
	* TSinglyList
	*
	*/

	template<class ElementType>
	TList<ElementType>::TList(MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
		, mTail(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
	{
		mHead->mNext = mTail;
		mHead->mPrev = nullptr;

		mTail->mPrev = mHead;
		mTail->mNext = nullptr;
	}

	template<class ElementType>
	TList<ElementType>::TList(size_t count, const ElementType& element, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
		, mTail(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TListNode<ElementType>* prevNode = mHead;

		for (size_t i = 0; i < count; ++i)
		{
			TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
			new(newNode) TListNode<ElementType>(element);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	template<class IteratorType>
	TList<ElementType>::TList(IteratorType first, IteratorType last, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
		, mTail(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TListNode<ElementType>* prevNode = mHead;

		for (IteratorType iter = first; iter != last; ++iter)
		{
			TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
			new(newNode) TListNode<ElementType>(*iter);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	TList<ElementType>::TList(const TList& other)
		: mPool(other.mPool)
		, mHead(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
		, mTail(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TListNode<ElementType>* otherNode = other.mHead;
		TListNode<ElementType>* prevNode = mHead;

		while (otherNode->mNext != other.mTail)
		{
			otherNode = otherNode->mNext;

			TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
			new(newNode) TListNode<ElementType>(otherNode->mElement);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	TList<ElementType>::TList(const TList& other, MemoryPool& pool)
		: mPool(&pool)
		, mHead(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
		, mTail(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TListNode<ElementType>* otherNode = other.mHead;
		TListNode<ElementType>* prevNode = mHead;

		while (otherNode->mNext != other.mTail)
		{
			otherNode = otherNode->mNext;

			TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
			new(newNode) TListNode<ElementType>(otherNode->mElement);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	TList<ElementType>::TList(TList&& other)
		: mPool(other.mPool)
		, mHead(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
		, mTail(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
	{
		mHead->mNext = other.mHead->mNext;
		mHead->mPrev = nullptr;

		mTail->mPrev = other.mTail->mPrev;
		mTail->mNext = nullptr;

		other.mHead->mNext = other.mTail;
		other.mTail->mPrev = other.mHead;
	}

	template<class ElementType>
	TList<ElementType>::TList(std::initializer_list<ElementType> init, MemoryPool& pool)
		: mPool(&Pool)
		, mHead(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
		, mTail(reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>))))
	{
		mHead->mPrev = nullptr;
		mTail->mNext = nullptr;

		TListNode<ElementType>* prevNode = mHead;

		for (auto iter = init.begin(); iter != init.end(); ++iter)
		{
			TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
			new(newNode) TListNode<ElementType>(*iter);

			newNode->mPrev = prevNode;
			prevNode->mNext = newNode;

			prevNode = newNode;
		}

		mTail->mPrev = prevNode;
		prevNode->mNext = mTail;
	}

	template<class ElementType>
	TList<ElementType>& TList<ElementType>::operator=(const TList& other)
	{
		if (*this != other)
		{
			TListNode<ElementType>* setElementNode = mHead;
			TListNode<ElementType>* getElementNode = other.mHead;

			while (setElementNode->mNext != mTail || getElementNode->mNext != other.mTail)
			{
				setElementNode = setElementNode->mNext;
				getElementNode = getElementNode->mNext;

				setElementNode->mElement = getElementNode->mElement;
			}

			if (setElementNode->mNext != mTail)
			{
				TListNode<ElementType>* tempNode = setElementNode;

				setElementNode = setElementNode->mNext;

				while (setElementNode != mTail)
				{
					mPool->Deallocate(setElementNode, sizeof(TListNode<ElementType>));
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

					TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
					new(newNode) TListNode<ElementType>(getElementNode->mElement);

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
	TList<ElementType>& TList<ElementType>::operator=(TList&& other)
	{
		if (*this != other)
		{
			Swap(other);
		}
	}

	template<class ElementType>
	TList<ElementType>::~TList()
	{
		TListNode<ElementType>* tempNode;

		while (mHead != mTail)
		{
			tempNode = mHead;
			mHead = mHead->mNext;
			mPool->Deallocate(tempNode, sizeof(TListNode<ElementType>));
		}

		mPool->Deallocate(mTail, sizeof(TListNode<ElementType>));
	}

	template<class ElementType>
	bool TList<ElementType>::IsEmpty() const
	{
		return (mHead->mNext != mTail);
	}

	template<class ElementType>
	ElementType& TList<ElementType>::GetFront()
	{
		assert(IsEmpty());

		return mHead->mNext->mElement;
	}

	template<class ElementType>
	const ElementType& TList<ElementType>::GetFront() const
	{
		assert(IsEmpty());

		return mHead->mNext->mElement;
	}

	template<class ElementType>
	ElementType& TList<ElementType>::GetBack()
	{
		assert(IsEmpty());

		return mTail->mPrev->mElement;
	}

	template<class ElementType>
	const ElementType& TList<ElementType>::GetBack() const
	{
		assert(IsEmpty());

		return mTail->mPrev->mElement;
	}

	template<class ElementType>
	size_t TList<ElementType>::GetMaxSize() const
	{

	}

	template<class ElementType>
	TList<ElementType>::Iterator TList<ElementType>::begin()
	{
		return Iterator(mHead->mNext);
	}

	template<class ElementType>
	TList<ElementType>::Iterator TList<ElementType>::end()
	{
		return Iterator(mTail);
	}

	template<class ElementType>
	TList<ElementType>::Iterator TList<ElementType>::GetBeginIterator()
	{
		return Iterator(mHead->mNext);
	}

	template<class ElementType>
	TList<ElementType>::Iterator TList<ElementType>::GetEndIterator()
	{
		return Iterator(mTail);
	}

	template<class ElementType>
	TList<ElementType>::ConstIterator TList<ElementType>::GetBeginConstIterator()
	{
		return ConstIterator(mHead->mNext);
	}

	template<class ElementType>
	TList<ElementType>::ConstIterator TList<ElementType>::GetEndConstIterator()
	{
		return ConstIterator(mTail);
	}

	template<class ElementType>
	void TList<ElementType>::Clear()
	{
		while (mHead->mNext != mTail)
		{
			TListNode<ElementType>* tempNode = mHead->mNext;
			mHead->mNext = mHead->mNext->mNext;

			mPool->Deallocate(tempNode, sizeof(TListNode<ElementType>));
		}

		mTail->mPrev = mHead;
	}

	template<class ElementType>
	TList<ElementType>::Iterator TList<ElementType>::Insert(ConstIterator position, const ElementType& element)
	{
		assert(position.mNode != mHead);

		TListNode<ElementType>* positionNode = position.mNode;
		TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
		new(newNode) TListNode<ElementType>(element);

		positionNode->mPrev->mNext = newNode;
		newNode->mPrev = positionNode->mPrev;

		positionNode->mPrev = newNode;
		newNode->mNext = positionNode;

		return Iterator(newNode);
	}

	template<class ElementType>
	TList<ElementType>::Iterator TList<ElementType>::Insert(ConstIterator position, size_t count, const ElementType& element)
	{
		assert(position.mNode != mHead);

		if (count = 0)
		{
			return Iterator(position);
		}

		TListNode<ElementType>* prevNode = position.mNode->mPrev;
		Iterator returnIterator(prevNode);

		for (size_t i = 0; i < count; ++i)
		{
			TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
			new(newNode) TListNode<ElementType>(element);

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
	TList<ElementType>::Iterator TList<ElementType>::Insert(ConstIterator position, IteratorType first, IteratorType last)
	{
		assert(position.mNode != mHead);

		if (first == last)
		{
			return Iterator(position);
		}

		TListNode<ElementType>* prevNode = position.mNode->mPrev;
		Iterator returnIterator(prevNode);

		for (auto iter = first; iter != last; ++iter)
		{
			TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
			new(newNode) TListNode<ElementType>(*iter);

			prevNode->mNext = newNode;
			newNode->mPrev = prevNode;

			prevNode = newNode;
		}

		prevNode->mNext = position.mNode;
		position.mNode->mPrev = prevNode;

		return ++returnIterator;
	}

	template<class ElementType>
	TList<ElementType>::Iterator TList<ElementType>::Delete(ConstIterator position)
	{
		assert(position.mNode != mHead);
		assert(position.mNode != mTail);

		Iterator returnIterator(position.mNode->mPrev);

		position.mNode->mNext->mPrev = position.mNode->mPrev;
		position.mNode->mPrev->mNext = position.mNode->mNext;

		mPool->Deallocate(position.mNode, sizeof(TListNode<ElementType>));

		return returnIterator;
	}

	template<class ElementType>
	TList<ElementType>::Iterator TList<ElementType>::Delete(ConstIterator first, ConstIterator last)
	{
		assert(first.mNode != mHead);

		TListNode<ElementType>* deleteNode = first.mNode;

		Iterator returnIterator(first.mNode->mPrev);

		first.mNode->mPrev->mNext = last.mNode;
		last.mNode->mPrev = first.mNode->mPrev;

		while (deleteNode != last.mNode)
		{
			TListNode<ElementType>* tempNode = deleteNode;
			deleteNode = deleteNode->mNext;

			mPool->Deallocate(tempNode, sizeof(TListNode<ElementType>));
		}

		return returnIterator;
	}

	template<class ElementType>
	void TList<ElementType>::InsertFront(const ElementType& element)
	{
		TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
		new(newNode) TListNode<ElementType>(element);

		mHead->mNext->mPrev = newNode;
		newNode->mNext = mHead->mNext;

		mHead->mNext = newNode;
		newNode->mPrev = mHead;
	}

	template<class ElementType>
	void TList<ElementType>::InsertBack(const ElementType& element)
	{
		TListNode<ElementType>* newNode = reinterpret_cast<TListNode<ElementType>*>(mPool->Allocate(sizeof(TListNode<ElementType>)));
		new(newNode) TListNode<ElementType>(element);

		mTail->mPrev->mNext = newNode;
		newNode->mPrev = mTail->mPrev;

		mTail->mPrev = newNode;
		newNode->mNext = mTail;
	}
	
	template<class ElementType>
	void TList<ElementType>::DeleteFront()
	{
		assert(!IsEmpty());

		TListNode<ElementType>* tempNode = mHead->mNext;

		mHead->mNext->mNext->mPrev = mHead;
		mHead->mNext = mHead->mNext->mNext;

		mPool->Deallocate(tempNode, sizeof(TListNode<ElementType>));
	}

	template<class ElementType>
	void TList<ElementType>::DeleteBack()
	{
		assert(!IsEmpty());

		TListNode<ElementType>* tempNode = mTail->mPrev;

		mTail->mPrev->mPrev->mNext = mTail;
		mTail->mPrev = mTail->mPrev->mPrev;

		mPool->Deallocate(tempNode, sizeof(TListNode<ElementType>));
	}

	template<class ElementType>
	void TList<ElementType>::Swap(const TList& other)
	{
		TListNode<ElementType>* tempHead = mHead;
		TListNode<ElementType>* tempTail = mTail;

		mHead = other.mHead;
		mTail = other.mTail;

		other.mHead = tempHead;
		other.mTail = tempTail;
	}
}