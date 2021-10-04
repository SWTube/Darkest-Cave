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

export module cave.Core.Containers.Queue;

import cave.Core.Containers.Array;
import cave.Core.Memory.Memory;

export namespace cave
{
	class Queue final : private Array
	{
	public:
		using Base = Array;

		Queue();
		Queue(MemoryPool& pool);
		Queue(const Queue& other);
		Queue(const Queue& other, MemoryPool& pool);
		Queue(Queue&& other);

		constexpr Queue& operator=(const Queue& other);
		constexpr Queue& operator=(Queue&& other);

		constexpr void Enqueue(void* item);
		constexpr void Dequeue();

		constexpr void* GetTop();
		constexpr const void* GetTop() const;

		constexpr bool IsEmpty() const override;
		constexpr size_t GetSize() const override;
		constexpr size_t GetCapacity() const override;

	private:
		size_t mFront;
		size_t mRear;
	};

	Queue::Queue()
		: Queue(gCoreMemoryPool)
	{ }
				
	Queue::Queue(MemoryPool& pool)
		: Base(pool)
		, mFront(0)
		, mRear(0)
	{ 
		Base::mSize = Base::mCapacity;
	}

	Queue::Queue(const Queue& other)
		: Queue(other, gCoreMemoryPool)
	{ }

	Queue::Queue(const Queue& other, MemoryPool& pool)
		: Base(other, pool)
		, mFront(other.mFront)
		, mRear(other.mRear)
	{ }

	Queue::Queue(Queue&& other)
		: Base(std::move(other))
		, mFront(other.mFront)
		, mRear(other.mRear)
	{ }

	constexpr Queue& Queue::operator=(const Queue& other)
	{
		Base::operator=(other);
		mFront = other.mFront;
		mRear = other.mRear;

		return *this;
	}

	constexpr Queue& Queue::operator=(Queue&& other)
	{
		Base::operator=(std::move(other));
		mFront = other.mFront;
		mRear = other.mRear;

		return *this;
	}

	constexpr void Queue::Enqueue(void* item)
	{
		assert(Base::GetMaxSize() > 0);

		Base::GetData()[mRear] = item;

		size_t tempRear = (mRear + 1) & (Base::mCapacity - 1);

		if (tempRear == mFront)
		{
			size_t prevCapacity = Base::mCapacity;
			Base::SetCapacity(prevCapacity << 1);
			Base::mSize = Base::mCapacity;
			Memory::Memcpy(Base::GetData() + mFront + prevCapacity, Base::GetData() + mFront, (prevCapacity - mFront) * sizeof(void*));

			mFront += prevCapacity;
		}

		mRear = tempRear;
	}

	constexpr void Queue::Dequeue()
	{
		assert(GetSize() > 0);

		mFront = (++mFront) & (Base::mCapacity - 1);
	}

	constexpr void* Queue::GetTop()
	{
		assert(!IsEmpty());

		return Base::operator[](mFront);
	}

	constexpr const void* Queue::GetTop() const
	{
		assert(!IsEmpty());

		return Base::operator[](mFront);
	}

	constexpr bool Queue::IsEmpty() const
	{
		return mFront == mRear;
	}

	constexpr size_t Queue::GetSize() const
	{
		return (Base::mCapacity - mFront + mRear) & (Base::mCapacity - 1);
	}

	constexpr size_t Queue::GetCapacity() const
	{
		return Base::mCapacity;
	}

#ifdef CAVE_BUILD_DEBUG

	namespace QueueTest
	{
		constexpr uint8_t TEST_ALL = 0b11111111;
		constexpr uint8_t TEST_CONSTRUCTOR = 0b00000001;
		constexpr uint8_t TEST_ENQUEUE = 0b00000010;
		constexpr uint8_t TEST_DEQUEUE = 0b00000100;
		constexpr uint8_t TEST_GETTER = 0b00001000;

		int32_t* itemTable;

		size_t tableSize = 100;
		size_t testCount = 100000;
		size_t enqueueCount = 32;
		size_t dequeueCount = 32;
		uint8_t testCase = TEST_ENQUEUE | TEST_DEQUEUE;

		Queue* caveQueuePointer;

		void Test();

		namespace Container
		{
			void Constructor();
			void Enqueue();
			void Dequeue();	
			void Getter();

			void Constructor()
			{
				Queue queue;
			}

			void Enqueue()
			{
				size_t count = rand() % enqueueCount + 1;

				for (size_t i = 0; i < count; ++i)
				{
					size_t index = rand() % tableSize;
					caveQueuePointer->Enqueue(&itemTable[index]);
					LOGDF(eLogChannel::CORE_CONTAINER, "+%d", itemTable[index]);
				}
			}

			void Dequeue()
			{
				size_t count = rand() % dequeueCount + 1;

				for (size_t i = 0; i < count; ++i)
				{
					if (caveQueuePointer->GetSize() == 0)
					{
						break;
					}

					int32_t item = *reinterpret_cast<int32_t*>(caveQueuePointer->GetTop());
					caveQueuePointer->Dequeue();
					LOGDF(eLogChannel::CORE_CONTAINER, "-%d", item);
				}
			}

			void Getter()
			{
				LOGDF(eLogChannel::CORE_CONTAINER, "Size: %d, Capacity: %d", caveQueuePointer->GetSize(), caveQueuePointer->GetCapacity());
			}
		}

		void Test()
		{
			srand(time(NULL));

			Queue caveQueue;

			caveQueuePointer = &caveQueue;

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

			while (caveQueue.GetSize() != 0)
			{
				int32_t item = *reinterpret_cast<int32_t*>(caveQueuePointer->GetTop());
				caveQueuePointer->Dequeue();
				LOGDF(eLogChannel::CORE_CONTAINER, "-%d", item);
			}

			gCoreMemoryPool.Deallocate(itemTable, sizeof(int32_t) * tableSize);
		}
	}

#endif
}