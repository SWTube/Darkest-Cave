/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module Array;

import IteratorType;
import Memory;

export namespace cave
{
    template<class ElementType>
    class Array;

    template<class ElementType>
    class ArrayConstIterator
    {
    public:
        friend class Array<ElementType>;

        constexpr ArrayConstIterator();
        constexpr ArrayConstIterator(Array<ElementType>& container, size_t startIndex = 0);
        constexpr ArrayConstIterator(const ArrayConstIterator& other);

        constexpr ArrayConstIterator& operator=(const ArrayConstIterator& other);

        constexpr ArrayConstIterator& operator++();
        constexpr ArrayConstIterator operator++(int);

        constexpr ArrayConstIterator& operator--();
        constexpr ArrayConstIterator operator--(int);

        constexpr ArrayConstIterator& operator+=(size_t offset);
        constexpr ArrayConstIterator operator+(size_t offset);

        constexpr ArrayConstIterator& operator-=(size_t offset);
        constexpr ArrayConstIterator operator-(size_t offset);

        constexpr size_t operator-(const ArrayConstIterator& other);

        constexpr const ElementType& operator*() const;
        constexpr const ElementType& operator[](size_t offset) const;

        constexpr bool operator==(const ArrayConstIterator& other) const;
        constexpr bool operator!=(const ArrayConstIterator& other) const;
        constexpr bool operator<=(const ArrayConstIterator& other) const;
        constexpr bool operator<(const ArrayConstIterator& other) const;
        constexpr bool operator>=(const ArrayConstIterator& other) const;
        constexpr bool operator>(const ArrayConstIterator& other) const;

    private:
        Array<ElementType>* mContainer;
        size_t mIndex;
    };

    template<typename ElementType>
    class ArrayIterator : public ArrayConstIterator<ElementType>
    {
    public:
        friend class Array<ElementType>;

        using Base = ArrayConstIterator<ElementType>;

        constexpr ArrayIterator();
        constexpr ArrayIterator(Array<ElementType>& container, size_t startIndex = 0);
        constexpr ArrayIterator(const ArrayIterator& other);

        constexpr ArrayIterator& operator=(const ArrayConstIterator<ElementType>& other);

        constexpr ArrayIterator& operator++();
        constexpr ArrayIterator operator++(int);

        constexpr ArrayIterator& operator--();
        constexpr ArrayIterator operator--(int);

        constexpr ArrayIterator& operator+=(size_t offset);
        constexpr ArrayIterator operator+(size_t offset);

        constexpr ArrayIterator& operator-=(size_t offset);
        constexpr ArrayIterator operator-(size_t offset);

        constexpr ElementType& operator*();
        constexpr ElementType& operator[](size_t offset);
    };

    template<class ElementType>
    class Array final
    {
    public:
        using ConstIterator = ArrayConstIterator<ElementType>;
        using Iterator = ArrayIterator<ElementType>;

        constexpr explicit Array() noexcept;
        constexpr explicit Array(MemoryPool& pool) noexcept;
        constexpr Array(size_t count, const ElementType& value, MemoryPool& pool = gCoreMemoryPool);
        constexpr Array(size_t count, MemoryPool& pool = gCoreMemoryPool);
        template<class IteratorType>
        requires IteratorInputAble<IteratorType, ElementType>
        constexpr Array(IteratorType first, IteratorType last, MemoryPool& pool = gCoreMemoryPool);
        constexpr Array(const Array& other);
        constexpr Array(const Array& other, MemoryPool& pool);
        constexpr Array(Array&& other) noexcept;
        constexpr Array(Array&& other, MemoryPool& pool) noexcept;
        constexpr Array(const std::initializer_list<ElementType>& initialzerList, MemoryPool& pool = gCoreMemoryPool);
        ~Array();

        constexpr Array& operator=(const Array& other);
        constexpr Array& operator=(Array&& other);
        constexpr Array& operator=(const std::initializer_list<ElementType>& initialzerList);

        constexpr void Clear();

        constexpr void Assign(size_t count, const ElementType& initializeElement);

