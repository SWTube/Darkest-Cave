/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

// temporary wrapper
#include <vector>

#include "DataTypes.h"
// include assertion macros
// include memory

template<typename T, typename Allocator = std::allocator<T>>
class TArray
{
    template<typename T, typename Alloc>
    friend constexpr bool operator==(const std::TArray<T, Alloc>& lhs, const std::TArray<T, Alloc>& rhs);
public:
    constexpr explicit TArray(const Allocator& alloc) noexcept
        : mElements(alloc)
    {
    }

    constexpr TArray(size_type count, const T& value, const Allocator& alloc = Allocator())
        : mElements(count, value, alloc)
    {
    }

    constexpr explicit TArray(size_type count, const Allocator& alloc = Allocator())
        : mElements(count, alloc)
    {
    }

    template<typename InputIt>
    constexpr TArray(InputIt first, InputIt last, const Allocator& alloc = Allocator())
        : mElements(first, last, alloc)
    {
    }

    constexpr TArray(const TArray& other)
        : mElements(other.mElements)
    {
    }

    constexpr TArray(const TArray& other, const Allocator& alloc)
        : mElements(other.mElements, alloc)
    {
    }

    constexpr TArray(TArray&& other) noexcept
        : mElements(std::move(other.mElements))
    {
    }

    constexpr TArray(TArray&& other, const Allocator& alloc)
        : mElemnts(std::move(other.mElements), alloc)
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

    constexpr TArray& operator=(TArray&& other) noexcept(std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value || std::allocator_traits<Allocator>::is_always_equal::value)
    {
        if (this != &other)
        {
            mElements = std::move(other.mElements);
        }

        return mElements;
    }

    constexpr void Assign(size_type count, const T& value)
    {
        mElements.assign(count, value);
    }

    template< class InputIt >
    constexpr void Assign(InputIt first, InputIt last)
    {
        mElements.assign(first, last);
    }

    constexpr allocator_type GetAllocator() const noexcept
    {
        return mElements.get_allocator();
    }

    // Element Access
    constexpr reference At(size_type pos)
    {
        return mElements.at(pos);
    }

    constexpr const_reference At( size_type pos ) const
    {
        return mElements.at(pos);
    }

    constexpr reference operator[](size_type pos)
    {
        return mElements[pos];
    }

    constexpr const_reference operator[](size_type pos) const
    {
        return mElements[pos];
    }

    constexpr reference GetFront()
    {
        return mElements.front();
    }

    constexpr const_reference GetFront() const
    {
        return mElements.front();
    }

    constexpr reference GetBack()
    {
        return mElements.back();
    }

    constexpr const_reference GetBack() const
    {
        return mElements.back();
    }

    constexpr T* GetData() noexcept
    {
        return mElements.data();
    }

    constexpr const T* GetData() const noexcept
    {
        return mElements.data();
    }

    // Iterators
    constexpr iterator GetBeginIterator() noexcept
    {
        return mElements.begin();
    }

    constexpr const_iterator GetBeginConstIterator() const noexcept
    {
        return mElements.cbegin();
    }

    constexpr iterator GetEndIterator() noexcept
    {
        return mElements.end();
    }

    constexpr const_iterator GetEndConstIterator() const noexcept
    {
        return mElements.cend();
    }

    constexpr reverse_iterator GetReverseBeginIterator() noexcept
    {
        return mElements.rbegin();
    }

    constexpr const_reverse_iterator GetReverseBeginConstIterator() const noexcept
    {
        return mElements.crbegin();
    }

    constexpr reverse_iterator GetReverseEndIterator() noexcept
    {
        return mElements.rend();
    }

    constexpr const_reverse_iterator GetReverseEndConstIterator() const noexcept
    {
        return mElements.crend();
    }

    // Capacity
    [[nodiscard]] constexpr bool IsEmpty() const noexcept
    {
        return mElements.empty();
    }

    constexpr size_type GetSize() const noexcept
    {
        return mElements.size();
    }

    constexpr size_type GetMaxSize() const noexcept
    {
        return mElements.max_size();
    }

    constexpr void SetCapacity(size_type newCapacity)
    {
        mElements.reserve(newCapacity);
    }

    constexpr size_type GetCapacity() const noexcept
    {
        return mElements.capacity();
    }

    constexpr void ShrinkToFit()
    {
        mElements.shrink_to_fit();
    }

    // Modifier
    constexpr void Clear() noexcept
    {
        mElements.clear();
    }

    constexpr iterator Insert(const_iterator pos, const T& value)
    {
        return mElements.insert(pos, value);
    }

    constexpr iterator Insert(const_iterator pos, T&& value)
    {
        return mElements.insert(pos, std::move(value));
    }

    constexpr iterator Insert(const_iterator pos, size_type count, const T& value)
    {
        return mElements.insert(pos, count, value);
    }

    template< class InputIt >
    constexpr iterator Insert(const_iterator pos, InputIt first, InputIt last)
    {
        return mElements.insert(pos, first, last);
    }

    constexpr iterator Erase(const_iterator pos)
    {
        return mElements.erase(pos);
    }

    constexpr iterator Erase(const_iterator first, const_iterator last)
    {
        return mElements.erase(first, last);
    }

    constexpr void PushBack(const T& value)
    {
        mElements.push_back(value);
    }

    constexpr void PushBack(T&& value)
    {
        mElements.push_back(std::move(value));
    }

    constexpr void PopBack()
    {
        mElements.pop_back();
    }

    constexpr void Resize(size_type count)
    {
        mElements.resize(count);
    }

    constexpr void Resize(size_type count, const value_type& value)
    {
        mElements.resize(count, value);
    }

    constexpr void swap(TArray& other) noexcept(std::allocator_traits<Allocator>::propagate_on_container_swap::value || std::allocator_traits<Allocator>::is_always_equal::value)
    {
        mElements.swap(other.mElements)
    }

    // Non-member
private:
    std::vector<T, Allocator> mElements;
};