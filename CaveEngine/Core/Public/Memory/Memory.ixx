/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <cstdlib>
#include <cstring>
#include <cwchar>

#include "CoreTypes.h"
#include "Assertion/Assert.h"

export module cave.Core.Memory.Memory;

//import std.core;

namespace cave
{
	export template <size_t N>
	FORCEINLINE constexpr size_t GetSufficientCapacity(size_t length);
	export FORCEINLINE constexpr size_t GetUpperPowerOfTwo(size_t number);
	export FORCEINLINE constexpr size_t GetExponent(size_t number);
	export FORCEINLINE constexpr size_t GetPowerOfTwo(size_t exponent);

	export class Memory final
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
		static int32_t WMemcmp(const wchar_t* lhs, const wchar_t* rhs, size_t count);
		static wchar_t* WMemset(wchar_t* dest, wchar_t ch, size_t count);
		static wchar_t* WMemcpy(wchar_t* dest, const wchar_t* src, size_t count);
		static wchar_t* WMemmove(wchar_t* dest, const wchar_t* src, size_t count);
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

	void* Memory::Malloc(size_t size)
	{
		// size:	number of bytes to allocate 

		//Allocates size bytes of uninitialized storage.
		//
		//If allocation succeeds, returns a pointer to the lowest(first) byte in the allocated memory block that is suitably aligned for any scalar type.
		//
		//If size is zero, the behavior is implementation defined(null pointer may be returned, or some non - null pointer may be returned that may not be used to access storage, but has to be passed to std::free)
		//The following functions are required to be thread - safe:

		//The library versions of operator new and operator delete
		//	User replacement versions of global operator new and operator delete
		//	std::calloc, std::malloc, std::realloc, std::aligned_alloc(since C++17), std::free

		//	Calls to these functions that allocate or deallocate a particular unit of storage occur in a single total order, and each such deallocation call happens - before the next allocation(if any) in this order.

		// return:	On success, returns the pointer to the beginning of newly allocated memory. To avoid a memory leak, the returned pointer must be deallocated with std::free() or std::realloc().
					//On failure, returns a null pointer.
		return malloc(size);
	}

#if !defined(__WIN32__)
	void* Memory::AlignedAlloc(size_t alignment, size_t size)
	{
		return aligned_alloc(alignment, size);
	}
#endif

	void* Memory::Calloc(size_t num, size_t size)
	{
		return calloc(num, size);
	}

	void* Memory::Realloc(void* ptr, size_t newSize)
	{
		return realloc(ptr, newSize);
	}

	void Memory::Free(void* ptr)
	{
		free(ptr);
	}

	int32_t Memory::Memcmp(const void* lhs, const void* rhs, size_t count)
	{
		return memcmp(lhs, rhs, count);
	}

	void* Memory::Memset(void* dest, int32_t fill, size_t count)
	{
		return memset(dest, fill, count);
	}

	void* Memory::Memcpy(void* dest, const void* src, size_t count)
	{
		return memcpy(dest, src, count);
	}

	void* Memory::Memmove(void* dest, const void* src, size_t count)
	{
		return memmove(dest, src, count);
	}

	int32_t Memory::WMemcmp(const wchar_t* lhs, const wchar_t* rhs, size_t count)
	{
		return wmemcmp(lhs, rhs, count);
	}

	wchar_t* Memory::WMemset(wchar_t* dest, wchar_t ch, size_t count)
	{
		return wmemset(dest, ch, count);
	}

	wchar_t* Memory::WMemcpy(wchar_t* dest, const wchar_t* src, size_t count)
	{
		return wmemcpy(dest, src, count);
	}

	wchar_t* Memory::WMemmove(wchar_t* dest, const wchar_t* src, size_t count)
	{
		return wmemmove(dest, src, count);
	}
} // namespace cave