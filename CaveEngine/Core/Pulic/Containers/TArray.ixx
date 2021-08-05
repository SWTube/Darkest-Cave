/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

// include assertion macros
#include "Assertion/Assert.h"
// include memory
#include "CoreGlobals.h"
#include "Memory/Memory.h"
#include "Memory/MemoryPool.h"
// include template
import IteratorType;

export module TArray;

export namespace cave
{
    template<class ElementType>
    class TArray;

    template<class ElementType>
    class TArrayConstIterator
    {
    public:
        friend class TArray<ElementType>;

        constexpr TArrayConstIterator();
        constexpr TArrayConstIterator(TArray<ElementType>& container, size_t startIndex = 0);
        constexpr TArrayConstIterator(const TArrayConstIterator& other);

        constexpr TArrayConstIterator& operator=(const TArrayConstIterator& other);

        constexpr TArrayConstIterator& operator++();
        constexpr TArrayConstIterator operator++(int);

        constexpr TArrayConstIterator& operator--();
        constexpr TArrayConstIterator operator--(int);

        constexpr TArrayConstIterator& operator+=(size_t offset);
        constexpr TArrayConstIterator operator+(size_t offset);

        constexpr TArrayConstIterator& operator-=(size_t offset);
        constexpr TArrayConstIterator operator-(size_t offset);

        constexpr size_t operator-(const TArrayConstIterator& other);

        constexpr const ElementType& operator*() const;
        constexpr const ElementType& operator[](size_t offset) const;

        constexpr bool operator==(const TArrayConstIterator& other) const;
        constexpr bool operator!=(const TArrayConstIterator& other) const;
        constexpr bool operator<=(const TArrayConstIterator& other) const;
        constexpr bool operator<(const TArrayConstIterator& other) const;
        constexpr bool operator>=(const TArrayConstIterator& other) const;
        constexpr bool operator>(const TArrayConstIterator& other) const;

    private:
        TArray<ElementType>* mContainer;
        size_t mIndex;
    };

    template<typename ElementType>
    class TArrayIterator : public TArrayConstIterator<ElementType>
    {
    public:
        using Base = TArrayConstIterator<ElementType>;

        constexpr TArrayIterator();
        constexpr TArrayIterator(TArray<ElementType>& container, size_t startIndex = 0);
        constexpr TArrayIterator(const TArrayIterator& other);

        constexpr TArrayIterator& operator=(const TArrayConstIterator<ElementType>& other);

        constexpr TArrayIterator& operator++();
        constexpr TArrayIterator operator++(int);

        constexpr TArrayIterator& operator--();
        constexpr TArrayIterator operator--(int);

        constexpr TArrayIterator& operator+=(size_t offset);
        constexpr TArrayIterator operator+(size_t offset);

        constexpr TArrayIterator& operator-=(size_t offset);
        constexpr TArrayIterator operator-(size_t offset);

        constexpr ElementType& operator*();
        constexpr ElementType& operator[](size_t offset);
    };

    template<class ElementType>
    class TArray
    {
    public:
        using ConstIterator = TArrayConstIterator<ElementType>;
        using Iterator = TArrayIterator<ElementType>;

        constexpr explicit TArray(MemoryPool& pool = gCoreMemoryPool) noexcept;
        constexpr TArray(size_t count, const ElementType& value, MemoryPool& pool = gCoreMemoryPool);
        constexpr TArray(size_t count, MemoryPool& pool = gCoreMemoryPool);
        template<class IteratorType>
        requires IteratorInputAble<IteratorType, ElementType>
            constexpr TArray(IteratorType first, IteratorType last, MemoryPool& pool = gCoreMemoryPool);
        constexpr TArray(const TArray& other, MemoryPool& pool = gCoreMemoryPool);
        constexpr TArray(TArray&& other, MemoryPool& pool = gCoreMemoryPool) noexcept;
        virtual ~TArray();

        constexpr TArray& operator=(const TArray& other);
        constexpr TArray& operator=(TArray&& other);


        constexpr void Reserve(size_t maxSize);

        constexpr void Resize(size_t size, const ElementType& initializeElement);

        constexpr void ClearElements();


