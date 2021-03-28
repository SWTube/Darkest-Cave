/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <intrin.h>
#include <string.h>

#include "Memory/Memory.h"

namespace cave
{
	void* MemoryManager::Malloc(size_t size)
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
		return nullptr;
	}

	uint64_t Memory::msTotalPhysical = 0;
	uint64_t Memory::msTotalVirtual = 0;
	size_t Memory::msPageSize = 0;
	size_t Memory::msOsAllocationGranularity = 0;
	size_t Memory::msBinnedPageSize = 0;
	size_t Memory::msBinnedAllocationGranularity = 0;
	uint64_t Memory::msAddressLimit = static_cast<uint64_t>(0xffffffff) + 1;
	uint32_t Memory::msTotalPhysicalGb = 1;

	void Memory::Init()
	{
		SetupMemoryPools();

#if IS_32BITS
		//const int64 GB(1024 * 1024 * 1024);
//		SET_MEMORY_STAT(MCR_Physical, 2 * GB); //2Gb of physical memory on win32
//		SET_MEMORY_STAT(MCR_PhysicalLLM, 5 * GB);	// no upper limit on Windows. Choose 5GB because it's roughly the same as current consoles.
#endif

		if (msTotalPhysical == 0)
		{
			// Gather platform memory constants.
			MEMORYSTATUSEX memoryStatusEx;
			Memset(&memoryStatusEx, 0, sizeof(memoryStatusEx));
			memoryStatusEx.dwLength = sizeof(memoryStatusEx);
			::GlobalMemoryStatusEx(&memoryStatusEx);

			SYSTEM_INFO systemInfo;
			Memset(&systemInfo, 0, sizeof(systemInfo));
			::GetSystemInfo(&systemInfo);

			msTotalPhysical = memoryStatusEx.ullTotalPhys;
			msTotalVirtual = memoryStatusEx.ullTotalVirtual;
			msBinnedPageSize = systemInfo.dwAllocationGranularity;	// Use this so we get larger 64KiB pages, instead of 4KiB
			msBinnedAllocationGranularity = systemInfo.dwPageSize; // Use 4KiB pages for more efficient use of memory - 64KiB pages don't really exist on this CPU
			msOsAllocationGranularity = systemInfo.dwAllocationGranularity;	// VirtualAlloc cannot allocate memory less than that
			msPageSize = systemInfo.dwPageSize;
			uint64_t value = msTotalPhysical;
			unsigned long log2;
			long mask = -static_cast<long>(_BitScanReverse(&log2, value) != 0);
			value = ((63 - log2) & mask) | (64 & ~mask);
			int64_t bitMask = static_cast<int64_t>(value << 57) >> 63;
			mask = -static_cast<long>(_BitScanReverse(&log2, value - 1) != 0);
			value = ((63 - log2) & mask) | (64 & ~mask);
			msAddressLimit = static_cast<uint64_t>(1) << ((64 - value) & (~bitMask));

			msTotalPhysicalGb = static_cast<uint32_t>((msTotalPhysical + 1024 * 1024 * 1024 - 1) / 1024 / 1024 / 1024);
		}
#if IS_32BITS
//		UE_LOG(LogMemory, Log, TEXT("Memory total: Physical=%.1fGB (%dGB approx) Virtual=%.1fGB"),
//			float(MemoryConstants.TotalPhysical / 1024.0 / 1024.0 / 1024.0),
//			MemoryConstants.TotalPhysicalGB,
//			float(MemoryConstants.TotalVirtual / 1024.0 / 1024.0 / 1024.0));
#else
		// Logging virtual memory size for 64bits is pointless.
//		UE_LOG(LogMemory, Log, TEXT("Memory total: Physical=%.1fGB (%dGB approx)"),
//			float(MemoryConstants.TotalPhysical / 1024.0 / 1024.0 / 1024.0),
//			MemoryConstants.TotalPhysicalGB);
#endif //PLATFORM_32BITS

//		// program size is hard to ascertain and isn't so relevant on Windows. For now just set to zero.
//		LLM(FLowLevelMemTracker::Get().SetProgramSize(0));
//
//		DumpStats(*GLog);
	}

	void Memory::SetupMemoryPools()
	{
		//SET_MEMORY_STAT(MCR_Physical, 0); // "unlimited" physical memory for the CPU, we still need to make this call to set the short name, etc
		//SET_MEMORY_STAT(MCR_PhysicalLLM, 0); // total "unlimited" physical memory, we still need to make this call to set the short name, etc
		//SET_MEMORY_STAT(MCR_GPU, 0); // "unlimited" GPU memory, we still need to make this call to set the short name, etc
		//SET_MEMORY_STAT(MCR_TexturePool, 0); // "unlimited" Texture memory, we still need to make this call to set the short name, etc
		//SET_MEMORY_STAT(MCR_StreamingPool, 0);
		//SET_MEMORY_STAT(MCR_UsedStreamingPool, 0);

		// if the platform chooses to have a BackupOOM pool, create it now
		if (GetBackMemoryPoolSize() > 0)
		{
		//	LLM_PLATFORM_SCOPE(ELLMTag::BackupOOMMemoryPoolPlatform);
		//	LLM_SCOPE(ELLMTag::BackupOOMMemoryPool);

		//	BackupOOMMemoryPool = FPlatformMemory::BinnedAllocFromOS(FPlatformMemory::GetBackMemoryPoolSize());

		//	LLM(FLowLevelMemTracker::Get().OnLowLevelAlloc(ELLMTracker::Default, BackupOOMMemoryPool, FPlatformMemory::GetBackMemoryPoolSize()));
		}
	}

	uint32_t Memory::GetBackMemoryPoolSize()
	{
		/**
		* Value determined by series of tests on Fortnite with limited process memory.
		* 26MB sufficed to report all test crashes, using 32MB to have some slack.
		* If this pool is too large, use the following values to determine proper size:
		* 2MB pool allowed to report 78% of crashes.
		* 6MB pool allowed to report 90% of crashes.
		*/
		return 32 * 1024 * 1024;
	}

	int Memory::Memcmp(const void* lhs, const void* rhs, size_t count)
	{
		return memcmp(lhs, rhs, count);
	}

	void* Memory::Memset(void* dest, uint8_t ch, size_t count)
	{
		return memset(dest, ch, count);
	}

	void* Memcpy(void* dest, const void* src, size_t count)
	{
		return memcpy(dest, src, count);
	}

	void* Memmove(void* dest, const void* src, size_t count)
	{
		return memmove(dest, src, count);
	}
} // namespace cave