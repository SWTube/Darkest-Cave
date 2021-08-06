/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#ifdef __WIN32__
import Memory;
#else 
#include <cstdlib>
#include <cstring>

#include "CoreTypes.h"

#include "Assertion/Assert.h"

//import std.core;

namespace cave
{
	template <size_t N>
	FORCEINLINE constexpr size_t GetSufficientCapacity(size_t length);
	FORCEINLINE constexpr size_t GetUpperPowerOfTwo(size_t number);
	FORCEINLINE constexpr size_t GetExponent(size_t number);
	FORCEINLINE constexpr size_t GetPowerOfTwo(size_t exponent);

	class Memory final
	{
	public:
		static void* Malloc(size_t size);
#if !defined(__WIN32__)
		static void* AlignedAlloc(size_t alignment, size_t size);
#endif
		static void* Calloc(size_t num, size_t size);
		static void* Realloc(void* ptr, size_t newSize);
		static void Free(void* ptr);
		static int32_t Memcmp(const void* lhs, const void* rhs, size_t count);
		static void* Memset(void* dest, int32_t fill, size_t count);
		static void* Memcpy(void* dest, const void* src, size_t count);
		static void* Memmove(void* dest, const void* src, size_t count);
	};

	template <size_t N>
	FORCEINLINE constexpr size_t GetSufficientCapacity(size_t length)
	{
		assert(length <= SIZE_MAX - 1ul - N);

		return (length + 1ul + N - 1ul) - ((length + 1ul + N - 1ul) % N);
	}

	constexpr size_t GetUpperPowerOfTwo(size_t number)
	{
		if (number && !(number & (number - 1ul)))
		{
			return number;
		}

		size_t count = 0ul;
		for (; number != 0ul; number >>= 1, ++count)
		{
		}

		return 1ul << count;
	}

	constexpr size_t GetExponent(size_t number)
	{
		if (!number || (number & (number - 1)))
		{
			return 0ul;
		}

		size_t exponent = 0ul;
		for (size_t i = 1ul; !(i & number); i <<= 1, ++exponent)
		{
		}

		return exponent;
	}

	constexpr size_t GetPowerOfTwo(size_t exponent)
	{
		size_t result = 1ul;

		for (size_t i = 0; i < exponent; ++i)
		{
			result <<= 1;
		}

		return result;
	}

	/*
	FORCEINLINE uintptr_t AlignAddress(uintptr_t address, size_t align)
	{
		const size_t mask = align - 1;
		assert((align & mask) == 0);	// pwr of 2
		return (address + mask) & ~mask;
	}

	template<typename T>
	FORCEINLINE T* AlignPointer(T* ptr, size_t align)
	{
		const uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
		const uintptr_t alignedAddress = AlignAddress(address, align);
		return reinterpret_cast<T*>(alignedAddress);
	}
	*/
} // namespace cave
#endif