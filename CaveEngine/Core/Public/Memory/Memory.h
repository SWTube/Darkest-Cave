/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <cassert>

#include "CoreTypes.h"

namespace cave
{
	class MemoryManager final
	{
	public:
		static void* Malloc(size_t size);
	};

	struct PlatformMemory
	{
	public:
		constexpr void* Memmove(void*);
	};

	inline uintptr_t AlignAddress(uintptr_t address, size_t align)
	{
		const size_t mask = align - 1;
		assert((align & mask) == 0);	// pwr of 2
		return (address + mask) & ~mask;
	}

	template<typename T>
	inline T* AlignPointer(T* ptr, size_t align)
	{
		const uintptr_t address = reinterpret_cast<uintptr_t>(ptr);
		const uintptr_t alignedAddress = AlignAddress(address, align);
		return reinterpret_cast<T*>(alignedAddress);
	}
} // namespace cave