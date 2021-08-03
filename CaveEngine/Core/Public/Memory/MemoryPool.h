/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <vector>

#include "CoreTypes.h"

#include "Debug/Log.h"
#include "Memory/DataBlock.h"
#include "Memory/Memory.h"

namespace cave
{
	class MemoryPool final
	{
	public:
		MemoryPool() = delete;
		MemoryPool(size_t maxPoolSize);
		MemoryPool(const MemoryPool&) = delete;
		virtual ~MemoryPool();
		MemoryPool& operator=(const MemoryPool& other) = delete;

		// Capacity
		constexpr size_t GetFreeMemorySize() const;
		size_t GetCurrentStorage() const;
		size_t GetMaxNumDataBlocks() const;
		size_t GetPoolSize() const;

		// Operations
		void* Allocate(size_t size);
		void Deallocate(void* item, size_t size);
		
		void PrintPoolStatus() const;
		void PrintDataBlockByByte(size_t byte) const;
	private:
		size_t mPoolSize;
		size_t mFreeSize;
		size_t mMinBlockSize;
		size_t mMaxBlockSize;
		size_t mMaxNumDataBlocks;
		std::vector<DataBlock*> mDataBlocks;
	};

	constexpr size_t MemoryPool::GetFreeMemorySize() const
	{
		return mFreeSize;
	}

#if CAVE_BUILD_DEBUG
	namespace MemoryPoolTest
	{
		void Test();

		void Constructor();
	}
#endif
}