/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <cassert>
#include <cstring>

#include "CoreTypes.h"
#include "Memory/Allocator.h"

namespace cave
{
	class MemoryManager final
	{
	public:
		static void* Malloc(size_t size);
	private:
		static Allocator mAllocator;
	};

	struct Memory
	{
	public:
		static void Init();
		static void SetupMemoryPools();
		static uint32_t GetBackMemoryPoolSize();
		static int Memcmp(const void* lhs, const void* rhs, size_t count);
		static void* Memset(void* dest, uint8_t ch, size_t count);
		static void* Memcpy(void* dest, const void* src, size_t count);
		static void* Memmove(void* dest, const void* src, size_t count);
		static __forceinline uintptr_t AlignAddress(uintptr_t address, size_t align)
		{
			const size_t mask = align - 1;
			assert((align & mask) == 0);	// pwr of 2
			return (address + mask) & ~mask;
		}

		template<typename T>
		static __forceinline T* AlignPointer(T* ptr, size_t align)
		{
			const uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
			const uintptr_t alignedAddress = AlignAddress(address, align);
			return reinterpret_cast<T*>(alignedAddress);
		}
	private:
		/** The amount of actual physical memory, in bytes (needs to handle >4GB for 64-bit devices running 32-bit code). */
		static uint64_t msTotalPhysical;
		/** The amount of virtual memory, in bytes. */
		static uint64_t msTotalVirtual;
		/** The size of a physical page, in bytes. This is also the granularity for PageProtect(), commitment and properties (e.g. ability to access) of the physical RAM. */
		static size_t msPageSize;
		/**
		 * Some platforms have advantages if memory is allocated in chunks larger than PageSize (e.g. VirtualAlloc() seems to have 64KB granularity as of now).
		 * This value is the minimum allocation size that the system will use behind the scenes.
		 */
		static size_t msOsAllocationGranularity;
		/** The size of a "page" in Binned2 malloc terms, in bytes. Should be at least 64KB. BinnedMalloc expects memory returned from BinnedAllocFromOS() to be aligned on BinnedPageSize boundary. */
		static size_t msBinnedPageSize;

		/** This is the "allocation granularity" in Binned malloc terms, i.e. BinnedMalloc will allocate the memory in increments of this value. If zero, Binned will use BinnedPageSize for this value. */
		static size_t msBinnedAllocationGranularity;

		// AddressLimit - Second parameter is estimate of the range of addresses expected to be returns by BinnedAllocFromOS(). Binned
		// Malloc will adjust its internal structures to make lookups for memory allocations O(1) for this range. 
		// It is ok to go outside this range, lookups will just be a little slower
		static uint64_t msAddressLimit;

		/** Approximate physical RAM in GB; 1 on everything except PC. Used for "course tuning", like FPlatformMisc::NumberOfCores(). */
		static uint32_t msTotalPhysicalGb;
	};
} // namespace cave