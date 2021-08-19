/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreGlobals.h"
#include "Debug/Log.h"
#include "Memory/MemoryPool.h"

export module Knapsack;

import Math;
import Memory;

namespace cave
{
	class Stuff
	{
	public:
		constexpr Stuff(size_t size, size_t value);
		constexpr Stuff(const Stuff& other) = default;
		constexpr Stuff(Stuff&& other) = default;
		constexpr Stuff& operator=(const Stuff& other) = default;
		constexpr Stuff& operator=(Stuff&& other) = default;
		virtual ~Stuff() = default;

		constexpr size_t GetSize() const;
		constexpr void SetSize(size_t size);
		constexpr size_t GetValue() const;
		constexpr void SetValue(size_t value);
	protected:
		size_t mSize;
		size_t mValue;
	};

	class Bag
	{
	public:
		typedef uint32_t slot_t;
	public:
		Bag(size_t capacity);
		Bag(size_t capacity, MemoryPool& pool);
		Bag(const Bag& other);
		Bag(const Bag& other, MemoryPool& pool);
		Bag(Bag&& other);
		Bag(Bag&& other, MemoryPool& pool);

		virtual ~Bag();

		Bag& operator=(const Bag& other);
		Bag& operator=(Bag&& other);

		constexpr const MemoryPool& GetMemoryPool() const;
		constexpr MemoryPool& GetMemoryPool();

		constexpr size_t GetCapacity() const;
		void SetCapacity(size_t capacity);
		constexpr size_t GetSize() const;
		void SetSize(size_t size);
		constexpr const uint32_t* GetBag() const;

		size_t GetBestKnapsack(Stuff* stuffs, size_t size);
	protected:
		MemoryPool* mPool;
		size_t mCapacity = 0u;
		size_t mSize = 0u;
		size_t mSlotSize = 0u;
		slot_t* mBag = nullptr;
	};

	constexpr Stuff::Stuff(size_t size, size_t value)
		: mSize(size)
		, mValue(value)
	{
	}

	constexpr size_t Stuff::GetSize() const
	{
		return mSize;
	}

	constexpr void Stuff::SetSize(size_t size)
	{
		mSize = size;
	}

	constexpr size_t Stuff::GetValue() const
	{
		return mValue;
	}

	constexpr void Stuff::SetValue(size_t value)
	{
		mValue = value;
	}

	Bag::Bag(size_t capacity)
		: Bag(capacity, gCoreMemoryPool)
	{
	}

	Bag::Bag(size_t capacity, MemoryPool& pool)
		: mPool(&pool)
		, mCapacity(capacity)
		, mSize(0u)
		, mSlotSize(mCapacity / (sizeof(slot_t) * 8))
	{
		mBag = reinterpret_cast<slot_t*>(mPool->Allocate(sizeof(slot_t) * mSlotSize));
		Memory::Memset(mBag, 0, mSlotSize * sizeof(slot_t));
	}

	Bag::Bag(const Bag& other)
		: Bag(other, *other.mPool)
	{
	}

	Bag::Bag(const Bag& other, MemoryPool& pool)
		: mPool(&pool)
		, mCapacity(other.mCapacity)
		, mSize(other.mSize)
		, mSlotSize(other.mSlotSize)
	{
		mBag = reinterpret_cast<slot_t*>(mPool->Allocate(sizeof(slot_t) * mSlotSize));
		Memory::Memcpy(mBag, other.mBag, mSlotSize * sizeof(slot_t));
	}

	Bag::Bag(Bag&& other)
		: Bag(std::move(other), *other.mPool)
	{
	}

	Bag::Bag(Bag&& other, MemoryPool& pool)
		: mPool(&pool)
		, mCapacity(other.mCapacity)
		, mSize(other.mSize)
		, mSlotSize(other.mSlotSize)
		, mBag(other.mBag)
	{
		other.mPool = nullptr;
		other.mCapacity = 0u;
		other.mSize = 0u;
		other.mSlotSize = 0u;
		other.mBag = nullptr;
	}

	Bag::~Bag()
	{
		mPool->Deallocate(mBag, sizeof(slot_t) * mSlotSize);
	}

	Bag& Bag::operator=(const Bag& other)
	{
		if (this != &other)
		{
			if (mSlotSize < other.mSlotSize)
			{
				slot_t* newBag = reinterpret_cast<slot_t*>(other.mPool->Allocate(sizeof(slot_t) * other.mSlotSize));
				Memory::Memset(newBag, 0u, sizeof(slot_t) * other.mSlotSize);
				mPool->Deallocate(mBag, sizeof(slot_t) * mSlotSize);
				mBag = newBag;
			}

			mPool = other.mPool;
			mCapacity = other.mCapacity;
			mSize = other.mSize;
			mSlotSize = other.mSlotSize;

			Memory::Memcpy(mBag, other.mBag, sizeof(slot_t) * mSlotSize);
		}

		return *this;
	}

	Bag& Bag::operator=(Bag&& other)
	{
		if (this != &other)
		{
			mPool = other.mPool;
			mCapacity = other.mCapacity;
			mSize = other.mSize;
			mSlotSize = other.mSlotSize;
			mBag = other.mBag;

			other.mPool = nullptr;
			other.mCapacity = 0u;
			other.mSize = 0u;
			other.mSlotSize = 0u;
			other.mBag = nullptr;
		}

		return *this;
	}

