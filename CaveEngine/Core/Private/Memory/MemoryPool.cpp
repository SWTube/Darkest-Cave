/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Memory/MemoryPool.h"

namespace cave
{
	MemoryPool::MemoryPool(size_t maxPoolSize)
		: mPoolSize(GetUpperPowerOfTwo(maxPoolSize))
		, mFreeSize(GetUpperPowerOfTwo(maxPoolSize))
		, mMaxNumDataBlocks(0)
	{
		// Set size of blocks to preallocate half the size of requested size for the pool
		size_t minAllocateSize = mPoolSize / 8;
		if (mPoolSize > 4096)
		{
			mMinBlockSize = 32;
			mMaxBlockSize = 256;
			minAllocateSize = 1024;
		}
		else if (mPoolSize <= 32)
		{
			mMinBlockSize = 1;
			if (mPoolSize > 16)
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
			mMaxBlockSize = mPoolSize / 32;
			mMinBlockSize = mPoolSize / 128;
		}
		
		// Initialize vector of predefined Data Blocks to preallocate memories
		mDataBlocks = std::vector<DataBlock*>(GetExponent(mPoolSize));
		size_t exponent = GetExponent(mMaxBlockSize);
		for (size_t i = GetExponent(mMinBlockSize); i <= exponent; ++i)
		{
			// Initialize corresponding Data Block size of power of i
			// SPECTRE MITIGATION
			size_t powerOfTwo = GetPowerOfTwo(i);
			mDataBlocks[i] = new DataBlock(powerOfTwo, minAllocateSize / powerOfTwo);
			mMaxNumDataBlocks += minAllocateSize;
		}
	}

