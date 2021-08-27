/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#ifdef CAVE_BUILD_DEBUG

#include <vector>
#include "Utils/Crt.h"
#include "Debug/Log.h"

#endif

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

        constexpr const void* operator*() const;

        constexpr const void* operator[](size_t offset) const;

        constexpr const void** operator->() const;

        constexpr size_t operator-(const ArrayConstIterator& other);

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
        constexpr const void* operator*() const;

        constexpr void* operator[](size_t offset);
        constexpr const void* operator[](size_t offset) const;

        constexpr void** operator->();
        constexpr const void** operator->() const;
    };

    class Array final
    {
    public:
        using ConstIterator = ArrayConstIterator;
        using Iterator = ArrayIterator;

        explicit Array() noexcept;
        explicit Array(MemoryPool& pool) noexcept;
        Array(void* item);
        Array(void* item, MemoryPool& pool);
        Array(size_t capacity);
        Array(size_t capacity, MemoryPool& pool);
        Array(const Array& other);
        Array(const Array& other, MemoryPool& pool);
        Array(Array&& other) noexcept;  
        ~Array();

        constexpr Array& operator=(const Array& other);
        constexpr Array& operator=(Array&& other);

        constexpr void Clear();

        constexpr void Swap(Array& other);

        Iterator Insert(ConstIterator position, void* item);

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

        constexpr ConstIterator begin() const;
        constexpr ConstIterator end() const;

        constexpr Iterator GetBeginIterator();
        constexpr Iterator GetEndIterator();
        
        constexpr ConstIterator GetBeginConstIterator() const;
        constexpr ConstIterator GetEndConstIterator() const;

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
        ArrayConstIterator temp = *this;
        temp += offset;

        return temp;
    }

    constexpr ArrayConstIterator& ArrayConstIterator::operator-=(size_t offset)
    {
        mIndex -= offset;

        return *this;
    }

    constexpr ArrayConstIterator ArrayConstIterator::operator-(size_t offset)
    {
        ArrayConstIterator temp = *this;
        temp -= offset;

        return temp;
    }

    constexpr size_t ArrayConstIterator::operator-(const ArrayConstIterator& other)
    {
        return mIndex - other.mIndex;
    }

    constexpr const void* ArrayConstIterator::operator*() const
    {
        assert(mContainer != nullptr);

        return mContainer->GetData()[mIndex];
    }

    constexpr const void* ArrayConstIterator::operator[](size_t offset) const
    {
        assert(mContainer != nullptr);

        return mContainer->GetData()[mIndex + offset];
    }

    constexpr const void** ArrayConstIterator::operator->() const
    {
        assert(mContainer != nullptr);

        return mContainer->GetData() + mIndex;
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
    
    constexpr const void* ArrayIterator::operator*() const
    {
        return Base::operator*();
    }

    constexpr void* ArrayIterator::operator[](size_t offset)
    {
        return const_cast<void*>(Base::operator[](offset));
    }

    constexpr const void* ArrayIterator::operator[](size_t offset) const
    {
        return Base::operator[](offset);
    }

    constexpr void** ArrayIterator::operator->()
    {
        return const_cast<void**>(Base::operator->());
    }

    constexpr const void** ArrayIterator::operator->() const
    {
        return Base::operator->();
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

    Array::Array(void* item)
        : Array(item, gCoreMemoryPool)
    { }

    Array::Array(void* item, MemoryPool& pool)
        : mPool(&pool)
        , mSize(1)
        , mCapacity(DEFAULT_CAPACITY)
        , mData(reinterpret_cast<void**>(mPool->Allocate(sizeof(void*)* mCapacity)))
    {
        mData[0] = item;
    }

    Array::Array(size_t capacity)
        : Array(capacity, gCoreMemoryPool)
    { }
  
    Array::Array(size_t capacity, MemoryPool& pool)
        : mPool(&pool)
        , mSize(0)
        , mCapacity(capacity)
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

    Array::Iterator Array::Delete(ConstIterator position)
    {
        size_t index = position.mIndex;

        assert(index < mSize);

        Memory::Memmove(mData + index, mData + index + 1, sizeof(void*) * (mSize - index - 1));


        mSize -= 1;

        return Iterator(*this, index);
    }

    
    Array::Iterator Array::Delete(ConstIterator first, ConstIterator last)
    {
        size_t count = 0;
        size_t index = first.mIndex;

        assert(last.mIndex < mSize);
        assert(first <= last);

        for (auto iterator = first; iterator != last; ++iterator, ++count);

        Memory::Memmove(mData + index, mData + index + count, sizeof(void*) * (mSize - index - count));

        mSize -= count;

        return Iterator(*this, index);
    }

    
    constexpr void Array::InsertBack(void* item)
    {
        assert(GetMaxSize() > 0);

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
        assert(!IsEmpty());

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
            for (size_t i = mSize; i < size; ++i)
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
        assert(!IsEmpty());

        return *mData;
    }

    
    constexpr const void* Array::GetFront() const
    {
        assert(!IsEmpty());

        return *mData;
    }

    
    constexpr void* Array::GetBack()
    {
        assert(!IsEmpty());

        return *(mData + mSize - 1);
    }

    
    constexpr const void* Array::GetBack() const
    {
        assert(!IsEmpty());

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

    constexpr Array::ConstIterator Array::begin() const
    {
        return ConstIterator(*this, 0);
    }

    constexpr Array::ConstIterator Array::end() const
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
    
    constexpr Array::ConstIterator Array::GetBeginConstIterator() const
    {
        return ConstIterator(*this, 0);
    }

    constexpr Array::ConstIterator Array::GetEndConstIterator() const
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
    
#ifdef CAVE_BUILD_DEBUG
    namespace ArrayTest
    {
        constexpr size_t DEFAULT_ARRAY_SIZE = 10;
        constexpr uint8_t TEST_ALL          = 0b11111111;
        constexpr uint8_t TEST_CONSTRUCTOR  = 0b00000001;
        constexpr uint8_t TEST_ASSIGN       = 0b00000010;
        constexpr uint8_t TEST_ACCESS       = 0b00000100;
        constexpr uint8_t TEST_INSERT       = 0b00001000;
        constexpr uint8_t TEST_MOVE         = 0b00001000;
        constexpr uint8_t TEST_DELETE       = 0b00010000;
        constexpr uint8_t TEST_COMPARE      = 0b00010000;
        constexpr uint8_t TEST_ITERATOR     = 0b00100000;
        constexpr uint8_t TEST_OTHER        = 0b01000000;

        int32_t*** insertTable;
        size_t** insertTableCount;

        size_t** deleteTable;

        int32_t* accessTable;

        std::vector<int32_t> stdVector;

        void Test(uint8_t constIteratorTestCase, size_t constIteratorTestCount, uint8_t iteratorTestCase, size_t iteratorTestCount, uint8_t containerTestCase, size_t containerTestCount);
        void ConstIteratorTest(uint8_t constIteratorTestCase, const Array& caveArray);
        void IteratorTest(uint8_t iteratorTestCase, Array& caveArray);
        void ContainerTest(uint8_t containerTestCase, Array& caveArray);
        void PrintArray(const Array& arr);
        void PrintArraySimple(const Array& arr);
        const int32_t Toint32_t(const void* item);

        namespace ConstIterator
        {
            void Constructor(const Array& caveArray);
            void AssignOperator(const Array& caveArray);
            void AccessOperator(const Array& caveArray);
            void MoveOperator(const Array& caveArray);
            void CompareOperator(const Array& caveArray);

            void Constructor(const Array& caveArray)
            {
                ArrayConstIterator defaultConstructor;
                LOGD(eLogChannel::CORE_CONTAINER, "ArrayConstIterator() Success");

                ArrayConstIterator arrayConstructor(caveArray, 0);
                LOGD(eLogChannel::CORE_CONTAINER, "ArrayConstIterator(arr, 0) Success");

                ArrayConstIterator copyConstructor(defaultConstructor);
                LOGD(eLogChannel::CORE_CONTAINER, "ArrayConstIterator(ArrayConstIterator) Success");
            }

            void AssignOperator(const Array& caveArray)
            {
                size_t offset = rand() % caveArray.GetSize();

                ArrayConstIterator iterator;
                ArrayConstIterator otherIterator(caveArray, offset);

                iterator = otherIterator;
                LOGDF(eLogChannel::CORE_CONTAINER, "ArrayConstIterator = ArrayConstIterator Success");
            }

            void AccessOperator(const Array& caveArray)
            {
                size_t offset = rand() % caveArray.GetSize();

                auto caveIterator = caveArray.GetBeginConstIterator();
                auto stdIterator = stdVector.cbegin();

                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(caveIterator[offset]) == stdIterator[offset]);
            }

            void MoveOperator(const Array& caveArray)
            {
                size_t offset = rand() % (caveArray.GetSize() - 2);
                auto caveIterator = caveArray.GetBeginConstIterator() + offset;
                auto stdIterator = stdVector.cbegin() + offset;

                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*++caveIterator) == *++stdIterator);
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*caveIterator++) == *stdIterator++);
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*--caveIterator) == *--stdIterator);
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*caveIterator--) == *stdIterator--);
                assert(Toint32_t(*caveIterator) == *stdIterator);

                caveIterator = caveArray.GetBeginConstIterator();
                stdIterator = stdVector.cbegin();

                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*(caveIterator + offset)) == *(stdIterator + offset));
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*(caveIterator += offset)) == *(stdIterator += offset));
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*(caveIterator - offset)) == *(stdIterator - offset));
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*(caveIterator -= offset)) == *(stdIterator -= offset));
                assert(Toint32_t(*caveIterator) == *stdIterator);
            }

            void CompareOperator(const Array& caveArray)
            {
                size_t leftOffset = rand() % caveArray.GetSize();
                size_t rightOffset = rand() % caveArray.GetSize();

                auto caveLeftIterator = caveArray.GetBeginConstIterator() + leftOffset;
                auto caveRightIterator = caveArray.GetBeginConstIterator() + rightOffset;
                auto stdLeftIterator = stdVector.cbegin() + leftOffset;
                auto stdRightIterator = stdVector.cbegin() + rightOffset;

                assert((caveLeftIterator == caveRightIterator) == (stdLeftIterator == stdRightIterator));
                assert((caveLeftIterator != caveRightIterator) == (stdLeftIterator != stdRightIterator));
                assert((caveLeftIterator <= caveRightIterator) == (stdLeftIterator <= stdRightIterator));
                assert((caveLeftIterator >= caveRightIterator) == (stdLeftIterator >= stdRightIterator));
                assert((caveLeftIterator < caveRightIterator) == (stdLeftIterator < stdRightIterator));
                assert((caveLeftIterator > caveRightIterator) == (stdLeftIterator > stdRightIterator));
                assert((caveLeftIterator - caveRightIterator) == (stdLeftIterator - stdRightIterator));
            }
        }

        namespace Iterator
        {
            void Constructor(Array& caveArray);
            void AssignOperator(Array& caveArray);
            void AccessOperator(Array& caveArray);
            void MoveOperator(Array& caveArray);
            

            void Constructor(Array& caveArray)
            {
                ArrayIterator defaultConstructor;
                LOGD(eLogChannel::CORE_CONTAINER, "ArrayIterator() Success");

                ArrayIterator arrayConstructor(caveArray, 0);
                LOGD(eLogChannel::CORE_CONTAINER, "ArrayIterator(arr, 0) Success");

                ArrayIterator copyConstructor(defaultConstructor);
                LOGD(eLogChannel::CORE_CONTAINER, "ArrayIterator(ArrayIterator) Success");
            }

            void AssignOperator(Array& caveArray)
            {
                size_t offset = rand() % caveArray.GetSize();

                ArrayIterator iterator;
                ArrayIterator otherIterator(caveArray, offset);

                iterator = otherIterator;
                LOGDF(eLogChannel::CORE_CONTAINER, "ArrayIterator = ArrayIterator Success");
            }

            void AccessOperator(Array& caveArray)
            {
                size_t offset = rand() % caveArray.GetSize();

                auto caveIterator = caveArray.GetBeginIterator();
                auto stdIterator = stdVector.begin();

                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(caveIterator[offset]) == stdIterator[offset]);
            }

            void MoveOperator(Array& caveArray)
            {
                size_t offset = rand() % (caveArray.GetSize() - 2);
                auto caveIterator = caveArray.GetBeginIterator() + offset;
                auto stdIterator = stdVector.begin() + offset;

                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*++caveIterator) == *++stdIterator);
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*caveIterator++) == *stdIterator++);
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*--caveIterator) == *--stdIterator);
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*caveIterator--) == *stdIterator--);
                assert(Toint32_t(*caveIterator) == *stdIterator);

                caveIterator = caveArray.GetBeginIterator();
                stdIterator = stdVector.begin();

                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*(caveIterator + offset)) == *(stdIterator + offset));
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*(caveIterator += offset)) == *(stdIterator += offset));
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*(caveIterator - offset)) == *(stdIterator - offset));
                assert(Toint32_t(*caveIterator) == *stdIterator);
                assert(Toint32_t(*(caveIterator -= offset)) == *(stdIterator -= offset));
                assert(Toint32_t(*caveIterator) == *stdIterator);
            }
        }

        namespace Container
        {
            void Constructor();
            void AssignOperator(const Array& caveArray);
            void AccessOperator(Array& caveArray, size_t index);
            void Insert(Array& caveArray, size_t index);
            void Delete(Array& caveArray, size_t index);
            void Iterator(Array& caveArray);
            void Other(Array& caveArray);

            Array CreateTempArray(const Array& copyArray);

            void Check(Array& caveArray);

            void Constructor()
            {
                size_t capacity = rand() % 10;
                int32_t item = rand();

                LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Start");

                Array defaultConstructor;
                LOGD(eLogChannel::CORE_CONTAINER, "Array() Success");
                PrintArray(defaultConstructor);

                Array itemConstructor(&item);
                LOGDF(eLogChannel::CORE_CONTAINER, "Array(item(%d)) Success", item);
                PrintArray(itemConstructor);

                Array capacityConstructor(capacity);
                LOGDF(eLogChannel::CORE_CONTAINER, "Array(capacity(%d)) Success", capacity);
                PrintArray(capacityConstructor);

                Array copyConstructor(itemConstructor);
                LOGD(eLogChannel::CORE_CONTAINER, "Array(sizeConstructor) Success");
                PrintArray(copyConstructor);

                Array moveConstructor(CreateTempArray(itemConstructor));
                LOGD(eLogChannel::CORE_CONTAINER, "Array(Array) Success");
                PrintArray(moveConstructor);
            }

            void AssignOperator(const Array& caveArray)
            {
                Array copyAssign;
                copyAssign = caveArray;
                LOGD(eLogChannel::CORE_CONTAINER, "Array = otherArray Success");
                PrintArray(copyAssign);

                Array moveAssign;
                moveAssign = CreateTempArray(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "Array = otherArray() Success");
                PrintArray(moveAssign);
            }

            void AccessOperator(Array& caveArray, size_t index)
            {
                size_t size = rand() % 8 + caveArray.GetSize();

                caveArray.SetCapacity(size);
                stdVector.reserve(size);

                LOGDF(eLogChannel::CORE_CONTAINER, "Array.GetCapacity(): %d", size, caveArray.GetCapacity());

                caveArray.SetSize(size, &accessTable[index]);
                stdVector.resize(size, accessTable[index]);
                LOGDF(eLogChannel::CORE_CONTAINER, "Array.GetSize(): %d", size, accessTable[index], caveArray.GetSize());
                
                LOGDF(eLogChannel::CORE_CONTAINER, "Array.GetMaxSize(): %d", caveArray.GetMaxSize());

                if (!caveArray.IsEmpty())
                {
                    assert(Toint32_t(caveArray.GetFront()) == stdVector.front());
                    assert(Toint32_t(caveArray.GetBack()) == stdVector.back());

                    size_t offset = rand() % caveArray.GetSize();

                    assert(Toint32_t(caveArray.GetData()[offset]) == stdVector.data()[offset]);
                    assert(Toint32_t(caveArray[offset]) == stdVector[offset]);
                }

                Check(caveArray);
            }

            void Insert(Array& caveArray, size_t index)
            {
                for (size_t i = 0; i < insertTableCount[index][0]; ++i)
                {
                    size_t offset;

                    if (caveArray.IsEmpty())
                    {
                        offset = 0;
                    }
                    else
                    {
                        offset = rand() % caveArray.GetSize();
                    }

                    caveArray.Insert(caveArray.GetBeginIterator() + offset, &insertTable[index][0][i]);
                    stdVector.insert(stdVector.begin() + offset, insertTable[index][0][i]);
                }

                for (size_t i = 0; i < insertTableCount[index][1]; ++i)
                {
                    caveArray.InsertBack(&insertTable[index][1][i]);
                    stdVector.push_back(insertTable[index][1][i]);
                }

                Check(caveArray);
            }

            void Delete(Array& caveArray, size_t index)
            {
                for (size_t i = 0; i < deleteTable[index][0]; ++i)
                {
                    size_t offset = rand() % caveArray.GetSize();
                    caveArray.Delete(caveArray.GetBeginIterator() + offset);
                    stdVector.erase(stdVector.begin() + offset);
                }

                for (size_t i = 0; i < deleteTable[index][1]; ++i)
                {
                    caveArray.DeleteBack();
                    stdVector.pop_back();
                }

                Check(caveArray);
            }

            void Iterator(Array& caveArray)
            {
                if (!caveArray.IsEmpty())
                {
                    assert(Toint32_t(*caveArray.GetBeginConstIterator()) == *stdVector.cbegin());
                    assert(Toint32_t(*caveArray.GetBeginIterator()) == *stdVector.begin());
                    assert(Toint32_t(*(caveArray.GetEndConstIterator() - 1)) == *(stdVector.cend() - 1));
                    assert(Toint32_t(*(caveArray.GetEndIterator() - 1)) == *(stdVector.end() - 1));
                }
            }

            void Other(Array& caveArray)
            {
                int item = rand();

                Array tempArray(&item);

                caveArray.Swap(tempArray);
                
                LOGD(eLogChannel::CORE_CONTAINER, "Swap() Success");

                LOGD(eLogChannel::CORE_CONTAINER, "caveArray");
                PrintArray(caveArray);

                LOGD(eLogChannel::CORE_CONTAINER, "tempArray");
                PrintArray(tempArray);

                caveArray.Swap(tempArray);

                assert(caveArray.IsEmpty() == stdVector.empty());

                caveArray.Clear();
                stdVector.clear();

                LOGD(eLogChannel::CORE_CONTAINER, "Clear() Success");
                PrintArray(caveArray);

                assert(caveArray.IsEmpty() == stdVector.empty());

                Check(caveArray);
            }

            Array CreateTempArray(const Array& copyArray)
            {
                Array tempArray(copyArray);

                return tempArray;
            }

            void Check(Array& caveArray)
            {
                for (size_t i = 0; i < caveArray.GetSize(); ++i)
                {
                    assert(stdVector[i] == *reinterpret_cast<int32_t*>(caveArray[i]));
                }
            }
        }

        void Test(uint8_t constIteratorTestCase, size_t constIteratorTestCount, uint8_t iteratorTestCase, size_t iteratorTestCount, uint8_t containerTestCase, size_t containerTestCount)
        {
            srand(time(NULL));

            Array caveArray;

            int32_t inputArray[DEFAULT_ARRAY_SIZE];
            size_t constIteratorCount = 0;
            size_t iteratorCount = 0;
            size_t containerCount = 0;

            for (size_t i = 0; i < DEFAULT_ARRAY_SIZE; ++i)
            {
                inputArray[i] = rand();
                caveArray.InsertBack(&inputArray[i]);
                stdVector.push_back(inputArray[i]);
            }

            LOGD(eLogChannel::CORE_CONTAINER, "====Array Test====");

            LOGD(eLogChannel::CORE_CONTAINER, "caveArray");
            PrintArray(caveArray);

            insertTable = reinterpret_cast<int32_t***>(gCoreMemoryPool.Allocate(sizeof(int32_t**) * containerTestCount));
            insertTableCount = reinterpret_cast<size_t**>(gCoreMemoryPool.Allocate(sizeof(size_t*) * containerTestCount));

            deleteTable = reinterpret_cast<size_t**>(gCoreMemoryPool.Allocate(sizeof(size_t*) * containerTestCount));

            accessTable = reinterpret_cast<int32_t*>(gCoreMemoryPool.Allocate(sizeof(int32_t) * containerTestCount));

            while (constIteratorCount + iteratorCount + containerCount < constIteratorTestCount + iteratorTestCount + containerTestCount)
            {
                if (constIteratorCount < constIteratorTestCount)
                {
                    ConstIteratorTest(constIteratorTestCase, caveArray);
                    ++constIteratorCount;
                }

                if (iteratorCount < iteratorTestCount)
                {
                    IteratorTest(iteratorTestCase, caveArray);
                    ++iteratorCount;
                }

                if (containerCount < containerTestCount)
                {
                    size_t i = containerCount++;

                    insertTableCount[i] = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * 2));
                    insertTableCount[i][0] = rand() % 16 + 1;
                    insertTableCount[i][1] = rand() % 16 + 1;
                    insertTable[i] = reinterpret_cast<int32_t**>(gCoreMemoryPool.Allocate(sizeof(int32_t*) * 2));
                    insertTable[i][0] = reinterpret_cast<int32_t*>(gCoreMemoryPool.Allocate(sizeof(int32_t) * insertTableCount[i][0]));
                    insertTable[i][1] = reinterpret_cast<int32_t*>(gCoreMemoryPool.Allocate(sizeof(int32_t) * insertTableCount[i][1]));

                    deleteTable[i] = reinterpret_cast<size_t*>(gCoreMemoryPool.Allocate(sizeof(size_t) * 2));
                    deleteTable[i][0] = rand() % (caveArray.GetSize() / 2 + 1);
                    deleteTable[i][1] = rand() % (caveArray.GetSize() / 2 + 1);

                    accessTable[i] = rand();

                    for (size_t j = 0; j < insertTableCount[i][0]; ++j)
                    {
                        insertTable[i][0][j] = rand();
                    }

                    for (size_t j = 0; j < insertTableCount[i][1]; ++j)
                    {
                        insertTable[i][1][j] = rand();
                    }

                    ContainerTest(containerTestCase, caveArray);
                }
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

            gCoreMemoryPool.Deallocate(accessTable, sizeof(int32_t) * containerTestCount);
        }

        void PrintArray(const Array& array)
        {
            size_t i = 0;

            LOGDF(eLogChannel::CORE_CONTAINER, "size: %d", array.GetSize());
            LOGDF(eLogChannel::CORE_CONTAINER, "capacity: %d", array.GetCapacity());

            for (const auto& item : array)
            {
                LOGDF(eLogChannel::CORE_CONTAINER, "%d: %d", i, *reinterpret_cast<const int32_t*>(item));
                ++i;
            }
        }

        void PrintArraySimple(const Array& arr)
        {
            LOGDF(eLogChannel::CORE_CONTAINER, "size: %d", arr.GetSize());
            LOGDF(eLogChannel::CORE_CONTAINER, "capacity: %d", arr.GetCapacity());
        }

        const int32_t Toint32_t(const void* item)
        {
            return *reinterpret_cast<const int32_t*>(item);
        }

        void ConstIteratorTest(uint8_t constIteratorTestCase, const Array& caveArray)
        {
            static size_t testCount = 0;
            LOGDF(eLogChannel::CORE_CONTAINER, "====ConstIterator Test#%d====", ++testCount);

            if (constIteratorTestCase & TEST_CONSTRUCTOR)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Start");
                ConstIterator::Constructor(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Success");
            }

            if (constIteratorTestCase & TEST_ASSIGN)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Start");
                ConstIterator::AssignOperator(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Success");
            }

            if (constIteratorTestCase & TEST_ACCESS)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Start");
                ConstIterator::AccessOperator(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Success");
            }

            if (constIteratorTestCase & TEST_MOVE)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_MOVE Start");
                ConstIterator::MoveOperator(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_MOVE Success");
            }

            if (constIteratorTestCase & TEST_COMPARE)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_COMPARE Start");
                ConstIterator::CompareOperator(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_COMPARE Success");
            }
        }

        void IteratorTest(uint8_t iteratorTestCase, Array& caveArray)
        {
            static size_t testCount = 0;
            LOGDF(eLogChannel::CORE_CONTAINER, "====Iterator Test#%d====", ++testCount);

            if (iteratorTestCase & TEST_CONSTRUCTOR)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Start");
                Iterator::Constructor(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_CONSTRUCTOR Success");
            }

            if (iteratorTestCase & TEST_ASSIGN)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Start");
                Iterator::AssignOperator(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Success");
            }

            if (iteratorTestCase & TEST_ACCESS)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Start");
                Iterator::AccessOperator(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Success");
            }

            if (iteratorTestCase & TEST_MOVE)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_MOVE Start");
                Iterator::MoveOperator(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_MOVE Success");
            }
        }

        void ContainerTest(uint8_t containerTestCase, Array& caveArray)
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
                Container::AssignOperator(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ASSIGN Success");
            }

            if (containerTestCase & TEST_ACCESS)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Start");
                Container::AccessOperator(caveArray, testCount - 1);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ACCESS Success");
            }

            if (containerTestCase & TEST_INSERT)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_INSERT Start");
                Container::Insert(caveArray, testCount - 1);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_INSERT Success");
            }

            if (containerTestCase & TEST_DELETE)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_DELETE Start");
                Container::Delete(caveArray, testCount - 1);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_DELETE Success");
            }

            if (containerTestCase & TEST_ITERATOR)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ITERATOR Start");
                Container::Iterator(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_ITERATOR Success");
            }

            if (containerTestCase & TEST_OTHER)
            {
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_OTHER Start");
                Container::Other(caveArray);
                LOGD(eLogChannel::CORE_CONTAINER, "TEST_OTHER Success");
            }

            PrintArraySimple(caveArray);
        }
    }
#endif

}