        constexpr void Assign(size_t count, const ElementType& initializeElement);
        template<class IteratorType>
        requires IteratorInputAble<IteratorType, ElementType>
            constexpr void Assign(IteratorType first, IteratorType last);

        constexpr Iterator Insert(ConstIterator position, const ElementType& element);
        constexpr Iterator Insert(ConstIterator position, size_t count, const ElementType& element);
        template<class IteratorType>
        requires IteratorInputAble<IteratorType, ElementType>
            constexpr Iterator Insert(ConstIterator position, IteratorType first, IteratorType last);

        constexpr Iterator Erase(ConstIterator position);
        constexpr Iterator Erase(ConstIterator first, ConstIterator last);

        constexpr void PushBack(const ElementType& element);

        constexpr void PopBack();

        constexpr bool IsEmpty() const;

        constexpr size_t GetSize() const;

        constexpr size_t GetCapacity() const;

        constexpr size_t GetMaxSize() const;


        // Element Access
        constexpr ElementType& operator[](size_t pos);
        constexpr const ElementType& operator[](size_t pos) const;

        constexpr ElementType& GetFront();
        constexpr const ElementType& GetFront() const;

        constexpr ElementType& GetBack();
        constexpr const ElementType& GetBack() const;

        constexpr ElementType* GetData() noexcept;
        constexpr const ElementType* GetData() const noexcept;

        // Iterators
        constexpr Iterator GetBeginIterator();
        constexpr Iterator GetEndIterator();
        constexpr Iterator begin();
        constexpr Iterator end();

        constexpr ConstIterator GetBeginConstIterator() const;
        constexpr ConstIterator GetEndConstIterator() const;

        constexpr bool operator==(const TArray& other) const;
        constexpr bool operator!=(const TArray& other) const;



    private:
        MemoryPool* mPool;
        size_t mSize;
        size_t mCapacity;
        ElementType* mData;
    };

    /*
    *
    * TArrayConstIterator Implement
    *
    */

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType>::TArrayConstIterator()
        : mContainer(nullptr)
        , mIndex(0)
    { }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType>::TArrayConstIterator(TArray<ElementType>& container, size_t startIndex)
        : mContainer(&container)
        , mIndex(startIndex)
    { }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType>::TArrayConstIterator(const TArrayConstIterator& other)
        : mContainer(other.mContainer)
        , mIndex(other.mIndex)
    { }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType>& TArrayConstIterator<ElementType>::operator=(const TArrayConstIterator& other)
    {
        mContainer = other.mContainer;
        mIndex = other.mIndex;

        return *this;
    }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType>& TArrayConstIterator<ElementType>::operator++()
    {
        ++mIndex;

        return *this;
    }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType> TArrayConstIterator<ElementType>::operator++(int)
    {
        TArrayConstIterator temp = *this;
        ++mIndex;

        return temp;
    }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType>& TArrayConstIterator<ElementType>::operator--()
    {
        --mIndex;

        return *this;
    }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType> TArrayConstIterator<ElementType>::operator--(int)
    {
        TArrayConstIterator temp = *this;
        --mIndex;

        return temp;
    }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType>& TArrayConstIterator<ElementType>::operator+=(size_t offset)
    {
        mIndex += offset;

        return *this;
    }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType> TArrayConstIterator<ElementType>::operator+(size_t offset)
    {
        mIndex += offset;
        TArrayConstIterator temp = *this;

        return temp;
    }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType>& TArrayConstIterator<ElementType>::operator-=(size_t offset)
    {
        mIndex -= offset;

        return *this;
    }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType> TArrayConstIterator<ElementType>::operator-(size_t offset)
    {
        mIndex -= offset;
        TArrayConstIterator temp = *this;

        return temp;
    }

    template<class ElementType>
    constexpr size_t TArrayConstIterator<ElementType>::operator-(const TArrayConstIterator& other)
    {
        return mIndex - other.mIndex;
    }

    template<class ElementType>
    constexpr const ElementType& TArrayConstIterator<ElementType>::operator*() const
    {
        return (*mContainer)[mIndex];
    }

