/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <memory>

#include "CoreTypes.h"

#define MINIMUM_ALIGNMENT	16			// Alignment of blocks
#define MAX_SMALL_POOL_SIZE	(32768-16)	// Maximum block size in GMallocBinned2SmallBlockSizes
#define SMALL_POOL_COUNT	45

namespace caveengine
{
	struct Allocator
	{
	public:
		using size_type_t = size_t;
		using difference_type_t = ptrdiff_t;

		constexpr Allocator() noexcept;
		constexpr Allocator(const Allocator& other) noexcept = default;
		virtual ~Allocator();

		[[nodiscard]] constexpr void* Allocate(size_t size, uint32_t alignment);
		[[nodiscard]] constexpr void* Reallocate(void* ptr, size_t size, uint32_t alignment);
		constexpr void Deallocate(void* ptr, size_t size, size_t n);
		constexpr void Free(void* ptr);
	public:
		static uint16_t msSmallBlockSizesReversed[SMALL_POOL_COUNT];
	};

	template<typename T>
	struct TAllocator : public Allocator
	{
	public:
		using size_type_t = size_t;
		using difference_type_t = ptrdiff_t;

		constexpr TAllocator() noexcept = default;
		constexpr TAllocator(const TAllocator& other) noexcept = default;

		[[nodiscard]] constexpr void* Allocate(size_t n)
		{
			return Allocator::Allocate(sizeof(T) * n, sizeof(T));
		}

		constexpr void Deallocate(void* ptr, size_t n)
		{
			Allocator::Deallocate(ptr, sizeof(T), n);
		}
	};
} // namespace caveengine