        constexpr Iterator Insert(ConstIterator position, const ElementType& element);
        constexpr Iterator Insert(ConstIterator position, size_t count, const ElementType& element);
        template<class IteratorType>
        requires IteratorInputAble<IteratorType, ElementType>
        constexpr Iterator Insert(ConstIterator position, IteratorType first, IteratorType last);

        constexpr Iterator Delete(ConstIterator position);
        constexpr Iterator Delete(ConstIterator first, ConstIterator last);

        constexpr void InsertBack(const ElementType& element);

        constexpr void DeleteBack();

        constexpr bool IsEmpty() const;

        constexpr size_t GetSize() const;
        constexpr void SetSize(size_t size, const ElementType& initializeElement);

        constexpr size_t GetCapacity() const;
        constexpr void SetCapacity(size_t capacity);

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
        constexpr Iterator begin();

        constexpr Iterator GetEndIterator();
        constexpr Iterator end();

        constexpr ConstIterator GetBeginConstIterator() const;
        constexpr ConstIterator GetEndConstIterator() const;

        constexpr bool operator==(const Array& other) const;
        constexpr bool operator!=(const Array& other) const;

        constexpr static size_t DEFAULT_CAPACITY = 8u;

    private:
        MemoryPool& mPool;
        size_t mSize;
        size_t mCapacity;
        ElementType* mData;
    };

    /*
    *
    * ArrayConstIterator Implement
    *
    */

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType>::ArrayConstIterator()
        : mContainer(nullptr)
        , mIndex(0)
    { }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType>::ArrayConstIterator(Array<ElementType>& container, size_t startIndex)
        : mContainer(&container)
        , mIndex(startIndex)
    { }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType>::ArrayConstIterator(const ArrayConstIterator& other)
        : mContainer(other.mContainer)
        , mIndex(other.mIndex)
    { }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType>& ArrayConstIterator<ElementType>::operator=(const ArrayConstIterator& other)
    {
        mContainer = other.mContainer;
        mIndex = other.mIndex;

        return *this;
    }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType>& ArrayConstIterator<ElementType>::operator++()
    {
        ++mIndex;

        return *this;
    }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType> ArrayConstIterator<ElementType>::operator++(int)
    {
        ArrayConstIterator temp = *this;
        ++mIndex;

        return temp;
    }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType>& ArrayConstIterator<ElementType>::operator--()
    {
        --mIndex;

        return *this;
    }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType> ArrayConstIterator<ElementType>::operator--(int)
    {
        ArrayConstIterator temp = *this;
        --mIndex;

        return temp;
    }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType>& ArrayConstIterator<ElementType>::operator+=(size_t offset)
    {
        mIndex += offset;

        return *this;
    }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType> ArrayConstIterator<ElementType>::operator+(size_t offset)
    {
        mIndex += offset;
        ArrayConstIterator temp = *this;

        return temp;
    }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType>& ArrayConstIterator<ElementType>::operator-=(size_t offset)
    {
        mIndex -= offset;

        return *this;
    }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType> ArrayConstIterator<ElementType>::operator-(size_t offset)
    {
        mIndex -= offset;
        ArrayConstIterator temp = *this;

        return temp;
    }

    template<class ElementType>
    constexpr size_t ArrayConstIterator<ElementType>::operator-(const ArrayConstIterator& other)
    {
        return mIndex - other.mIndex;
    }

    template<class ElementType>
    constexpr const ElementType& ArrayConstIterator<ElementType>::operator*() const
    {
        assert(mContainer != nullptr);

        return (*mContainer)[mIndex];
    }

    template<class ElementType>
    constexpr const ElementType& ArrayConstIterator<ElementType>::operator[](size_t offset) const
    {
        assert(mContainer != nullptr);

        return (*mContainer)[mIndex + offset];
    }

