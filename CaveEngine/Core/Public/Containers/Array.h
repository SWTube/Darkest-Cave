/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

// temporary wrapper
#include "CoreTypes.h"
// include assertion macros
// include memory
#include "Memory/Allocator.h"
// include template
#include "Template/EnableIf.h"
#include "Template/IsIterator.h"

namespace cave
{
    template<typename ContainerType, typename ElementType, typename SizeType>
    class TArrayIterator
    {
    public:
        TArrayIterator(ContainerType& container, SizeType startIndex = 0)
            : mContainer(container), mIndex(startIndex)
        {
        }

        TArrayIterator& operator++()
        {
            ++mIndex;
            return *this;
        }

        TArrayIterator operator++(int)
        {
            TArrayIterator temp(*this);
            ++mIndex;
            return temp;
        }

        TArrayIterator& operator--()
        {
            --mIndex;
            return *this;
        }

        TArrayIterator operator--(int)
        {
            TArrayIterator temp(*this);
            --mIndex;
            return temp;
        }

        TArrayIterator& operator+=(SizeType offset)
        {
            mIndex += offset;
            return *this;
        }

        TArrayIterator operator+(SizeType offset)
        {
            TArrayIterator temp(*this);
            return temp += offset;
        }

        TArrayIterator& operator-=(SizeType offset)
        {
            mIndex -= offset;
            return *this;
        }

        TArrayIterator operator-(SizeType offset)
        {
            TArrayIterator temp(*this);
            return temp -= offset;
        }

        ElementType& operator*() const
        {
            return mContainer[mIndex];
        }

        ElementType* operator->() const
        {
            return &mContainer[mIndex];
        }

        SizeType GetIndex() const
        {
            return mIndex;
        }

        void Reset()
        {
            mIndex = 0;
        }

        friend bool operator==(const TArrayIterator& lhs, const TArrayIterator& rhs)
        {
            return &lhs.mContainer == &rhs.mContainer && lhs.mIndex == rhs.mIndex;
        }

    private:
        ContainerType& mContainer;
        SizeType mIndex;
    };

    template<typename ElementType, typename AllocatorType = TAllocator<ElementType>>
    class TArray
    {
    public:
        using Iterator = TArrayIterator<TArray, ElementType, size_t>;
        using ConstIterator = TArrayIterator<TArray, const ElementType, size_t>;

        constexpr explicit TArray(const AllocatorType& alloc) noexcept
            : mData(nullptr)
            , mMaxSize(0)
            , mCurrentSize(0)
            , mAllocator(alloc)
        {
        }

        constexpr TArray(size_t count, const ElementType& value, const AllocatorType& alloc = AllocatorType())
            : mAllocator(alloc)
        {
            mData = new ElementType[count];
            mMaxSize = count;
            mCurrentSize = count;
            for (size_t i = 0; i < count; ++i)
            {
                *(mData + i) = value;
            }
        }

        constexpr explicit TArray(size_t count, const AllocatorType& alloc = AllocatorType())
            : mAllocator(alloc)
        {
            mData = new ElementType[count];
            mMaxSize = count;
            mCurrentSize = 0;
        }

        template<typename InputIt, typename TEnableIf<TIsIterator<Iterator>::Value, bool>::Type = true>
        constexpr TArray(InputIt first, InputIt last, const AllocatorType& alloc = AllocatorType())
            : mAllocator(alloc)
        {
            size_t count = 0;
            for (InputIt iterator = first; iterator != last; ++iterator)
            {
                ++count;
            }
            mData = new ElementType[count];;
            mMaxSize = count;
            mCurrentSize = count;
            size_t i = 0;
            for (InputIt iterator = first; iterator != last; ++iterator, ++i)
            {
                *(mData + i) = *iterator;
            }
        }

        constexpr TArray(const TArray& other)
        {
            if (this != &other)
            {
                mAllocator = other.mAllocator;
                mMaxSize = other.mMaxSize;
                mCurrentSize = other.mCurrentSize;
                mData = new ElementType[mMaxSize];
                for (size_t i = 0; i < mCurrentSize; ++i)
                {
                    mData[i] = other.mData[i];
                }
            }
            else
            {
                mAllocator = AllocatorType();
                mMaxSize = 0;
                mCurrentSize = 0;
                mData = nullptr;
            }
        }

        constexpr TArray(const TArray& other, const AllocatorType& alloc)
        {
            if (this != &other)
            {
                mAllocator = alloc;
                mMaxSize = other.mMaxSize;
                mCurrentSize = other.mCurrentSize;
                mData = new ElementType[mMaxSize];
                for (size_t i = 0; i < mCurrentSize; ++i)
                {
                    mData[i] = other.mData[i];
                }
            }
            else
            {
                mAllocator = alloc;
                mMaxSize = 0;
                mCurrentSize = 0;
                mData = nullptr;
            }
        }

        constexpr TArray(TArray&& other) noexcept
        {
            if (this != &other)
            {
                mAllocator = other.mAllocator;
                mMaxSize = other.mMaxSize;
                mCurrentSize = other.mCurrentSize;
                mData = other.mData;
                other.mMaxSize = 0;
                other.mCurrentSize = 0;
                other.mData = nullptr;
            }
            else
            {
                mAllocator = AllocatorType();
                mMaxSize = 0;
                mCurrentSize = 0;
                mData = nullptr;
            }
        }