    template<class ElementType>
    constexpr const ElementType& TArrayConstIterator<ElementType>::operator[](size_t offset) const
    {
        return (*mContainer)[mIndex + offset];
    }

    template<class ElementType>
    constexpr bool TArrayConstIterator<ElementType>::operator==(const TArrayConstIterator& other) const
    {
        return (mIndex == other.mIndex && mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr bool TArrayConstIterator<ElementType>::operator!=(const TArrayConstIterator& other) const
    {
        return (mIndex != other.mIndex || mContainer != other.mContainer);
    }

    template<class ElementType>
    constexpr bool TArrayConstIterator<ElementType>::operator<=(const TArrayConstIterator& other) const
    {
        return (mIndex <= other.mIndex && mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr bool TArrayConstIterator<ElementType>::operator<(const TArrayConstIterator& other) const
    {
        return (mIndex < other.mIndex&& mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr bool TArrayConstIterator<ElementType>::operator>=(const TArrayConstIterator& other) const
    {
        return (mIndex >= other.mIndex && mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr bool TArrayConstIterator<ElementType>::operator>(const TArrayConstIterator& other) const
    {
        return (mIndex > other.mIndex && mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr TArrayConstIterator<ElementType> operator+(size_t offset, TArrayConstIterator<ElementType> Iterator)
    {
        return Iterator += offset;
    }

    /*
    *
    * TArrayIterator Implement
    *
    */

    template<class ElementType>
    constexpr TArrayIterator<ElementType>::TArrayIterator()
        : Base()
    { }

    template<class ElementType>
    constexpr TArrayIterator<ElementType>::TArrayIterator(TArray<ElementType>& container, size_t startIndex)
        : Base(container, startIndex)
    { }

    template<class ElementType>
    constexpr TArrayIterator<ElementType>::TArrayIterator(const TArrayIterator& other)
        : Base(other)
    { }

    template<class ElementType>
    constexpr TArrayIterator<ElementType>& TArrayIterator<ElementType>::operator=(const TArrayConstIterator<ElementType>& other)
    {
        Base::operator=(other);

        return *this;
    }

    template<class ElementType>
    constexpr TArrayIterator<ElementType>& TArrayIterator<ElementType>::operator++()
    {
        Base::operator++();

        return *this;
    }

    template<class ElementType>
    constexpr TArrayIterator<ElementType> TArrayIterator<ElementType>::operator++(int)
    {
        TArrayIterator Temp = *this;
        Base::operator++();

        return Temp;
    }

    template<class ElementType>
    constexpr TArrayIterator<ElementType>& TArrayIterator<ElementType>::operator--()
    {
        Base::operator--();

        return *this;
    }

    template<class ElementType>
    constexpr TArrayIterator<ElementType> TArrayIterator<ElementType>::operator--(int)
    {
        TArrayIterator Temp = *this;
        Base::operator--();

        return Temp;
    }

    template<class ElementType>
    constexpr TArrayIterator<ElementType>& TArrayIterator<ElementType>::operator+=(size_t offset)
    {
        Base::operator+=(offset);

        return *this;
    }

    template<class ElementType>
    constexpr TArrayIterator<ElementType> TArrayIterator<ElementType>::operator+(size_t offset)
    {
        TArrayIterator Temp = *this;

        return Temp += offset;
    }

    template<class ElementType>
    constexpr TArrayIterator<ElementType>& TArrayIterator<ElementType>::operator-=(size_t offset)
    {
        Base::operator-=(offset);

        return *this;
    }

    template<class ElementType>
    constexpr TArrayIterator<ElementType> TArrayIterator<ElementType>::operator-(size_t offset)
    {
        TArrayIterator Temp = *this;

        return Temp -= offset;

    }

    template<class ElementType>
    constexpr ElementType& TArrayIterator<ElementType>::operator*()
    {
        return const_cast<ElementType&>(Base::operator*());
    }

    template<class ElementType>
    constexpr ElementType& TArrayIterator<ElementType>::operator[](size_t offset)
    {
        return const_cast<ElementType&>(Base::operator[](offset));
    }

    template<class ElementType>
    constexpr TArrayIterator<ElementType> operator+(size_t offset, TArrayIterator<ElementType> Iterator)
    {
        return Iterator += offset;
    }

    /*
    *
    * TArray Implement
    *
    */

    template<class ElementType>
    constexpr TArray<ElementType>::TArray(MemoryPool& pool) noexcept
        : mPool(&pool)
        , mSize(0)
        , mCapacity(0)
        , mData(nullptr)
    { }

    template<class ElementType>
    constexpr TArray<ElementType>::TArray(size_t count, const ElementType& value, MemoryPool& pool)
        : mPool(&pool)
        , mSize(count)
        , mCapacity(mSize)
        , mData(reinterpret_cast<ElementType*>(mPool->Allocate(sizeof(ElementType)* mCapacity)))
    {
        for (size_t i = 0; i < count; ++i)
        {
            mData[i] = value;
        }
    }

    template<class ElementType>
    constexpr TArray<ElementType>::TArray(size_t count, MemoryPool& pool)
        : mPool(&pool)
        , mSize(0)
        , mCapacity(count)
        , mData(reinterpret_cast<ElementType*>(mPool->Allocate(sizeof(ElementType)* mCapacity)))
    { }

    template<class ElementType>
    template<class IteratorType>
    requires IteratorInputAble<IteratorType, ElementType>
        constexpr TArray<ElementType>::TArray(IteratorType first, IteratorType last, MemoryPool& pool)
        : mPool(&pool)
    {
        //GetIteratorDIstance(first, last)

        size_t count = 0;
        for (IteratorType iter = first; iter != last; ++iter, ++count);

        mSize = count;
        mCapacity = count;
        mData = reinterpret_cast<ElementType*>(mPool->Allocate(sizeof(ElementType) * count));
        new(mData) ElementType[count];

        size_t i = 0;
        for (IteratorType iterator = first; iterator != last; ++iterator, ++i)
        {
            mData[i] = *iterator;
        }
    }

    template<class ElementType>
    constexpr TArray<ElementType>::TArray(const TArray& other, MemoryPool& pool)
        : mPool(&pool)
        , mSize(other.mSize)
        , mCapacity(other.mCapacity)
        , mData(nullptr)
    {
        if (mCapacity > 0)
        {
            mData = reinterpret_cast<ElementType*>(mPool->Allocate(sizeof(ElementType) * mCapacity));
            Memory::Memcpy(mData, other.mData, sizeof(ElementType) * mSize);
        }
    }

    template<class ElementType>
    constexpr TArray<ElementType>::TArray(TArray&& other, MemoryPool& pool) noexcept
        : mPool(&pool)
        , mSize(other.mSize)
        , mCapacity(other.mCapacity)
        , mData(other.mData)
    {
        other.mCapacity = 0;
        other.mSize = 0;
        other.mData = nullptr;
    }

    template<class ElementType>
    TArray<ElementType>::~TArray()
    {
        if (mData != nullptr)
        {
            mPool->Deallocate(mData, mCapacity * sizeof(ElementType));
        }
    }

    template<class ElementType>
    constexpr TArray<ElementType>& TArray<ElementType>::operator=(const TArray& other)
    {
        if (this != &other)
        {
            ClearElements();
            Reserve(other.mCapacity);
            mSize = other.mSize;

            Memory::Memcpy(mData, other.mData, sizeof(ElementType) * mSize);
        }

        return *this;
    }

    template<class ElementType>
    constexpr TArray<ElementType>& TArray<ElementType>::operator=(TArray&& other)
    {
        if (this != &other)
        {
            mCapacity = other.mCapacity;
            mSize = other.mSize;
            mData = other.mData;
            other.mCapacity = 0;
            other.mSize = 0;
            other.mData = nullptr;
        }

        return *this;
    }

    template<class ElementType>
    constexpr void TArray<ElementType>::Reserve(size_t maxSize)
    {
        assert(maxSize <= GetMaxSize());

        if (maxSize > mCapacity)
        {
            ElementType* temp = reinterpret_cast<ElementType*>(mPool->Allocate(sizeof(ElementType) * maxSize));

            if (mData != nullptr)
            {
                Memory::Memcpy(temp, mData, mSize * sizeof(ElementType));
                mPool->Deallocate(mData, mCapacity * sizeof(ElementType));
            }

            mData = temp;
            mCapacity = maxSize;
        }
    }

    template<class ElementType>
    constexpr void TArray<ElementType>::Resize(size_t size, const ElementType& initializeElement)
    {
        assert(size <= GetMaxSize());

        if (size > mCapacity)
        {
            Reserve(size);
        }

        if (size > mSize)
        {
            for (int i = mSize; i < size; ++i)
            {
                mData[i] = initializeElement;
            }
        }

        mSize = size;
    }

    template<class ElementType>
    constexpr void TArray<ElementType>::ClearElements()
    {
        mSize = 0;
    }

    template<class ElementType>
    constexpr void TArray<ElementType>::Assign(size_t count, const ElementType& initializeElement)
    {
        ClearElements();
        Resize(count, initializeElement);
    }

    template<class ElementType>
    template<class IteratorType>
    requires IteratorInputAble<IteratorType, ElementType>
        constexpr void TArray<ElementType>::Assign(IteratorType first, IteratorType last)
    {
        size_t count = 0;
        for (IteratorType iterator = first; iterator != last; ++iterator, ++count);

        ClearElements();
        Reserve(count);

        size_t i = 0;
        for (IteratorType iterator = first; iterator != last; ++iterator, ++i)
        {
            mData[i] = *iterator;
        }
        mSize = count;
    }

    template<class ElementType>
    constexpr TArray<ElementType>::Iterator TArray<ElementType>::Insert(ConstIterator position, const ElementType& element)
    {
        size_t index = position.mIndex;

        assert(index >= 0);
        assert(index <= mSize);

        size_t newMaxSize = mCapacity;

        if (newMaxSize == 0)
        {
            newMaxSize = 1;
        }
        if (mSize + 1 > newMaxSize)
        {
            newMaxSize <<= 1;
        }
        Reserve(newMaxSize);

        Memory::Memmove(mData + index + 1, mData + index, sizeof(ElementType) * (mSize - index));

        mSize += 1;
        mData[index] = element;

        return Iterator(*this, index);
    }

    template<class ElementType>
    constexpr TArray<ElementType>::Iterator TArray<ElementType>::Insert(ConstIterator position, size_t count, const ElementType& element)
    {
        size_t index = position.mIndex;

        assert(index >= 0);
        assert(index <= mSize);

        size_t newMaxSize = mCapacity;

        if (newMaxSize == 0)
        {
            newMaxSize = 1;
        }
        while (mSize + count > newMaxSize)
        {
            newMaxSize <<= 1;
        }
        Reserve(newMaxSize);

        Memory::Memmove(mData + index + count, mData + index, sizeof(ElementType) * (mSize - index));

        mSize += count;

        for (size_t i = 0; i < count; ++i)
        {
            mData[index + i] = element;
        }

        return Iterator(*this, index);
    }

    template<class ElementType>
    template<class IteratorType>
    requires IteratorInputAble<IteratorType, ElementType>
        constexpr TArray<ElementType>::Iterator TArray<ElementType>::Insert(ConstIterator position, IteratorType first, IteratorType last)
    {
        size_t count = 0;
        size_t index = position.mIndex;

        assert(index >= 0);
        assert(index <= mSize);

        size_t newMaxSize = mCapacity;

        for (IteratorType iterator = first; iterator != last; ++iterator, ++count);

        if (newMaxSize == 0)
        {
            newMaxSize = 1;
        }
        while (mSize + count > newMaxSize)
        {
            newMaxSize <<= 1;
        }
        Reserve(newMaxSize);

        Memory::Memmove(mData + index + count, mData + index, sizeof(ElementType) * (mSize - index));

        mSize += count;

        size_t i = 0;
        for (IteratorType iterator = first; iterator != last; ++iterator, ++i)
        {
            mData[index + i] = *iterator;
        }

        return Iterator(*this, index);
    }

    template<class ElementType>
    constexpr TArray<ElementType>::Iterator TArray<ElementType>::Erase(ConstIterator position)
    {
        size_t index = position.mIndex;

        assert(index >= 0);
        assert(index < mSize);

        Memory::Memmove(mData + index, mData + index + 1, sizeof(ElementType) * (mSize - index - 1));


        mSize -= 1;

        return Iterator(*this, index);
    }

    template<class ElementType>
    constexpr TArray<ElementType>::Iterator TArray<ElementType>::Erase(ConstIterator first, ConstIterator last)
    {
        size_t count = 0;
        size_t index = first.mIndex;

        assert(first.mIndex >= 0);
        assert(last.mIndex < mSize);
        assert(first <= last);

        for (Iterator iterator = first; iterator != last; ++iterator, ++count);

        Memory::Memmove(mData + index, mData + index + count, sizeof(ElementType) * (mSize - index - count));

        mSize -= count;

        return Iterator(*this, index);
    }

    template<class ElementType>
    constexpr void TArray<ElementType>::PushBack(const ElementType& element)
    {
        Insert(GetEndIterator(), element);
    }

    template<class ElementType>
    constexpr void TArray<ElementType>::PopBack()
    {
        --mSize;
    }

    template<class ElementType>
    constexpr bool TArray<ElementType>::IsEmpty() const
    {
        return (mSize == 0);
    }

    template<class ElementType>
    constexpr size_t TArray<ElementType>::GetSize() const
    {
        return mSize;
    }

    template<class ElementType>
    constexpr size_t TArray<ElementType>::GetCapacity() const
    {
        return mCapacity;
    }

    template<class ElementType>
    constexpr size_t TArray<ElementType>::GetMaxSize() const
    {
        return mPool->GetFreeMemorySize() / sizeof(ElementType);
    }

    template<class ElementType>
    constexpr ElementType& TArray<ElementType>::operator[](size_t pos)
    {
        return *(mData + pos);
    }

    template<class ElementType>
    constexpr const ElementType& TArray<ElementType>::operator[](size_t pos) const
    {
        return *(mData + pos);
    }

    template<class ElementType>
    constexpr ElementType& TArray<ElementType>::GetFront()
    {
        return *mData;
    }

    template<class ElementType>
    constexpr const ElementType& TArray<ElementType>::GetFront() const
    {
        return *mData;
    }

    template<class ElementType>
    constexpr ElementType& TArray<ElementType>::GetBack()
    {
        return *(mData + mSize - 1);
    }

    template<class ElementType>
    constexpr const ElementType& TArray<ElementType>::GetBack() const
    {
        return *(mData + mSize - 1);
    }

    template<class ElementType>
    constexpr ElementType* TArray<ElementType>::GetData() noexcept
    {
        return mData;
    }

    template<class ElementType>
    constexpr const ElementType* TArray<ElementType>::GetData() const noexcept
    {
        return mData;
    }

    template<class ElementType>
    constexpr TArray<ElementType>::Iterator TArray<ElementType>::GetBeginIterator()
    {
        return Iterator(*this, 0);
    }

    template<class ElementType>
    constexpr TArray<ElementType>::Iterator TArray<ElementType>::begin()
    {
        return Iterator(*this, 0);
    }

    template<class ElementType>
    constexpr TArray<ElementType>::Iterator TArray<ElementType>::GetEndIterator()
    {
        return Iterator(*this, mSize);
    }

    template<class ElementType>
    constexpr TArray<ElementType>::Iterator TArray<ElementType>::end()
    {
        return Iterator(*this, mSize);
    }

    template<class ElementType>
    constexpr TArray<ElementType>::ConstIterator TArray<ElementType>::GetBeginConstIterator() const
    {
        return ConstIterator(*this, 0);
    }

    template<class ElementType>
    constexpr TArray<ElementType>::ConstIterator TArray<ElementType>::GetEndConstIterator() const
    {
        return ConstIterator(*this, mSize);
    }

    template<class ElementType>
    constexpr bool  TArray<ElementType>::operator==(const TArray<ElementType>& other) const
    {
        return mData == other.mData;
    }

    template<class ElementType>
    constexpr bool  TArray<ElementType>::operator!=(const TArray<ElementType>& other) const
    {
        return mData != other.mData;
    }
}