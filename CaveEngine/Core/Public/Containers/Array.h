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

    // Iterator
private:
    std::vector<T, Allocator> mElements;
};