	constexpr const MemoryPool& Bag::GetMemoryPool() const
	{
		return *mPool;
	}

	constexpr MemoryPool& Bag::GetMemoryPool()
	{
		return *mPool;
	}

	constexpr size_t Bag::GetCapacity() const
	{
		return mCapacity;
	}

	void Bag::SetCapacity(size_t capacity)
	{
		size_t newSlotSize = capacity / (sizeof(slot_t) * 8u);

		if (newSlotSize > mSlotSize)
		{
			slot_t* newBag = reinterpret_cast<slot_t*>(mPool->Allocate(sizeof(slot_t) * newSlotSize));
			Memory::Memcpy(newBag, mBag, sizeof(slot_t) * mSlotSize);
			mPool->Deallocate(mBag, sizeof(slot_t) * mSlotSize);
			mBag = newBag;

			mSlotSize = newSlotSize;
		}

		if (capacity > mCapacity)
		{
			mCapacity = capacity;
		}
	}

	constexpr size_t Bag::GetSize() const
	{
		return mSize;
	}

	void Bag::SetSize(size_t size)
	{
		if (mCapacity < size)
		{
			size_t newCapacity = GetUpperPowerOfTwo(size);
			size_t newSlotSize = newCapacity / (sizeof(slot_t) * 8u);

			if (newSlotSize > mSlotSize)
			{
				slot_t* newBag = reinterpret_cast<slot_t*>(mPool->Allocate(sizeof(slot_t) * newSlotSize));
				Memory::Memcpy(newBag, mBag, sizeof(slot_t) * mSlotSize);
				mPool->Deallocate(mBag, sizeof(slot_t) * mSlotSize);
				mBag = newBag;
			}

			Memory::Memset(mBag + sizeof(slot_t) * mSlotSize, 1u, sizeof(slot_t) * (newSlotSize - mSlotSize));
			mSlotSize = newSlotSize;

			mCapacity = newCapacity;
		}
	}

	constexpr const uint32_t* Bag::GetBag() const
	{
		return mBag;
	}

	size_t Bag::GetBestKnapsack(Stuff* stuffs, size_t size)
	{
		size_t** grid = reinterpret_cast<size_t**>(mPool->Allocate(sizeof(size_t*) * size));

		for (size_t i = 0; i < size; ++i)
		{
			grid[i] = reinterpret_cast<size_t*>(mPool->Allocate(sizeof(size_t) * mCapacity));
			Memory::Memset(grid[i], 0u, sizeof(size_t) * mCapacity);
		}

		for (size_t itemIndex = 0; itemIndex < mCapacity; ++itemIndex)
		{
			if (stuffs[itemIndex].GetSize() > itemIndex)
			{
				continue;
			}

			grid[0][itemIndex] = stuffs[itemIndex].GetSize();
		}

		for (size_t itemIndex = 1; itemIndex < size; ++itemIndex)
		{
			for (size_t gridIndex = 0; gridIndex < mCapacity; ++gridIndex)
			{
				if (stuffs[itemIndex].GetSize() > gridIndex + 1)
				{
					grid[itemIndex][gridIndex] = grid[itemIndex - 1][gridIndex];
					continue;
				}

				size_t remainingSize = (gridIndex + 1) - stuffs[itemIndex].GetSize();
				size_t remainingMaxValue = grid[itemIndex - 1][remainingSize];

				size_t choice1 = grid[itemIndex - 1][gridIndex];
				size_t choice2 = stuffs[itemIndex].GetValue() + remainingMaxValue;

				grid[itemIndex][gridIndex] = Math::GetMaxSizeType(choice1, choice2);
			}
		}

		size_t result = grid[size - 1][mCapacity - 1];

		for (size_t i = 0; i < size; ++i)
		{
			mPool->Deallocate(grid[i], sizeof(size_t) * mCapacity);
		}

		mPool->Deallocate(grid, sizeof(size_t*) * size);

		return result;
	}

#ifdef CAVE_BUILD_DEBUG
	namespace KnapsackTest
	{
		export void Main();

		void Main()
		{
			{
				Stuff stuffs[3] =
				{
					Stuff(5, 5),
					Stuff(4, 2),
					Stuff(11, 6)
				};

				Bag bag(15);

				LOGDF(cave::eLogChannel::CORE, "Maximum: %u", bag.GetBestKnapsack(stuffs, 3));
			}

			{
				Stuff stuffs[4] =
				{
					Stuff(5, 5),
					Stuff(4, 2),
					Stuff(11, 6),
					Stuff(6, 4)
				};

				Bag bag(15);

				LOGDF(cave::eLogChannel::CORE, "Maximum: %u", bag.GetBestKnapsack(stuffs, 4));
			}

			{
				Stuff stuffs[5] =
				{
					Stuff(5, 5),
					Stuff(4, 2),
					Stuff(11, 6),
					Stuff(6, 4),
					Stuff(2, 3)
				};

				Bag bag(15);

				LOGDF(cave::eLogChannel::CORE, "Maximum: %u", bag.GetBestKnapsack(stuffs, 5));
			}
		}
	}
#endif
}