/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Memory/MemoryPool.h"

namespace cave
{
	MemoryPool::MemoryPool(size_t maxPoolSize)
		: mPoolSize(maxPoolSize), mFreeSize(maxPoolSize), mMaxNumDataBlocks(0)
	{
		// Set size of blocks to preallocate half the size of requested size for the pool
		size_t poolSize = GetUpperPowerOfTwo(maxPoolSize);
		size_t minAllocateSize = poolSize / 8;
		if (poolSize > 4096)
		{
			mMinBlockSize = 32;
			mMaxBlockSize = 256;
			minAllocateSize = 1024;
		}
		else if (poolSize <= 32)
		{
			mMinBlockSize = 1;
			if (poolSize > 16)
			{
				mMaxBlockSize = 2;
			}
			else
			{
				mMaxBlockSize = 1;
			}
		}
		else
		{
			mMaxBlockSize = poolSize / 32;
			mMinBlockSize = poolSize / 128;
		}
		
		// Initialize vector of predefined Data Blocks to preallocate memories
		mDataBlocks = std::vector<DataBlock*>(GetExponent(poolSize));
		for (size_t i = GetExponent(mMinBlockSize); i <= GetExponent(mMaxBlockSize); ++i)
		{
			// Initialize corresponding Data Block size of power of i
			size_t powerOfTwo = GetPowerOfTwo(i);
			mDataBlocks[i] = new DataBlock(powerOfTwo, minAllocateSize / powerOfTwo);
			mMaxNumDataBlocks += minAllocateSize;
		}
	}

	MemoryPool::~MemoryPool()
	{
#ifdef CAVE_BUILD_DEBUG
		PrintPoolStatus(std::cerr);
#endif
		for (DataBlock* const dataBlock : mDataBlocks)
		{
			delete dataBlock;
		}
	}

	void* MemoryPool::Allocate(size_t size)
	{
		size_t memorySize = GetUpperPowerOfTwo(size);
		size_t memoryIndex = GetExponent(memorySize);

		// Terminate if user requests memory larger than what pool can provide
		if (memoryIndex >= mDataBlocks.size())
		{
			LOGEF(eLogChannel::CORE_MEMORY, std::cerr, "Request memory's index %ul must be greater than number of datablocks %u", memoryIndex, mDataBlocks.size());
			assert(memoryIndex < mDataBlocks.size());
			// return nullptr;
		}
		
		// Create new type of Data Block if user requests bigger / smaller memory
		if (mDataBlocks[memoryIndex] == nullptr)
		{
			mDataBlocks[memoryIndex] = new DataBlock(memorySize, 1ul);
		}

		// LOGEF(eLogChannel::CORE_MEMORY, std::cerr, "memorySize: %u, Datablock[%u]: %u / %u", memorySize, memoryIndex, mDataBlocks[memoryIndex]->GetFreeSize(), mDataBlocks[memoryIndex]->GetAllocatedSize());

		// If Data Block is empty, allocate new memory and push back
		// If user requires larger memory than current free memory, return corresponding pointer but don't store
		if (mDataBlocks[memoryIndex]->IsEmpty() || mFreeSize < memorySize)
		{
			void* newPointer = malloc(memorySize);
			assert(newPointer != nullptr);
			if (mFreeSize >= memorySize)
			{
				mFreeSize -= memorySize;
				mMaxBlockSize += memorySize;
			}
			return newPointer;
		}

		// Memory Pool can give pointer stored in corresponding Data Block
		mFreeSize -= memorySize;
		return mDataBlocks[memoryIndex]->Get();
	}

	void MemoryPool::Deallocate(void* item, size_t size)
	{
		static size_t counter = 0ul;
		// item should not be nullptr
		// If user tries to deallocate pointer already returned to Data Block, neglect.
		size_t memorySize = GetUpperPowerOfTwo(size);
		size_t memoryIndex = GetExponent(memorySize);
		// LOGEF(eLogChannel::CORE_MEMORY, std::cerr, "%u memorySize: %u, Datablock[%u]: %u / %u", counter, memorySize, memoryIndex, mDataBlocks[memoryIndex]->GetFreeSize(), mDataBlocks[memoryIndex]->GetAllocatedSize());

		if (item == nullptr || mDataBlocks[memoryIndex]->HasItem(item))
		{
			LOGE(eLogChannel::CORE_MEMORY, std::cerr, "item is nullptr");
			++counter;
			return;
		}

		// if user deallocates pointer of size bigger / smaller than predefined Data Block, free it
		// if Data Block can't store the returned pointer, free it
		if (mDataBlocks[memoryIndex] == nullptr || (mFreeSize == mPoolSize && mFreeSize > 0))
		{
			LOGE(eLogChannel::CORE_MEMORY, std::cerr, "datablock is nullptr");
			++counter;
			free(item);
			return;
		}

		// Return pointer to Data Block
		mDataBlocks[memoryIndex]->Return(item);
		mFreeSize += memorySize;
		++counter;
	}

	size_t MemoryPool::GetFreeMemorySize() const
	{
		return mFreeSize;
	}

	size_t MemoryPool::GetCurrentStorage() const
	{
		size_t currentStorage = 0;

		for (const auto& dataBlock : mDataBlocks)
		{
			if (dataBlock != nullptr)
			{
				currentStorage += dataBlock->GetPoolSize();
			}
		}

		return currentStorage;
	}

	size_t MemoryPool::GetPoolSize() const
	{
		return mPoolSize;
	}

	size_t MemoryPool::GetMaxNumDataBlocks() const
	{
		return mMaxNumDataBlocks;
	}

	void MemoryPool::PrintPoolStatus(std::ostream& os) const
	{
		for (size_t i = 0ul; i < mDataBlocks.size(); ++i)
		{
			DataBlock* dataBlock = mDataBlocks[i];
			if (dataBlock == nullptr)
			{
				LOGIF(eLogChannel::CORE_MEMORY, os, "DataBlock[%2u] = %7u / %2u / %u (bit/free/allocated)", i, GetPowerOfTwo(i), 0u, 0u);
			}
			else
			{
				LOGIF(eLogChannel::CORE_MEMORY, os, "DataBlock[%2u] = %7u / %2u / %u (bit/free/allocated)", i, dataBlock->GetSize(), dataBlock->GetFreeSize(), dataBlock->GetAllocatedSize());
			}
		}
	}
} // namespace neople