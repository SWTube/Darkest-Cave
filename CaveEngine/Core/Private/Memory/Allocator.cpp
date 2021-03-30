/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Memory/Allocator.h"

namespace cave
{
	static uint16_t sSmallBlockSizes[] =
	{
		16, 32, 48, 64, 80, 96, 112, 128,
		160, 192, 224, 256, 288, 320, 384, 448,
		512, 576, 640, 704, 768, 896, 1024 - 16, 1168,
		1360, 1632, 2048 - 16, 2336, 2720, 3264, 4096 - 16, 4368,
		4672, 5040, 5456, 5952, 6544 - 16, 7280, 8192 - 16, 9360,
		10912, 13104, 16384 - 16, 21840, 32768 - 16
	};

	constexpr Allocator::Allocator() noexcept
	{
//		static bool bOnce = false;
//		check(!bOnce); // this is now a singleton-like thing and you cannot make multiple copies
//		bOnce = true;
//
		for (uint32_t index = 0; index != SMALL_POOL_COUNT; ++index)
		{
			uint32_t partner = SMALL_POOL_COUNT - index - 1;
			msSmallBlockSizesReversed[index] = sSmallBlockSizes[partner];
		}

		//SYSTEM_INFO systemInfo;
//		FGenericPlatformMemoryConstants Constants = FPlatformMemory::GetConstants();
//		PageSize = Constants.BinnedPageSize;
//		OsAllocationGranularity = Constants.BinnedAllocationGranularity ? Constants.BinnedAllocationGranularity : PageSize;
//		NumPoolsPerPage = PageSize / sizeof(FPoolInfo);
//		PtrToPoolMapping.Init(PageSize, NumPoolsPerPage, Constants.AddressLimit);
//
//		checkf(FMath::IsPowerOfTwo(PageSize), TEXT("OS page size must be a power of two"));
//		checkf(FMath::IsPowerOfTwo(Constants.AddressLimit), TEXT("OS address limit must be a power of two"));
//		checkf(Constants.AddressLimit > PageSize, TEXT("OS address limit must be greater than the page size")); // Check to catch 32 bit overflow in AddressLimit
//		checkf(SmallBlockSizes[BINNED2_SMALL_POOL_COUNT - 1] == BINNED2_MAX_SMALL_POOL_SIZE, TEXT("BINNED2_MAX_SMALL_POOL_SIZE must equal the smallest block size"));
//		checkf(PageSize % BINNED2_LARGE_ALLOC == 0, TEXT("OS page size must be a multiple of BINNED2_LARGE_ALLOC"));
//		checkf(sizeof(FMallocBinned2::FFreeBlock) <= SmallBlockSizes[0], TEXT("Pool header must be able to fit into the smallest block"));
//		static_assert(UE_ARRAY_COUNT(SmallBlockSizes) == BINNED2_SMALL_POOL_COUNT, "Small block size array size must match BINNED2_SMALL_POOL_COUNT");
//		static_assert(UE_ARRAY_COUNT(SmallBlockSizes) <= 256, "Small block size array size must fit in a byte");
//		static_assert(sizeof(FFreeBlock) <= BINNED2_MINIMUM_ALIGNMENT, "Free block struct must be small enough to fit into a block.");
//
		// Init pool tables.
		for (uint32_t index = 0; index != SMALL_POOL_COUNT; ++index)
		{
//			checkf(Index == 0 || SmallBlockSizes[Index - 1] < SmallBlockSizes[Index], TEXT("Small block sizes must be strictly increasing"));
//			checkf(SmallBlockSizes[Index] <= PageSize, TEXT("Small block size must be small enough to fit into a page"));
//			checkf(SmallBlockSizes[Index] % BINNED2_MINIMUM_ALIGNMENT == 0, TEXT("Small block size must be a multiple of BINNED2_MINIMUM_ALIGNMENT"));
//
			//SmallPoolTables[index].BlockSize = SmallBlockSizes[index];
		}
//
//		// Set up pool mappings
//		uint8* IndexEntry = MemSizeToIndex;
//		uint32  PoolIndex = 0;
//		for (uint32 Index = 0; Index != 1 + (BINNED2_MAX_SMALL_POOL_SIZE >> BINNED2_MINIMUM_ALIGNMENT_SHIFT); ++Index)
//		{
//
//			uint32 BlockSize = Index << BINNED2_MINIMUM_ALIGNMENT_SHIFT; // inverse of int32 Index = int32((Size >> BINNED2_MINIMUM_ALIGNMENT_SHIFT));
//			while (SmallBlockSizes[PoolIndex] < BlockSize)
//			{
//				++PoolIndex;
//				check(PoolIndex != BINNED2_SMALL_POOL_COUNT);
//			}
//			check(PoolIndex < 256);
//			*IndexEntry++ = uint8(PoolIndex);
//		}
//		// now reverse the pool sizes for cache coherency
//
//		for (uint32 Index = 0; Index != BINNED2_SMALL_POOL_COUNT; ++Index)
//		{
//			uint32 Partner = BINNED2_SMALL_POOL_COUNT - Index - 1;
//			SmallBlockSizesReversed[Index] = SmallBlockSizes[Partner];
//		}
//
//		uint64 MaxHashBuckets = PtrToPoolMapping.GetMaxHashBuckets();
//
//		{
//			LLM_PLATFORM_SCOPE(ELLMTag::FMalloc);
//			HashBuckets = (PoolHashBucket*)FPlatformMemory::BinnedAllocFromOS(Align(MaxHashBuckets * sizeof(PoolHashBucket), OsAllocationGranularity));
//#if BINNED2_ALLOCATOR_STATS
//			Binned2HashMemory += Align(MaxHashBuckets * sizeof(PoolHashBucket), OsAllocationGranularity);
//#endif
//		}
//
//		DefaultConstructItems<PoolHashBucket>(HashBuckets, MaxHashBuckets);
//		MallocBinned2 = this;
//		GFixedMallocLocationPtr = (FMalloc**)(&MallocBinned2);
	}