	MemoryPool::~MemoryPool()
	{
#ifdef CAVE_BUILD_DEBUG
		PrintPoolStatus();
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
		//if (memoryIndex >= mDataBlocks.size())
		//{
			//LOGEF(eLogChannel::CORE_MEMORY, "Request memory's index %ul must be greater than number of datablocks %u", memoryIndex, mDataBlocks.size());
		assert(memoryIndex < mDataBlocks.size());
			// return nullptr;
		//}
		
		// Create new type of Data Block if user requests bigger / smaller memory
		if (mDataBlocks[memoryIndex] == nullptr)
		{
			mDataBlocks[memoryIndex] = new DataBlock(memorySize, 1ul);
		}

		// LOGEF(eLogChannel::CORE_MEMORY, "memorySize: %u, Datablock[%u]: %u / %u", memorySize, memoryIndex, mDataBlocks[memoryIndex]->GetFreeSize(), mDataBlocks[memoryIndex]->GetAllocatedSize());

		// If Data Block is empty, allocate new memory and push back
		// If user requires larger memory than current Memory::Free memory, return corresponding pointer but don't store
		if (mDataBlocks[memoryIndex]->IsEmpty() || mFreeSize < memorySize)
		{
			void* newPointer = Memory::Malloc(memorySize);
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
		void* pointer = mDataBlocks[memoryIndex]->Get();
		return pointer;
	}

	void MemoryPool::Deallocate(void* item, size_t size)
	{
		// item should not be nullptr
		// If user tries to deallocate pointer already returned to Data Block, neglect.
		size_t memorySize = GetUpperPowerOfTwo(size);
		size_t memoryIndex = GetExponent(memorySize);
		// LOGEF(eLogChannel::CORE_MEMORY, "%u memorySize: %u, Datablock[%u]: %u / %u", counter, memorySize, memoryIndex, mDataBlocks[memoryIndex]->GetFreeSize(), mDataBlocks[memoryIndex]->GetAllocatedSize());

		if (item == nullptr || mDataBlocks[memoryIndex]->HasItem(item))
		{
			//LOGE(eLogChannel::CORE_MEMORY, "item is nullptr");
			return;
		}

		// if user deallocates pointer of size bigger / smaller than predefined Data Block, Memory::Free it
		// if Data Block can't store the returned pointer, Memory::Free it
		if (mDataBlocks[memoryIndex] == nullptr || (mFreeSize == mPoolSize && mFreeSize > 0))
		{
			//LOGE(eLogChannel::CORE_MEMORY, "datablock is nullptr");
			Memory::Free(item);
			return;
		}

		// Return pointer to Data Block
		mDataBlocks[memoryIndex]->Return(item);
		mFreeSize += memorySize;
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

	void MemoryPool::PrintPoolStatus() const
	{
		for (size_t i = 0ul; i < mDataBlocks.size(); ++i)
		{
			DataBlock* dataBlock = mDataBlocks[i];
			if (dataBlock == nullptr)
			{
				LOGDF(eLogChannel::CORE_MEMORY, "DataBlock[%2llu] = %7llu / %2u / %u (bit/Memory::Free/allocated)"
					, static_cast<uint64_t>(i), static_cast<uint64_t>(GetPowerOfTwo(i)), 0u, 0u);
			}
			else
			{
				LOGDF(eLogChannel::CORE_MEMORY, "DataBlock[%2llu] = %7llu / %2llu / %llu (bit/Memory::Free/allocated)"
					, static_cast<uint64_t>(i), static_cast<uint64_t>(dataBlock->GetSize())
					, static_cast<uint64_t>(dataBlock->GetFreeSize()), static_cast<uint64_t>(dataBlock->GetAllocatedSize()));
			}
		}
	}

	void MemoryPool::PrintDataBlockByByte(size_t byte) const
	{
		size_t memorySize = GetUpperPowerOfTwo(byte);
		size_t memoryIndex = GetExponent(memorySize);

		// mDataBlocks[memoryIndex]->PrintFreedNodes();
		mDataBlocks[memoryIndex]->PrintAllocatedNodes();
	}

#if CAVE_BUILD_DEBUG
	namespace MemoryPoolTest
	{
		void Test()
		{
			//LOGD(eLogChannel::CORE_MEMORY, "======Memory Pool Test======");
			Constructor();
		}

		void Constructor()
		{
			//LOGD(eLogChannel::CORE_MEMORY, "====Constructor Test====");

			// 1 kb
			for (size_t poolSize = 513ul; poolSize <= 1024ul; ++poolSize) {
				MemoryPool memoryPool(poolSize);
				//LOGDF(eLogChannel::CORE_MEMORY, "poolSize: %lu, freeMemorySize: %lu", poolSize, memoryPool.GetFreeMemorySize());
				assert(memoryPool.GetPoolSize() == 1024ul);
			}

			// 2 kb
			for (size_t poolSize = 1025ul; poolSize <= 2048ul; ++poolSize) {
				MemoryPool memoryPool(poolSize);
				//LOGDF(eLogChannel::CORE_MEMORY, "poolSize: %lu, freeMemorySize: %lu", poolSize, memoryPool.GetFreeMemorySize());
				assert(memoryPool.GetPoolSize() == 2048ul);
			}

			// 4 kb
			for (size_t poolSize = 2049ul; poolSize <= 4096ul; ++poolSize) {
				MemoryPool memoryPool(poolSize);
				//LOGDF(eLogChannel::CORE_MEMORY, "poolSize: %lu, freeMemorySize: %lu", poolSize, memoryPool.GetFreeMemorySize());
				assert(memoryPool.GetPoolSize() == 4096ul);
			}

			// 8 kb
			for (size_t poolSize = 4097ul; poolSize <= 8192ul; ++poolSize) {
				MemoryPool memoryPool(poolSize);
				//LOGDF(eLogChannel::CORE_MEMORY, "poolSize: %lu, freeMemorySize: %lu", poolSize, memoryPool.GetFreeMemorySize());
				assert(memoryPool.GetPoolSize() == 8192ul);
			}
		}
	}
#endif
} // namespace cave