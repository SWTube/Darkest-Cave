/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module cave.Core.Containers.Array;

import cave.Core.Memory.Memory;

export namespace cave
{
    class Array;

    class ArrayConstIterator
    {
    public:
        friend class Array;

        constexpr ArrayConstIterator();
        constexpr ArrayConstIterator(const Array& container, size_t startIndex);
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

        constexpr const void* operator*() const;
        constexpr const void* operator[](size_t offset) const;

        constexpr bool operator==(const ArrayConstIterator& other) const;
        constexpr bool operator!=(const ArrayConstIterator& other) const;
        constexpr bool operator<=(const ArrayConstIterator& other) const;
        constexpr bool operator<(const ArrayConstIterator& other) const;
        constexpr bool operator>=(const ArrayConstIterator& other) const;
        constexpr bool operator>(const ArrayConstIterator& other) const;

    private:
        const Array* mContainer;
        size_t mIndex;
    };

    class ArrayIterator final : public ArrayConstIterator
    {
    public:
        friend class Array;

        using Base = ArrayConstIterator;

        constexpr ArrayIterator();
        constexpr ArrayIterator(Array& container, size_t startIndex);
        constexpr ArrayIterator(const ArrayIterator& other);

        constexpr ArrayIterator& operator=(const ArrayConstIterator& other);

        constexpr ArrayIterator& operator++();
        constexpr ArrayIterator operator++(int);

        constexpr ArrayIterator& operator--();
        constexpr ArrayIterator operator--(int);

        constexpr ArrayIterator& operator+=(size_t offset);
        constexpr ArrayIterator operator+(size_t offset);

        constexpr ArrayIterator& operator-=(size_t offset);
        constexpr ArrayIterator operator-(size_t offset);

        constexpr void* operator*();
        constexpr void* operator[](size_t offset);
    };

    class Array final
    {
    public:
        using ConstIterator = ArrayConstIterator;
        using Iterator = ArrayIterator;

        explicit Array() noexcept;
        explicit Array(MemoryPool& pool) noexcept;
        Array(size_t count, void* item);
        Array(size_t count, void* item, MemoryPool& pool);
        Array(size_t count);
        Array(size_t count, MemoryPool& pool);
        Array(const Array& other);
        Array(const Array& other, MemoryPool& pool);
        Array(Array&& other) noexcept;
        ~Array();

        constexpr Array& operator=(const Array& other);
        constexpr Array& operator=(Array&& other);

        constexpr void Clear();

        constexpr void Swap(Array& other);

        Iterator Insert(ConstIterator position, void* item);
        Iterator Insert(ConstIterator position, size_t count, void* item);

        Iterator Delete(ConstIterator position);
        Iterator Delete(ConstIterator first, ConstIterator last);

        constexpr void InsertBack(void* item);

        constexpr void DeleteBack();

        constexpr bool IsEmpty() const;

        constexpr size_t GetSize() const;
        constexpr void SetSize(size_t size, void* item);

        constexpr size_t GetCapacity() const;
        constexpr void SetCapacity(size_t capacity);

        constexpr size_t GetMaxSize() const;

        // Element Access
        constexpr void* operator[](size_t pos);
        constexpr const void* operator[](size_t pos) const;

        constexpr void* GetFront();
        constexpr const void* GetFront() const;

        constexpr void* GetBack();
        constexpr const void* GetBack() const;

        constexpr void** GetData() noexcept;
        constexpr const void** GetData() const noexcept;

        // Iterators
        constexpr Iterator begin();
        constexpr Iterator end();

        ConstIterator cbegin() const;
        ConstIterator cend() const;

        constexpr Iterator GetBeginIterator();
        constexpr Iterator GetEndIterator();
        
        ConstIterator GetBeginConstIterator() const;
        ConstIterator GetEndConstIterator() const;

        constexpr bool operator==(const Array& other) const;
        constexpr bool operator!=(const Array& other) const;

        constexpr static size_t DEFAULT_CAPACITY = 8u;

    private:
        MemoryPool* mPool;
        size_t mSize;
        size_t mCapacity;
        void** mData;
    };

    /*
    *
    * ArrayConstIterator Implement
    *
    */

    constexpr ArrayConstIterator::ArrayConstIterator()
        : mContainer(nullptr)
        , mIndex(0)
    { }

    constexpr ArrayConstIterator::ArrayConstIterator(const Array& container, size_t startIndex)
        : mContainer(&container)
        , mIndex(startIndex)
    { }

