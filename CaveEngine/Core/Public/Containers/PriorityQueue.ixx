/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;

#ifdef CAVE_BUILD_DEBUG

#include "Utils/Crt.h"
#include "Debug/Log.h"

#endif

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module cave.Core.Containers.PriorityQueue;

import cave.Core.Containers.Array;
import cave.Core.Containers.CompareItemType;
import cave.Core.Memory.Memory;

export namespace cave
{
	class PriorityQueue final : private Array
	{
	public:
		using Base = Array;

		PriorityQueue();
		PriorityQueue(CompareItem::Type compareMethod);
		PriorityQueue(MemoryPool& pool);
		PriorityQueue(CompareItem::Type compareMethod, MemoryPool& pool);

		constexpr void Enqueue(void* item);
		constexpr void Dequeue();

		constexpr void* GetTop();
		constexpr const void* GetTop() const;

		constexpr bool IsEmpty() const override;
		constexpr size_t GetSize() const override;
		constexpr size_t GetCapacity() const override;

	private:
		CompareItem::Type mCompareMethod;
	};

	PriorityQueue::PriorityQueue()
		: PriorityQueue(CompareItem::DefaultFunction, gCoreMemoryPool)
	{ }

	PriorityQueue::PriorityQueue(CompareItem::Type compareMethod)
		: PriorityQueue(compareMethod, gCoreMemoryPool)
	{ }

	PriorityQueue::PriorityQueue(MemoryPool& pool)
		: PriorityQueue(CompareItem::DefaultFunction, pool)
	{ }

	PriorityQueue::PriorityQueue(CompareItem::Type compareMethod, MemoryPool& pool)
		: Base(pool)
		, mCompareMethod(compareMethod)
	{ }

	constexpr void PriorityQueue::Enqueue(void* item)
	{
		size_t prevIndex = Base::mSize;
		size_t index = (prevIndex - 1) / 2;

		Base::InsertBack(item);

		while (mCompareMethod(item, Base::mData[index]) == eCompareItem::GREATER && prevIndex != 0)
		{
			Base::mData[prevIndex] = Base::mData[index];
			Base::mData[index] = item;

			prevIndex = index;
			index = (index - 1)/2;
		}
	}

	constexpr void PriorityQueue::Dequeue()
	{
		void* item = Base::mData[--Base::mSize];
		Base::mData[0] = item;
		size_t nextIndex = 0;
		size_t index = nextIndex;
		
		while (index == nextIndex && index * 2 + 2 < Base::mSize)
		{
			if (mCompareMethod(Base::mData[index*2 + 1], Base::mData[index * 2 + 2]) == eCompareItem::GREATER)
			{
				nextIndex = index * 2 + 1;
			}
			else
			{
				nextIndex = index * 2 + 2;
			}

			if (mCompareMethod(item, Base::mData[nextIndex]) == eCompareItem::LESS)
			{
				Base::mData[index] = Base::mData[nextIndex];
				Base::mData[nextIndex] = item;

				index = nextIndex;
			}
		}

		if (index * 2 + 2 == Base::mSize)
		{
			nextIndex = index * 2 + 1;

			if (mCompareMethod(item, Base::mData[nextIndex]) == eCompareItem::LESS)
			{
				Base::mData[index] = Base::mData[nextIndex];
				Base::mData[nextIndex] = item;
			}
		}
	}

	constexpr void* PriorityQueue::GetTop()
	{
		return Base::GetFront();
	}

	constexpr const void* PriorityQueue::GetTop() const
	{
		return Base::GetFront();
	}

	constexpr bool PriorityQueue::IsEmpty() const
	{
		return Base::IsEmpty();
	}

	constexpr size_t PriorityQueue::GetSize() const
	{
		return Base::GetSize();
	}

	constexpr size_t PriorityQueue::GetCapacity() const
	{
		return Base::GetCapacity();
	}
#ifdef CAVE_BUILD_DEBUG

	namespace PriorityQueueTest
	{
		constexpr uint8_t TEST_ALL = 0b11111111;
		constexpr uint8_t TEST_CONSTRUCTOR = 0b00000001;
		constexpr uint8_t TEST_ENQUEUE = 0b00000010;
		constexpr uint8_t TEST_DEQUEUE = 0b00000100;
		constexpr uint8_t TEST_GETTER = 0b00001000;

		int32_t* itemTable;

		size_t tableSize = 10000;
		size_t testCount = 1000;
		size_t enqueueCount = 8;
		size_t dequeueCount = 8;
		uint8_t testCase = TEST_ENQUEUE | TEST_DEQUEUE;

		PriorityQueue* cavePriorityQueuePointer;

		void Test();

		eCompareItem TestCompareMethod(void* leftItem, void* rightItem)
		{
			int32_t leftInt = *reinterpret_cast<int32_t*>(leftItem);
			int32_t rightInt = *reinterpret_cast<int32_t*>(rightItem);

			if (leftInt < rightInt)
			{
				return eCompareItem::LESS;
			}

			if (leftInt > rightInt)
			{
				return eCompareItem::GREATER;
			}

			return eCompareItem::EQUAL;
		}

		namespace Container
		{
			void Constructor();
			void Enqueue();
			void Dequeue();
			void Getter();

			void Constructor()
			{
				PriorityQueue priorityQueue;
			}

			void Enqueue()
			{
				size_t count = rand() % enqueueCount + 1;

				for (size_t i = 0; i < count; ++i)
				{
					size_t index = rand() % tableSize;
					cavePriorityQueuePointer->Enqueue(&itemTable[index]);
					LOGDF(eLogChannel::CORE_CONTAINER, "+%d", itemTable[index]);
				}
			}

			void Dequeue()
			{
				size_t count = rand() % dequeueCount + 1;

				for (size_t i = 0; i < count; ++i)
				{
					if (cavePriorityQueuePointer->GetSize() == 0)
					{
						break;
					}

					int32_t item = *reinterpret_cast<int32_t*>(cavePriorityQueuePointer->GetTop());
					cavePriorityQueuePointer->Dequeue();
					LOGDF(eLogChannel::CORE_CONTAINER, "-%d", item);
				}
			}

			void Getter()
			{
				LOGDF(eLogChannel::CORE_CONTAINER, "Size: %d, Capacity: %d", cavePriorityQueuePointer->GetSize(), cavePriorityQueuePointer->GetCapacity());
			}
		}

		void Test()
		{
			srand(time(NULL));

			PriorityQueue cavePriorityQueue;

			cavePriorityQueuePointer = &cavePriorityQueue;

			itemTable = reinterpret_cast<int32_t*>(gCoreMemoryPool.Allocate(sizeof(int32_t) * tableSize));

			for (int i = 0; i < tableSize; ++i)
			{
				itemTable[i] = i;
			}

			for (size_t i = 0; i < testCount; ++i)
			{
				if (testCase & TEST_CONSTRUCTOR)
				{
					Container::Constructor();
				}

				if (testCase & TEST_ENQUEUE)
				{
					Container::Enqueue();
				}

				if (testCase & TEST_DEQUEUE)
				{
					Container::Dequeue();
				}

				if (testCase & TEST_GETTER)
				{
					Container::Getter();
				}
			}

			while (cavePriorityQueuePointer->GetSize() != 0)
			{
				int32_t item = *reinterpret_cast<int32_t*>(cavePriorityQueuePointer->GetTop());
				cavePriorityQueuePointer->Dequeue();
				LOGDF(eLogChannel::CORE_CONTAINER, "-%d", item);
			}

			gCoreMemoryPool.Deallocate(itemTable, sizeof(int32_t) * tableSize);
		}
	}

#endif
}