        constexpr TArray(TArray&& other, const AllocatorType& alloc)
        {
            if (this != &other)
            {
                mAllocator = alloc;
                mMaxSize = other.mMaxSize;
                mCurrentSize = other.mCurrentSize;
                mData = other.mData;
                other.mMaxSize = 0;
                other.mCurrentSize = 0;
                other.mData = nullptr;
            }
            else
            {
                mAllocator = alloc;
                mMaxSize = 0;
                mCurrentSize = 0;
                mData = nullptr;
            }
        }

        ~TArray()
        {
            if (mData != nullptr)
            {
                delete[] mData;
            }
        }

        constexpr TArray& operator=(const TArray& other)
        {
            if (this != &other)
            {
                mAllocator = other.mAllocator;
                mMaxSize = other.mMaxSize;
                mCurrentSize = other.mCurrentSize;
                mData = new ElementType[mMaxSize];
                for (size_t i = 0; i < mCurrentSize; ++i)
                {
                    mData[i] = other.mData[i];
                }
            }

            return *this;
        }

        constexpr TArray& operator=(TArray&& other) noexcept(std::allocator_traits<AllocatorType>::propagate_on_container_move_assignment::value || std::allocator_traits<AllocatorType>::is_always_equal::value)
        {
            if (this != &other)
            {
                mAllocator = other.mAllocator;
                mMaxSize = other.mMaxSize;
                mCurrentSize = other.mCurrentSize;
                mData = other.mData;
                other.mMaxSize = 0;
                other.mCurrentSize = 0;
                other.mData = nullptr;
            }

            return *this;
        }

        constexpr void Assign(size_t count, const ElementType& value)
        {
            if (mCurrentSize + count > mMaxSize)
            {
                mMaxSize = mCurrentSize + count;
                ElementType* tempData = new ElementType[mMaxSize];
                for (size_t i = 0; i < mCurrentSize; ++i)
                {
                    tempData[i] = mData[i];
                }
                for (size_t i = 0; i < count; ++i)
                {
                    tempData[mCurrentSize + i] = value;
                }
                mCurrentSize += count;
                delete[] mData;
                mData = tempData;
            }

            else
            {
                for (size_t i = 0; i < count; ++i)
                {
                    mData[mCurrentSize + i] = value;
                }
                mCurrentSize += count;
            }
        }

        template<class InputIt, typename TEnableIf<TIsIterator<Iterator>::Value, bool>::Type = true>
        constexpr void Assign(InputIt first, InputIt last)
        {
            size_t count = 0;
            for (InputIt iterator = first; iterator != last; ++iterator)
            {
                ++count;
            }

            if (mCurrentSize + count > mMaxSize)
            {
                mMaxSize = mCurrentSize + count;
                ElementType* tempData = new ElementType[mMaxSize];
                for (size_t i = 0; i < mCurrentSize; ++i)
                {
                    tempData[i] = mData[i];
                }

                size_t i = 0;
                for (InputIt iterator = first; iterator != last; ++iterator, ++i)
                {
                    tempData[mCurrentSize + i] = *iterator;
                }
                mCurrentSize += count;
                delete[] mData;
                mData = tempData;
            }

            else
            {
                size_t i = 0;
                for (InputIt iterator = first; iterator != last; ++iterator, ++i)
                {
                    mData[mCurrentSize + i] = *iterator;
                }
                mCurrentSize += count;
            }
        }

        constexpr void ClearElements()
        {
            mCurrentSize = 0;
        }

        constexpr void InsertBack(const ElementType& element)
        {
            Assign(1, element);
        }

        constexpr void RemoveBack()
        {
            --mCurrentSize;
        }

        constexpr bool IsEmpty()
        {
            return (mCurrentSize == 0);
        }

        constexpr size_t GetSize()
        {
            return mCurrentSize;
        }

        constexpr size_t GetMaxSize()
        {
            return mMaxSize;
        }

        constexpr AllocatorType GetAllocator() const noexcept
        {
            return mAllocator;
        }

        // Element Access
        constexpr ElementType& operator[](size_t pos)
        {
            return *(mData + pos);
        }

        constexpr const ElementType& operator[](size_t pos) const
        {
            return *(mData + pos);
        }

        constexpr ElementType& GetFront()
        {
            return *mData;
        }

        constexpr const ElementType& GetFront() const
        {
            return *mData;
        }

        constexpr ElementType& GetBack()
        {
            return *(mData + mCurrentSize - 1);
        }

        constexpr const ElementType& GetBack() const
        {
            return *(mData + mCurrentSize - 1);
        }

        constexpr ElementType* GetData() noexcept
        {
            return mData;
        }

        constexpr const ElementType* GetData() const noexcept
        {
            return mData;
        }

        // Iterators

        constexpr Iterator GetBeginIterator()
        {
            return Iterator(*this, 0);
        }

        constexpr Iterator GetEndIterator()
        {
            return Iterator(*this, 0 + mCurrentSize);
        }

        constexpr ConstIterator GetBeginConstIterator()
        {
            return ConstIterator(*this, 0);
        }

        constexpr ConstIterator GetEndConstIterator()
        {
            return ConstIterator(*this, 0 + mCurrentSize);
        }

    private:
        size_t mCurrentSize;
        size_t mMaxSize;
        ElementType* mData;
        AllocatorType mAllocator;
    };
} // namespace cave