	Allocator::~Allocator()
	{
	}

	[[nodiscard]] constexpr void* Allocator::Allocate(size_t size, uint32_t alignment)
	{
		// Allocates n * sizeof(T) bytes of uninitialized storage by calling ::operator new(std::size_t) or ::operator new(std::size_t, std::align_val_t) (since C++17), but it is unspecified when and how this function is called. The pointer hint may be used to provide locality of reference: the allocator, if supported by the implementation, will attempt to allocate the new memory block as close as possible to hint.

		// Then, this function creates an array of type T[n] in the storage and starts its lifetime, but does not start lifetime of any of its elements.

		// Use of this function is ill-formed if T is an incomplete type.

		// In order to use this function in a constant expression, the allocated storage must be deallocated within the evaluation of the same expression.
		// 	(since C++20)
		// Parameters
		// n 	- 	the number of objects to allocate storage for
		// hint 	- 	pointer to a nearby memory location
		// Return value

		// Pointer to the first element of an array of n objects of type T whose elements have not been constructed yet.
		// Exceptions

		// Throws std::bad_array_new_length if std::numeric_limits<std::size_t>::max() / sizeof(T) < n.
		// 	(since C++11)

		// Throws std::bad_alloc if allocation fails.
		void* ptr = nullptr;

		// Only allocate from the small pools if the size is small enough and the alignment isn't crazy large.
		// With large alignments, we'll waste a lot of memory allocating an entire page, but such alignments are highly unlikely in practice.
		if ((size <= MAX_SMALL_POOL_SIZE) & (alignment <= MINIMUM_ALIGNMENT))
		{

		}


			return nullptr;
	}