    constexpr ArrayConstIterator::ArrayConstIterator(const ArrayConstIterator& other)
        : mContainer(other.mContainer)
        , mIndex(other.mIndex)
    { }

    constexpr ArrayConstIterator& ArrayConstIterator::operator=(const ArrayConstIterator& other)
    {
        mContainer = other.mContainer;
        mIndex = other.mIndex;

        return *this;
    }

    constexpr ArrayConstIterator& ArrayConstIterator::operator++()
    {
        ++mIndex;

        return *this;
    }

    constexpr ArrayConstIterator ArrayConstIterator::operator++(int)
    {
        ArrayConstIterator temp = *this;
        ++mIndex;

        return temp;
    }
    
    constexpr ArrayConstIterator& ArrayConstIterator::operator--()
    {
        --mIndex;

        return *this;
    }

    constexpr ArrayConstIterator ArrayConstIterator::operator--(int)
    {
        ArrayConstIterator temp = *this;
        --mIndex;

        return temp;
    }

    constexpr ArrayConstIterator& ArrayConstIterator::operator+=(size_t offset)
    {
        mIndex += offset;

        return *this;
    }

    constexpr ArrayConstIterator ArrayConstIterator::operator+(size_t offset)
    {
        mIndex += offset;
        ArrayConstIterator temp = *this;

        return temp;
    }

    constexpr ArrayConstIterator& ArrayConstIterator::operator-=(size_t offset)
    {
        mIndex -= offset;

        return *this;
    }

    constexpr ArrayConstIterator ArrayConstIterator::operator-(size_t offset)
    {
        mIndex -= offset;
        ArrayConstIterator temp = *this;

        return temp;
    }

    constexpr size_t ArrayConstIterator::operator-(const ArrayConstIterator& other)
    {
        return mIndex - other.mIndex;
    }

    constexpr const void* ArrayConstIterator::operator*() const
    {
        assert(mContainer != nullptr);

        return (*mContainer)[mIndex];
    }

    constexpr const void* ArrayConstIterator::operator[](size_t offset) const
    {
        assert(mContainer != nullptr);

        return (*mContainer)[mIndex + offset];
    }

    constexpr bool ArrayConstIterator::operator==(const ArrayConstIterator& other) const
    {
        return (mIndex == other.mIndex && mContainer == other.mContainer);
    }

    constexpr bool ArrayConstIterator::operator!=(const ArrayConstIterator& other) const
    {
        return (mIndex != other.mIndex || mContainer != other.mContainer);
    }

    constexpr bool ArrayConstIterator::operator<=(const ArrayConstIterator& other) const
    {
        return (mIndex <= other.mIndex && mContainer == other.mContainer);
    }

    constexpr bool ArrayConstIterator::operator<(const ArrayConstIterator& other) const
    {
        return (mIndex < other.mIndex&& mContainer == other.mContainer);
    }

    constexpr bool ArrayConstIterator::operator>=(const ArrayConstIterator& other) const
    {
        return (mIndex >= other.mIndex && mContainer == other.mContainer);
    }

    constexpr bool ArrayConstIterator::operator>(const ArrayConstIterator& other) const
    {
        return (mIndex > other.mIndex && mContainer == other.mContainer);
    }

    constexpr ArrayConstIterator operator+(size_t offset, ArrayConstIterator Iterator)
    {
        return Iterator += offset;
    }

    /*
    *
    * ArrayIterator Implement
    *
    */

    constexpr ArrayIterator::ArrayIterator()
        : Base()
    { }

    constexpr ArrayIterator::ArrayIterator(Array& container, size_t startIndex)
        : Base(container, startIndex)
    { }
    
    constexpr ArrayIterator::ArrayIterator(const ArrayIterator& other)
        : Base(other)
    { }

    constexpr ArrayIterator& ArrayIterator::operator=(const ArrayConstIterator& other)
    {
        Base::operator=(other);

        return *this;
    }
    
    constexpr ArrayIterator& ArrayIterator::operator++()
    {
        Base::operator++();

        return *this;
    }
    
    constexpr ArrayIterator ArrayIterator::operator++(int)
    {
        ArrayIterator Temp = *this;
        Base::operator++();

        return Temp;
    }
    
    constexpr ArrayIterator& ArrayIterator::operator--()
    {
        Base::operator--();

        return *this;
    }
    