    template<class ElementType>
    constexpr bool ArrayConstIterator<ElementType>::operator==(const ArrayConstIterator& other) const
    {
        return (mIndex == other.mIndex && mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr bool ArrayConstIterator<ElementType>::operator!=(const ArrayConstIterator& other) const
    {
        return (mIndex != other.mIndex || mContainer != other.mContainer);
    }

    template<class ElementType>
    constexpr bool ArrayConstIterator<ElementType>::operator<=(const ArrayConstIterator& other) const
    {
        return (mIndex <= other.mIndex && mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr bool ArrayConstIterator<ElementType>::operator<(const ArrayConstIterator& other) const
    {
        return (mIndex < other.mIndex&& mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr bool ArrayConstIterator<ElementType>::operator>=(const ArrayConstIterator& other) const
    {
        return (mIndex >= other.mIndex && mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr bool ArrayConstIterator<ElementType>::operator>(const ArrayConstIterator& other) const
    {
        return (mIndex > other.mIndex && mContainer == other.mContainer);
    }

    template<class ElementType>
    constexpr ArrayConstIterator<ElementType> operator+(size_t offset, ArrayConstIterator<ElementType> Iterator)
    {
        return Iterator += offset;
    }

    /*
    *
    * ArrayIterator Implement
    *
    */

    template<class ElementType>
    constexpr ArrayIterator<ElementType>::ArrayIterator()
        : Base()
    { }

    template<class ElementType>
    constexpr ArrayIterator<ElementType>::ArrayIterator(Array<ElementType>& container, size_t startIndex)
        : Base(container, startIndex)
    { }

    template<class ElementType>
    constexpr ArrayIterator<ElementType>::ArrayIterator(const ArrayIterator& other)
        : Base(other)
    { }

    template<class ElementType>
    constexpr ArrayIterator<ElementType>& ArrayIterator<ElementType>::operator=(const ArrayConstIterator<ElementType>& other)
    {
        Base::operator=(other);

        return *this;
    }

    template<class ElementType>
    constexpr ArrayIterator<ElementType>& ArrayIterator<ElementType>::operator++()
    {
        Base::operator++();

        return *this;
    }

    template<class ElementType>
    constexpr ArrayIterator<ElementType> ArrayIterator<ElementType>::operator++(int)
    {
        ArrayIterator Temp = *this;
        Base::operator++();

        return Temp;
    }

    template<class ElementType>
    constexpr ArrayIterator<ElementType>& ArrayIterator<ElementType>::operator--()
    {
        Base::operator--();

        return *this;
    }

    template<class ElementType>
    constexpr ArrayIterator<ElementType> ArrayIterator<ElementType>::operator--(int)
    {
        ArrayIterator Temp = *this;
        Base::operator--();

        return Temp;
    }

    template<class ElementType>
    constexpr ArrayIterator<ElementType>& ArrayIterator<ElementType>::operator+=(size_t offset)
    {
        Base::operator+=(offset);

        return *this;
    }

    template<class ElementType>
    constexpr ArrayIterator<ElementType> ArrayIterator<ElementType>::operator+(size_t offset)
    {
        ArrayIterator Temp = *this;

        return Temp += offset;
    }

    template<class ElementType>
    constexpr ArrayIterator<ElementType>& ArrayIterator<ElementType>::operator-=(size_t offset)
    {
        Base::operator-=(offset);

        return *this;
    }

    template<class ElementType>
    constexpr ArrayIterator<ElementType> ArrayIterator<ElementType>::operator-(size_t offset)
    {
        ArrayIterator Temp = *this;

        return Temp -= offset;

    }

    template<class ElementType>
    constexpr ElementType& ArrayIterator<ElementType>::operator*()
    {
        return const_cast<ElementType&>(Base::operator*());
    }

    template<class ElementType>
    constexpr ElementType& ArrayIterator<ElementType>::operator[](size_t offset)
    {
        return const_cast<ElementType&>(Base::operator[](offset));
    }

    template<class ElementType>
    constexpr ArrayIterator<ElementType> operator+(size_t offset, ArrayIterator<ElementType> Iterator)
    {
        return Iterator += offset;
    }

    /*
    *
    * Array Implement
    *
    */

    template<class ElementType>
    constexpr Array<ElementType>::Array() noexcept
        : mPool(gCoreMemoryPool)
        , mSize(0)
        , mCapacity(DEFAULT_CAPACITY)
        , mData(reinterpret_cast<ElementType*>(mPool.Allocate(sizeof(ElementType)* mCapacity)))
    {
    }

    template<class ElementType>
    constexpr Array<ElementType>::Array(MemoryPool& pool) noexcept
        : mPool(pool)
        , mSize(0)
        , mCapacity(DEFAULT_CAPACITY)
        , mData(reinterpret_cast<ElementType*>(mPool.Allocate(sizeof(ElementType)* mCapacity)))
    {
    }

    template<class ElementType>
    constexpr Array<ElementType>::Array(size_t count, const ElementType& value, MemoryPool& pool)
        : mPool(pool)
        , mSize(count)
        , mCapacity(mSize)
        , mData(reinterpret_cast<ElementType*>(mPool.Allocate(sizeof(ElementType)* mCapacity)))
    {
        for (size_t i = 0; i < count; ++i)
        {
            mData[i] = value;
        }
    }

    template<class ElementType>
    constexpr Array<ElementType>::Array(size_t count, MemoryPool& pool)
        : mPool(pool)
        , mSize(0)
        , mCapacity(count)
        , mData(reinterpret_cast<ElementType*>(mPool.Allocate(sizeof(ElementType)* mCapacity)))
    { }

    template<class ElementType>
    template<class IteratorType>
    requires IteratorInputAble<IteratorType, ElementType>
        constexpr Array<ElementType>::Array(IteratorType first, IteratorType last, MemoryPool& pool)
        : mPool(pool)
    {
        //GetIteratorDIstance(first, last)

        size_t count = 0;
        for (IteratorType iter = first; iter != last; ++iter, ++count);

        mSize = count;
        mCapacity = count;
        mData = reinterpret_cast<ElementType*>(mPool.Allocate(sizeof(ElementType) * count));

        size_t i = 0;
        for (IteratorType iterator = first; iterator != last; ++iterator, ++i)
        {
            mData[i] = *iterator;
        }
    }

    template<class ElementType>
    constexpr Array<ElementType>::Array(const Array& other)
        : Array(other, gCoreMemoryPool)
    {
    }

    template<class ElementType>
    constexpr Array<ElementType>::Array(const Array& other, MemoryPool& pool)
        : mPool(pool)
        , mSize(other.mSize)
        , mCapacity(other.mCapacity)
        , mData(reinterpret_cast<ElementType*>(mPool.Allocate(sizeof(ElementType)* mCapacity)))
    {
        if (mSize > 0)
        {
            Memory::Memcpy(mData, other.mData, sizeof(ElementType) * mSize);
        }
    }

    template<class ElementType>
    constexpr Array<ElementType>::Array(Array&& other) noexcept
        : Array(std::move(other), other.mPool)
    {
    }

    template<class ElementType>
    constexpr Array<ElementType>::Array(Array&& other, MemoryPool& pool) noexcept
        : mPool(pool)
        , mSize(other.mSize)
        , mCapacity(other.mCapacity)
        , mData(other.mData)
    {
        other.mCapacity = 0;
        other.mSize = 0;
        other.mData = nullptr;
    }

    template<class ElementType>
    constexpr Array<ElementType>::Array(const  std::initializer_list<ElementType>& initialzerList, MemoryPool& pool)
        : mPool(pool)
    {

        size_t count = 0;
        for (auto iterator = initialzerList.begin(); iterator != initialzerList.end(); ++iterator, ++count);

        mSize = count;
        mCapacity = count;
        mData = reinterpret_cast<ElementType*>(mPool.Allocate(sizeof(ElementType) * mCapacity));

        size_t i = 0;
        for (auto iterator = initialzerList.begin(); iterator != initialzerList.end(); ++iterator, ++i)
        {
            mData[i] = *iterator;
        }
    }

    template<class ElementType>
    Array<ElementType>::~Array()
    {
        if (mData != nullptr)
        {
            mPool.Deallocate(mData, mCapacity * sizeof(ElementType));
        }
    }

    template<class ElementType>
    constexpr Array<ElementType>& Array<ElementType>::operator=(const Array& other)
    {
        if (this != &other)
        {
            Clear();
            SetCapacity(other.mCapacity);
            mSize = other.mSize;

            Memory::Memcpy(mData, other.mData, sizeof(ElementType) * mSize);
        }

        return *this;
    }

    template<class ElementType>
    constexpr Array<ElementType>& Array<ElementType>::operator=(Array&& other)
    {
        if (this != &other)
        {
            size_t tempCapacity = mCapacity;
            size_t tempSize = mSize;
            ElementType* tempData = mData;
            MemoryPool* tempPool = mPool;

            mCapacity = other.mCapacity;
            mSize = other.mSize;
            mData = other.mData;
            mPool = other.mPool;

            other.mCapacity = tempCapacity;
            other.mSize = tempSize;
            other.mData = tempData;
            other.mPool = tempPool;
        }

        return *this;
    }

    template<class ElementType>
    constexpr Array<ElementType>& Array<ElementType>::operator=(const std::initializer_list<ElementType>& initialzerList)
    {
        size_t count = 0;
        for (auto iterator = initialzerList.begin(); iterator != initialzerList.end(); ++iterator, ++count);

        Clear();
        SetCapacity(count);

        size_t i = 0;
        for (auto iterator = initialzerList.begin(); iterator != initialzerList.end(); ++iterator, ++i)
        {
            mData[i] = *iterator;
        }
        mSize = count;

        return *this;
    }

    template<class ElementType>
    constexpr void Array<ElementType>::SetCapacity(size_t capacity)
    {
        assert(capacity <= GetMaxSize());

        if (capacity > mCapacity)
        {
            ElementType* temp = reinterpret_cast<ElementType*>(mPool.Allocate(sizeof(ElementType) * capacity));

            if (mData != nullptr)
            {
                Memory::Memcpy(temp, mData, mSize * sizeof(ElementType));
                mPool.Deallocate(mData, mCapacity * sizeof(ElementType));
            }

            mData = temp;
            mCapacity = capacity;
        }
    }

    template<class ElementType>
    constexpr void Array<ElementType>::SetSize(size_t size, const ElementType& initializeElement)
    {
        assert(size <= GetMaxSize());

        if (size > mCapacity)
        {
            SetCapacity(size);
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
    constexpr void Array<ElementType>::Clear()
    {
        mSize = 0;
    }

    template<class ElementType>
    constexpr void Array<ElementType>::Assign(size_t count, const ElementType& initializeElement)
    {
        Clear();
        SetSize(count, initializeElement);
    }

    template<class ElementType>
    constexpr Array<ElementType>::Iterator Array<ElementType>::Insert(ConstIterator position, const ElementType& element)
    {
        size_t index = position.mIndex;

        assert(index >= 0);
        assert(index <= mSize);

        size_t newMaxSize = mCapacity;

        if (mSize + 1 > newMaxSize)
        {
            newMaxSize <<= 1;
        }

        SetCapacity(newMaxSize);

        Memory::Memmove(mData + index + 1, mData + index, sizeof(ElementType) * (mSize - index));

        mSize += 1;
        mData[index] = element;

        return Iterator(*this, index);
    }

    template<class ElementType>
    constexpr Array<ElementType>::Iterator Array<ElementType>::Insert(ConstIterator position, size_t count, const ElementType& element)
    {
        size_t index = position.mIndex;

        assert(index >= 0);
        assert(index <= mSize);

        size_t newMaxSize = mCapacity;

        while (mSize + count > newMaxSize)
        {
            newMaxSize <<= 1;
        }

        SetCapacity(newMaxSize);

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
        constexpr Array<ElementType>::Iterator Array<ElementType>::Insert(ConstIterator position, IteratorType first, IteratorType last)
    {
        size_t count = 0;
        size_t index = position.mIndex;

        assert(index >= 0);
        assert(index <= mSize);

        size_t newMaxSize = mCapacity;

        for (IteratorType iterator = first; iterator != last; ++iterator, ++count);

        while (mSize + count > newMaxSize)
        {
            newMaxSize <<= 1;
        }

        SetCapacity(newMaxSize);

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
    constexpr Array<ElementType>::Iterator Array<ElementType>::Delete(ConstIterator position)
    {
        size_t index = position.mIndex;

        assert(index >= 0);
        assert(index < mSize);

        Memory::Memmove(mData + index, mData + index + 1, sizeof(ElementType) * (mSize - index - 1));


        mSize -= 1;

        return Iterator(*this, index);
    }

    template<class ElementType>
    constexpr Array<ElementType>::Iterator Array<ElementType>::Delete(ConstIterator first, ConstIterator last)
    {
        size_t count = 0;
        size_t index = first.mIndex;

        assert(first.mIndex >= 0);
        assert(last.mIndex < mSize);
        assert(first <= last);

        for (auto iterator = first; iterator != last; ++iterator, ++count);

        Memory::Memmove(mData + index, mData + index + count, sizeof(ElementType) * (mSize - index - count));

        mSize -= count;

        return Iterator(*this, index);
    }

    template<class ElementType>
    constexpr void Array<ElementType>::InsertBack(const ElementType& element)
    {
        size_t newMaxSize = mCapacity;

        if (mSize + 1 > newMaxSize)
        {
            newMaxSize <<= 1;
        }

        SetCapacity(newMaxSize);

        mData[mSize] = element;
        mSize++;
    }

    template<class ElementType>
    constexpr void Array<ElementType>::DeleteBack()
    {
        --mSize;
    }

    template<class ElementType>
    constexpr bool Array<ElementType>::IsEmpty() const
    {
        return (mSize == 0);
    }

    template<class ElementType>
    constexpr size_t Array<ElementType>::GetSize() const
    {
        return mSize;
    }

    template<class ElementType>
    constexpr size_t Array<ElementType>::GetCapacity() const
    {
        return mCapacity;
    }

    template<class ElementType>
    constexpr size_t Array<ElementType>::GetMaxSize() const
    {
        return mPool.GetFreeMemorySize() / sizeof(ElementType);
    }

    template<class ElementType>
    constexpr ElementType& Array<ElementType>::operator[](size_t pos)
    {
        return *(mData + pos);
    }

    template<class ElementType>
    constexpr const ElementType& Array<ElementType>::operator[](size_t pos) const
    {
        return *(mData + pos);
    }

    template<class ElementType>
    constexpr ElementType& Array<ElementType>::GetFront()
    {
        return *mData;
    }

    template<class ElementType>
    constexpr const ElementType& Array<ElementType>::GetFront() const
    {
        return *mData;
    }

    template<class ElementType>
    constexpr ElementType& Array<ElementType>::GetBack()
    {
        return *(mData + mSize - 1);
    }

    template<class ElementType>
    constexpr const ElementType& Array<ElementType>::GetBack() const
    {
        return *(mData + mSize - 1);
    }

    template<class ElementType>
    constexpr ElementType* Array<ElementType>::GetData() noexcept
    {
        return mData;
    }

    template<class ElementType>
    constexpr const ElementType* Array<ElementType>::GetData() const noexcept
    {
        return mData;
    }

    template<class ElementType>
    constexpr Array<ElementType>::Iterator Array<ElementType>::GetBeginIterator()
    {
        return Iterator(*this, 0);
    }

    template<class ElementType>
    constexpr Array<ElementType>::Iterator Array<ElementType>::begin()
    {
        return Iterator(*this, 0);
    }

    template<class ElementType>
    constexpr Array<ElementType>::Iterator Array<ElementType>::GetEndIterator()
    {
        return Iterator(*this, mSize);
    }

    template<class ElementType>
    constexpr Array<ElementType>::Iterator Array<ElementType>::end()
    {
        return Iterator(*this, mSize);
    }

    template<class ElementType>
    constexpr Array<ElementType>::ConstIterator Array<ElementType>::GetBeginConstIterator() const
    {
        return ConstIterator(*this, 0);
    }

    template<class ElementType>
    constexpr Array<ElementType>::ConstIterator Array<ElementType>::GetEndConstIterator() const
    {
        return ConstIterator(*this, mSize);
    }

    template<class ElementType>
    constexpr bool  Array<ElementType>::operator==(const Array<ElementType>& other) const
    {
        return mData == other.mData;
    }

    template<class ElementType>
    constexpr bool  Array<ElementType>::operator!=(const Array<ElementType>& other) const
    {
        return mData != other.mData;
    }
}