	[[nodiscard]] constexpr void* Allocator::Reallocate(void* ptr, size_t size, uint32_t alignment)
	{
		if (size == 0)
		{
			Free(ptr);
			return nullptr;
		}

//		if (!IsOSAllocation(Ptr))
//		{
//			check(Ptr); // null is 64k aligned so we should not be here
//			// Reallocate to a smaller/bigger pool if necessary
//			FFreeBlock* Free = GetPoolHeaderFromPointer(Ptr);
//			Free->CanaryTest();
//			uint32 BlockSize = Free->BlockSize;
//			uint32 PoolIndex = Free->PoolIndex;
//			if (
//				((NewSize <= BlockSize) & (Alignment <= BINNED2_MINIMUM_ALIGNMENT)) && // one branch, not two
//				(PoolIndex == 0 || NewSize > PoolIndexToBlockSize(PoolIndex - 1)))
//			{
//				return Ptr;
//			}
//
//			// Reallocate and copy the data across
//			void* Result = FMallocBinned2::MallocSelect(NewSize, Alignment);
//			FMemory::Memcpy(Result, Ptr, FMath::Min<SIZE_T>(NewSize, BlockSize));
//			FMallocBinned2::FreeExternal(Ptr);
//			return Result;
//		}
//		if (!Ptr)
//		{
//			void* Result = FMallocBinned2::MallocSelect(NewSize, Alignment);
//			return Result;
//		}
//
//		// Allocated from OS.
//		Mutex.Lock();
//		FPoolInfo* Pool = Private::FindPoolInfo(*this, Ptr);
//		UE_CLOG(!Pool, LogMemory, Fatal, TEXT("FMallocBinned2 Attempt to realloc an unrecognized block %p"), Ptr);
//
//		UPTRINT PoolOsBytes = Pool->GetOsAllocatedBytes();
//		SIZE_T PoolOSRequestedBytes = Pool->GetOSRequestedBytes();
//		checkf(PoolOSRequestedBytes <= PoolOsBytes, TEXT("FMallocBinned2::ReallocExternal %d %d"), int32(PoolOSRequestedBytes), int32(PoolOsBytes));
//		bool bUseSmallMalloc = UseSmallAlloc(NewSize, Alignment);
//		if (NewSize > PoolOsBytes || // can't fit in the old block
//			bUseSmallMalloc || // can switch to the small block allocator
//			Align(NewSize, OsAllocationGranularity) < PoolOsBytes) // we can get some pages back
//		{
//			// Grow or shrink.
//			void* Result;
//			if (bUseSmallMalloc)
//			{
//				// Unlock before a small alloc, which rarely takes a lock
//				Mutex.Unlock();
//				Result = MallocExternalSmall(NewSize, Alignment);
//			}
//			else
//			{
//				// Unlock after a large alloc, which does take a lock, to save unlocking and re-locking unnecessarily
//				Result = MallocExternalLarge(NewSize, Alignment);
//				Mutex.Unlock();
//			}
//
//			FMemory::Memcpy(Result, Ptr, FMath::Min(NewSize, PoolOSRequestedBytes));
//			FMallocBinned2::FreeExternal(Ptr);
//			return Result;
//		}
//
//		Mutex.Unlock();
//
//		Alignment = FMath::Max<uint32>(Alignment, BINNED2_MINIMUM_ALIGNMENT);
//		NewSize = Align(FMath::Max((SIZE_T)1, NewSize), Alignment);
//
//		check(FMath::IsPowerOfTwo(Alignment));
//		check(Alignment <= PageSize);
//		check(FMallocBinned2::FPoolInfo::IsSupportedSize(NewSize));
//
//#if BINNED2_ALLOCATOR_STATS
//		AllocatedLargePoolMemory += ((int64)NewSize) - ((int64)PoolOSRequestedBytes);
//		// don't need to change the AllocatedLargePoolMemoryWAlignment because we didn't reallocate so it's the same size
//#endif
//
//		Pool->SetOSAllocationSizes(NewSize, PoolOsBytes);
//
//		return Ptr;
	}

	constexpr void Allocator::Deallocate(void* ptr, size_t size, size_t n)
	{
		// Deallocates the storage referenced by the pointer p, which must be a pointer obtained by an earlier call to allocate().

		// The argument n must be equal to the first argument of the call to allocate() that originally produced p; otherwise, the behavior is undefined.

		// Calls ::operator delete(void*) or ::operator delete(void*, std::align_val_t) (since C++17), but it is unspecified when and how it is called.

		// In evaluation of a constant expression, this function must deallocate storage allocated within the evaluation of the same expression.
		// 	(since C++20)
		// Parameters
		// p 	- 	pointer obtained from allocate()
		// n 	- 	number of objects earlier passed to allocate()
	}

	constexpr void Allocator::Free(void* ptr)
	{

	}
} // namespace cave