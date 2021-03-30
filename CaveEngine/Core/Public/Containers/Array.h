/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

// temporary wrapper
#include <vector>

#include "CoreTypes.h"
// include assertion macros
// include memory
#include "Memory/Allocator.h"

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
            ++Index;
            return *this;
        }

        TArrayIterator operator++(int)
        {
            TArrayIterator temp(*this);
            ++Index;
            return temp;
        }

        TArrayIterator& operator--()
        {
            --Index;
            return *this;
        }

        TArrayIterator operator--(int)
        {
            TArrayIterator temp(*this);
            --Index;
            return temp;
        }

        TArrayIterator& operator+=(SizeType offset)
        {
            Index += offset;
            return *this;
        }

        TArrayIterator operator+(SizeType offset)
        {
            TArrayIterator temp(*this);
            return temp += offset;
        }

        TArrayIterator& operator-=(SizeType offset)
        {
            Index -= offset;
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

    template<typename ElementType, typename TAllocator = TAllocator<ElementType>>
    class TArray
    {
    public:
        using Iterator = TArrayIterator<TArray, ElementType, size_t>;
        using ConstIterator = TArrayIterator<TArray, const ElementType, size_t>;

        constexpr explicit TArray(const TAllocator& alloc) noexcept
            : mElements(alloc)
        {
        }

        constexpr TArray(size_t count, const ElementType& value, const TAllocator& alloc = TAllocator<ElementType>())
            : mElements(count, value, alloc)
        {
        }

        constexpr explicit TArray(size_t count, const TAllocator& alloc = TAllocator<ElementType>())
            : mElements(count, alloc)
        {
        }

        template<typename InputIt>
        constexpr TArray(InputIt first, InputIt last, const TAllocator& alloc = TAllocator<ElementType>())
            : mElements(first, last, alloc)
        {
        }

        constexpr TArray(size_t count, const T& value, const TAllocator& alloc = TAllocator<T>())
            : mElements(count, value, alloc)
        {
        }

        constexpr explicit TArray(size_t count, const TAllocator& alloc = TAllocator<T>())
            : mElements(count, alloc)
        {
        }

        template<typename InputIt>
        constexpr TArray(InputIt first, InputIt last, const TAllocator& alloc = TAllocator<T>())
            : mElements(first, last, alloc)
        {
        }

        constexpr TArray(const TArray& other)
            : mElements(other.mElements)
        {
        }

        constexpr TArray(const TArray& other, const TAllocator& alloc)
            : mElements(other.mElements, alloc)
        {
        }

        constexpr TArray(TArray&& other) noexcept
            : mElements(std::move(other.mElements))
        {
        }

        constexpr TArray(TArray&& other, const TAllocator& alloc)
            : mElements(std::move(other.mElements), alloc)
        {
        }

        constexpr ~TArray()
        {
            mElements.clear();
        }

        constexpr TArray& operator=(const TArray& other)
        {
            if (this != &other)
            {
                mElements = other.mElements;
            }

            return *this;
        }

        constexpr TArray& operator=(TArray&& other) noexcept(std::allocator_traits<TAllocator>::propagate_on_container_move_assignment::value || std::allocator_traits<TAllocator>::is_always_equal::value)
        {
            if (this != &other)
            {
                mElements = std::move(other.mElements);
            }

            return mElements;
        }

        constexpr void Assign(size_t count, const ElementType& value)
        {
            mElements.assign(count, value);
        }

        template<class InputIt>
        constexpr void Assign(InputIt first, InputIt last)
        {
            mElements.assign(first, last);
        }

        constexpr TAllocator GetAllocator() const noexcept
        {
            return mElements.get_allocator();
        }

        // Element Access
        constexpr ElementType& operator[](size_t pos)
        {
            return mElements[pos];
        }

        constexpr const ElementType& operator[](size_t pos) const
        {
            return mElements[pos];
        }

        constexpr ElementType& GetFront()
        {
            return mElements.front();
        }

        constexpr const ElementType& GetFront() const
        {
            return mElements.front();
        }

        constexpr ElementType& GetBack()
        {
            return mElements.back();
        }

        constexpr const ElementType& GetBack() const
        {
            return mElements.back();
        }

        constexpr ElementType* GetData() noexcept
        {
            return mElements.data();
        }

        constexpr const ElementType* GetData() const noexcept
        {
            return mElements.data();
        }

        // Iterators

        constexpr Iterator GetBeginIterator()
        {
            return Iterator(*this, 0);
        }

        constexpr Iterator GetEndIterator()
        {
            return Iterator(*this, 0 + mElements.size());
        }

        constexpr ConstIterator GetBeginConstIterator()
        {
            return ConstIterator(*this, 0);
        }

        constexpr ConstIterator GetEndConstIterator()
        {
            return ConstIterator(*this, 0 + mElements.size());
        }

    private:
        std::vector<ElementType, TAllocator> mElements;
    };
} // namespace cave