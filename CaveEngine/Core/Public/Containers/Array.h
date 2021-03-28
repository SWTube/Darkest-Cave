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

namespace caveengine
{
    template<typename T, typename TAllocator = TAllocator<T>>
    class TArray
    {
    public:
        constexpr explicit TArray(const TAllocator& alloc) noexcept
            : mElements(alloc)
        {
        }

        //constexpr TArray(size_t count, const T& value, const TAllocator& alloc = TAllocator<T>())
        //    : mElements(count, value, alloc)
        //{
        //}

        //constexpr explicit TArray(size_t count, const TAllocator& alloc = TAllocator<T>())
        //    : mElements(count, alloc)
        //{
        //}

        //template<typename InputIt>
        //constexpr TArray(InputIt first, InputIt last, const TAllocator& alloc = TAllocator<T>())
        //    : mElements(first, last, alloc)
        //{
        //}

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

        constexpr void Assign(size_t count, const T& value)
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
        constexpr T& operator[](size_t pos)
        {
            return mElements[pos];
        }

        constexpr const T& operator[](size_t pos) const
        {
            return mElements[pos];
        }

        constexpr T& GetFront()
        {
            return mElements.front();
        }

        constexpr const T& GetFront() const
        {
            return mElements.front();
        }

        constexpr T& GetBack()
        {
            return mElements.back();
        }

        constexpr const T& GetBack() const
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
        std::vector<T, TAllocator> mElements;
    };
} // namespace caveengine