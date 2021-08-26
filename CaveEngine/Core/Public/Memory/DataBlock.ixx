/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreTypes.h"
#include "Assertion/Assert.h"
#include "Containers/Node.h"
#include "Debug/Log.h"

export module cave.Core.Memory.DataBlock;

import cave.Core.Memory.Memory;

namespace cave
{
	export class DataBlock final
	{
	public:
		DataBlock() = delete;
		DataBlock(size_t dataSize, size_t size);
		DataBlock(const DataBlock&) = delete;
		DataBlock(const DataBlock&&) = delete;
		DataBlock& operator=(const DataBlock&) = delete;
		DataBlock& operator=(const DataBlock&&) = delete;
		~DataBlock();

		constexpr bool IsEmpty() const;
		constexpr bool HasItem(void* item) const;

		FORCEINLINE void* Get();
		FORCEINLINE void Return(void* item);

		constexpr size_t GetSize() const;
		constexpr size_t GetFreeSize() const;
		constexpr size_t GetAllocatedSize() const;
		constexpr size_t GetPoolSize() const;
		void PrintFreedNodes() const;
		void PrintAllocatedNodes() const;
	private:
		FORCEINLINE void addItem(void* item);

		size_t mSize = 0u;
		size_t mFreeSize = 0u;
		size_t mAllocatedSize = 0u;
		MemoryNode* mFree = nullptr;
		MemoryNode* mAllocated = nullptr;
	};

	DataBlock::DataBlock(size_t dataSize, size_t size)
		: mSize(dataSize)
	{
		for (size_t i = 0ul; i < size; ++i)
		{
			// push back memory allocated according to the size of Data Block
			void* newPointer = Memory::Malloc(mSize);
			assert(newPointer != nullptr);
			addItem(newPointer);
		}
	}

	DataBlock::~DataBlock()
	{
		while (mFree != nullptr)
		{
			MemoryNode* tempNode = mFree;
			mFree = mFree->Next;
			delete tempNode;
		}

#ifdef CAVE_BUILD_DEBUG
		assert(mAllocated == nullptr);
#endif
		while (mAllocated != nullptr)
		{
			MemoryNode* tempNode = mAllocated;
			mAllocated = mAllocated->Next;
			delete tempNode;
		}
	}

	constexpr bool DataBlock::IsEmpty() const
	{
		return mFree == nullptr;
	}

	constexpr bool DataBlock::HasItem(void* item) const
	{
		MemoryNode* iterator = mFree;
		while (iterator != nullptr)
		{
			if (iterator->Data == item)
			{
				return true;
			}
			iterator = iterator->Next;
		}

		return false;
	}

	constexpr size_t DataBlock::GetSize() const
	{
		return mSize;
	}

	constexpr size_t DataBlock::GetFreeSize() const
	{
		return mFreeSize;
	}

	constexpr size_t DataBlock::GetAllocatedSize() const
	{
		return mAllocatedSize;
	}

	constexpr size_t DataBlock::GetPoolSize() const
	{
		return mSize * mFreeSize;
	}

	void DataBlock::PrintFreedNodes() const
	{
		MemoryNode* iterator = mFree;

		while (iterator != nullptr)
		{
			LOGDF(eLogChannel::CORE_MEMORY, "Freed Node: %p", iterator->Data);
			iterator = iterator->Next;
		}
	}

	void DataBlock::PrintAllocatedNodes() const
	{
		MemoryNode* iterator = mAllocated;
		uint64_t i = 0ull;

		while (iterator != nullptr)
		{
			LOGDF(eLogChannel::CORE_MEMORY, "%llu: Allocated Node: %p", i, iterator->Data);
			iterator = iterator->Next;
			++i;
		}
	}

	void* DataBlock::Get()
	{
		MemoryNode* allocatedNode = mFree;
		void* newPointer = allocatedNode->Data;
		mFree = mFree->Next;
		allocatedNode->Next = mAllocated;
		mAllocated = allocatedNode;
		++mAllocatedSize;
		--mFreeSize;

		return newPointer;
	}

	void DataBlock::Return(void* item)
	{
		if (mAllocated != nullptr)
		{
			MemoryNode* indirectIterator = mAllocated;

			if (indirectIterator->Data != item)
			{
				while (indirectIterator->Next != nullptr && indirectIterator->Next->Data != item)
				{
					indirectIterator = indirectIterator->Next;
				}

				if (indirectIterator->Next != nullptr)
				{
					MemoryNode* freedNode = indirectIterator->Next;
					indirectIterator->Next = indirectIterator->Next->Next;
					freedNode->Next = mFree;
					mFree = freedNode;
					--mAllocatedSize;
					++mFreeSize;
				}
				else
				{
					addItem(item);
				}
			}
			else
			{
				mAllocated = mAllocated->Next;
				MemoryNode* freedNode = indirectIterator;
				freedNode->Next = mFree;
				mFree = freedNode;
				--mAllocatedSize;
				++mFreeSize;
			}
		}
		else
		{
			addItem(item);
		}
	}

	void DataBlock::addItem(void* item)
	{
		assert(item != nullptr);

		MemoryNode* newNode = new MemoryNode(item, nullptr);

		if (mFree != nullptr)
		{
			newNode->Next = mFree;
			mFree = newNode;
		}
		else
		{
			mFree = newNode;
		}

		++mFreeSize;
	}
} // namespace cave