    constexpr ArrayIterator ArrayIterator::operator--(int)
    {
        ArrayIterator Temp = *this;
        Base::operator--();

        return Temp;
    }
    
    constexpr ArrayIterator& ArrayIterator::operator+=(size_t offset)
    {
        Base::operator+=(offset);

        return *this;
    }
    
    constexpr ArrayIterator ArrayIterator::operator+(size_t offset)
    {
        ArrayIterator Temp = *this;

        return Temp += offset;
    }
    
    constexpr ArrayIterator& ArrayIterator::operator-=(size_t offset)
    {
        Base::operator-=(offset);

        return *this;
    }
    
    constexpr ArrayIterator ArrayIterator::operator-(size_t offset)
    {
        ArrayIterator Temp = *this;

        return Temp -= offset;

    }
    
    constexpr void* ArrayIterator::operator*()
    {
        return const_cast<void*>(Base::operator*());
    }
    
    constexpr  void* ArrayIterator::operator[](size_t offset)
    {
        return const_cast<void*>(Base::operator[](offset));
    }

    constexpr ArrayIterator operator+(size_t offset, ArrayIterator Iterator)
    {
        return Iterator += offset;
    }

    /*
    *
    * Array Implement
    *
    */

    
    Array::Array() noexcept
        : Array(gCoreMemoryPool)
    { }

    Array::Array(MemoryPool& pool) noexcept
        : mPool(&pool)
        , mSize(0)
        , mCapacity(DEFAULT_CAPACITY)
        , mData(reinterpret_cast<void**>(mPool->Allocate(sizeof(void*)* mCapacity)))
    { }

    Array::Array(size_t count, void* item)
        : Array(count, item, gCoreMemoryPool)
    { }

    Array::Array(size_t count, void* item, MemoryPool& pool)
        : mPool(&pool)
        , mSize(count)
        , mCapacity(mSize)
        , mData(reinterpret_cast<void**>(mPool->Allocate(sizeof(void*)* mCapacity)))
    {
        for (size_t i = 0; i < count; ++i)
        {
            mData[i] = item;
        }
    }

    Array::Array(size_t count)
        : Array(count, gCoreMemoryPool)
    { }
  
    Array::Array(size_t count, MemoryPool& pool)
        : mPool(&pool)
        , mSize(0)
        , mCapacity(count)
        , mData(reinterpret_cast<void**>(mPool->Allocate(sizeof(void*)* mCapacity)))
    { }

    Array::Array(const Array& other)
        : Array(other, gCoreMemoryPool)
    { }

    Array::Array(const Array& other, MemoryPool& pool)
        : mPool(&pool)
        , mSize(other.mSize)
        , mCapacity(other.mCapacity)
        , mData(reinterpret_cast<void**>(mPool->Allocate(sizeof(void*)* mCapacity)))
    {
        if (mSize > 0)
        {
            Memory::Memcpy(mData, other.mData, sizeof(void*) * mSize);
        }
    }

    Array::Array(Array&& other) noexcept
        : mPool(other.mPool)
        , mSize(other.mSize)
        , mCapacity(other.mCapacity)
        , mData(other.mData)
    {
        other.mCapacity = 0;
        other.mSize = 0;
        other.mData = nullptr;
    }

    Array::~Array()
    {
        if (mData != nullptr)
        {
            mPool->Deallocate(mData, mCapacity * sizeof(void*));
        }
    }

    constexpr Array& Array::operator=(const Array& other)
    {
        if (this != &other)
        {
            Clear();
            SetCapacity(other.mCapacity);
            mSize = other.mSize;

            Memory::Memcpy(mData, other.mData, sizeof(void*) * mSize);
        }

        return *this;
    }

    
    constexpr Array& Array::operator=(Array&& other)
    {
        if (this != &other)
        {
            Swap(other);
        }

        return *this;
    }

    constexpr void Array::Clear()
    {
        mSize = 0;
    }

    constexpr void Array::Swap(Array& other)
    {
        size_t tempCapacity = mCapacity;
        size_t tempSize = mSize;
        void** tempData = mData;
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
    
    Array::Iterator Array::Insert(ConstIterator position, void* item)
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

        Memory::Memmove(mData + index + 1, mData + index, sizeof(void*) * (mSize - index));

        mSize += 1;
        mData[index] = item;

        return Iterator(*this, index);
    }

    
    Array::Iterator Array::Insert(ConstIterator position, size_t count, void* item)
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

        Memory::Memmove(mData + index + count, mData + index, sizeof(void*) * (mSize - index));

        mSize += count;

        for (size_t i = 0; i < count; ++i)
        {
            mData[index + i] = item;
        }

        return Iterator(*this, index);
    }

    Array::Iterator Array::Delete(ConstIterator position)
    {
        size_t index = position.mIndex;

        assert(index >= 0);
        assert(index < mSize);

        Memory::Memmove(mData + index, mData + index + 1, sizeof(void*) * (mSize - index - 1));


        mSize -= 1;

        return Iterator(*this, index);
    }

    
    Array::Iterator Array::Delete(ConstIterator first, ConstIterator last)
    {
        size_t count = 0;
        size_t index = first.mIndex;

        assert(first.mIndex >= 0);
        assert(last.mIndex < mSize);
        assert(first <= last);

        for (auto iterator = first; iterator != last; ++iterator, ++count);

        Memory::Memmove(mData + index, mData + index + count, sizeof(void*) * (mSize - index - count));

        mSize -= count;

        return Iterator(*this, index);
    }

    
    constexpr void Array::InsertBack(void* item)
    {
        size_t newMaxSize = mCapacity;

        if (mSize + 1 > newMaxSize)
        {
            newMaxSize <<= 1;
        }

        SetCapacity(newMaxSize);

        mData[mSize] = item;
        mSize++;
    }

    
    constexpr void Array::DeleteBack()
    {
        --mSize;
    }

    
    constexpr bool Array::IsEmpty() const
    {
        return (mSize == 0);
    }

    constexpr size_t Array::GetSize() const
    {
        return mSize;
    }

    constexpr void Array::SetSize(size_t size, void* item)
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
                mData[i] = item;
            }
        }

        mSize = size;
    }
    
    constexpr size_t Array::GetCapacity() const
    {
        return mCapacity;
    }

    constexpr void Array::SetCapacity(size_t capacity)
    {
        assert(capacity <= GetMaxSize());

        if (capacity > mCapacity)
        {
            void** temp = reinterpret_cast<void**>(mPool->Allocate(sizeof(void*) * capacity));

            if (mData != nullptr)
            {
                Memory::Memcpy(temp, mData, mSize * sizeof(void*));
                mPool->Deallocate(mData, mCapacity * sizeof(void*));
            }

            mData = temp;
            mCapacity = capacity;
        }
    }

    constexpr size_t Array::GetMaxSize() const
    {
        return mPool->GetFreeMemorySize() / sizeof(void*);
    }
    
    constexpr void* Array::operator[](size_t pos)
    {
        return *(mData + pos);
    }

    
    constexpr const void* Array::operator[](size_t pos) const
    {
        return *(mData + pos);
    }

    
    constexpr void* Array::GetFront()
    {
        return *mData;
    }

    
    constexpr const void* Array::GetFront() const
    {
        return *mData;
    }

    
    constexpr void* Array::GetBack()
    {
        return *(mData + mSize - 1);
    }

    
    constexpr const void* Array::GetBack() const
    {
        return *(mData + mSize - 1);
    }

    
    constexpr void** Array::GetData() noexcept
    {
        return mData;
    }

    
    constexpr const void** Array::GetData() const noexcept
    {
        return const_cast<const void**>(mData);
    }

    constexpr Array::Iterator Array::begin()
    {
        return Iterator(*this, 0);
    }

    constexpr Array::Iterator Array::end()
    {
        return Iterator(*this, mSize);
    }

    Array::ConstIterator Array::cbegin() const
    {
        return ConstIterator(*this, 0);
    }

    Array::ConstIterator Array::cend() const
    {
        return ConstIterator(*this, mSize);
    }
    
    constexpr Array::Iterator Array::GetBeginIterator()
    {
        return Iterator(*this, 0);
    }

    constexpr Array::Iterator Array::GetEndIterator()
    {
        return Iterator(*this, mSize);
    }
    
    Array::ConstIterator Array::GetBeginConstIterator() const
    {
        return ConstIterator(*this, 0);
    }

    Array::ConstIterator Array::GetEndConstIterator() const
    {
        return ConstIterator(*this, mSize);
    }

    constexpr bool  Array::operator==(const Array& other) const
    {
        return mData == other.mData;
    }

    constexpr bool  Array::operator!=(const Array& other) const
    {
        return mData != other.mData;
    }
}