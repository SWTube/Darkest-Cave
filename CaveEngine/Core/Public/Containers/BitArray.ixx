/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreTypes.h"

#include "Assertion/Assert.h"
#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module cave.Core.Containers.BitArray;

import cave.Core.Math;
import cave.Core.Memory.Memory;

namespace cave
{
	export class BitArray final
	{
		//friend BitArray operator&(const BitArray& lhs, const BitArray& rhs);
		//friend BitArray operator|(const BitArray& lhs, const BitArray& rhs);
		//friend BitArray operator^(const BitArray& lhs, const BitArray& rhs);
		//friend bool operator==(const BitArray& lhs, const BitArray& rhs);
		//friend bool operator!=(const BitArray& lhs, const BitArray& rhs);
	public:
		BitArray();
		BitArray(MemoryPool& pool);
		BitArray(size_t size, bool bit);
		BitArray(size_t size, bool bit, MemoryPool& pool);
		explicit BitArray(uint8_t data);
		explicit BitArray(uint8_t data, MemoryPool& pool);
		explicit BitArray(uint16_t data);
		explicit BitArray(uint16_t data, MemoryPool& pool);
		explicit BitArray(uint32_t data);
		explicit BitArray(uint32_t data, MemoryPool& pool);
		explicit BitArray(uint64_t data);
		explicit BitArray(uint64_t data, MemoryPool& pool);
		BitArray(const BitArray& other);
		BitArray(const BitArray& other, MemoryPool& pool);
		constexpr BitArray(BitArray&& other);
		constexpr BitArray(BitArray&& other, MemoryPool& pool);
		virtual ~BitArray();

		BitArray& operator=(const BitArray& other);
		BitArray& operator=(BitArray&& other);

		constexpr bool operator[](size_t index) const;
		constexpr bool Get(size_t index) const;
		constexpr void Set(size_t index, bool value);
		void SetAll(bool value);
		//BitArray operator<<(size_t count) const;
		//BitArray operator>>(size_t count) const;
		//BitArray operator!() const;

	private:
		MemoryPool* mPool = &gCoreMemoryPool;
		size_t mSize = 0;
		size_t mCapacity = sizeof(uint8_t);
		uint8_t* mData = nullptr;
	};


	BitArray::BitArray()
		: BitArray(gCoreMemoryPool)
	{
	}

	BitArray::BitArray(MemoryPool& pool)
		: mPool(&pool)
		, mData(reinterpret_cast<uint8_t*>(mPool->Allocate(mCapacity / 8)))
	{
		Memory::Memset(mPool, 0, (mCapacity + 7) / 8);
	}

	BitArray::BitArray(size_t size, bool bit)
		: BitArray(size, bit, gCoreMemoryPool)
	{
	}

	BitArray::BitArray(size_t size, bool bit, MemoryPool& pool)
		: mPool(&pool)
		, mSize(static_cast<size_t>(bit) * size)
		, mCapacity(((size + 7) / 8) * 8)
		, mData(reinterpret_cast<uint8_t*>(mPool->Allocate(mCapacity / 8)))
	{
		Memory::Memset(mData, static_cast<int>(bit), (mSize + 7) / 8);
		Memory::Memset(mData + (mSize + 7) / 8, 0, (mCapacity / 8) - ((mSize + 7) / 8));
	}

	BitArray::BitArray(uint8_t data)
		: BitArray(data, gCoreMemoryPool)
	{
	}

	BitArray::BitArray(uint8_t data, MemoryPool& pool)
		: mPool(&pool)
		, mSize(Math::GetBitCount8(data))
		, mCapacity(sizeof(data))
		, mData(reinterpret_cast<uint8_t*>(mPool->Allocate(1)))
	{
		mData[0] = data;
	}

	BitArray::BitArray(uint16_t data)
		: BitArray(data, gCoreMemoryPool)
	{
	}

	BitArray::BitArray(uint16_t data, MemoryPool& pool)
		: mPool(&pool)
		, mSize(Math::GetBitCount16(data))
		, mCapacity(sizeof(data))
		, mData(reinterpret_cast<uint8_t*>(mPool->Allocate(2)))
	{
		mData[0] = static_cast<uint8_t>(data >> 8);
		mData[1] = static_cast<uint8_t>(data);
	}

	BitArray::BitArray(uint32_t data)
		: BitArray(data, gCoreMemoryPool)
	{
	}

	BitArray::BitArray(uint32_t data, MemoryPool& pool)
		: mPool(&pool)
		, mSize(Math::GetBitCount32(data))
		, mCapacity(sizeof(data))
		, mData(reinterpret_cast<uint8_t*>(mPool->Allocate(4)))
	{
		mData[0] = static_cast<uint8_t>(data >> 24);
		mData[1] = static_cast<uint8_t>(data >> 16);
		mData[2] = static_cast<uint8_t>(data >> 8);
		mData[3] = static_cast<uint8_t>(data);
	}


	BitArray::BitArray(uint64_t data)
		: BitArray(data, gCoreMemoryPool)
	{
	}

	BitArray::BitArray(uint64_t data, MemoryPool& pool)
		: mPool(&pool)
		, mSize(Math::GetBitCount64(data))
		, mCapacity(sizeof(data))
		, mData(reinterpret_cast<uint8_t*>(mPool->Allocate(8)))
	{
		mData[0] = static_cast<uint8_t>(data >> 56);
		mData[1] = static_cast<uint8_t>(data >> 48);
		mData[2] = static_cast<uint8_t>(data >> 40);
		mData[3] = static_cast<uint8_t>(data >> 32);
		mData[4] = static_cast<uint8_t>(data >> 24);
		mData[5] = static_cast<uint8_t>(data >> 16);
		mData[6] = static_cast<uint8_t>(data >> 8);
		mData[7] = static_cast<uint8_t>(data);
	}

	BitArray::BitArray(const BitArray& other)
		: BitArray(other, *other.mPool)
	{
	}

	BitArray::BitArray(const BitArray& other, MemoryPool& pool)
		: mPool(&pool)
		, mSize(other.mSize)
		, mCapacity(other.mCapacity)
		, mData(reinterpret_cast<uint8_t*>(mPool->Allocate((mCapacity + 7) / 8)))
	{
		Memory::Memcpy(mData, other.mData, (mCapacity + 7) / 8);
	}

	constexpr BitArray::BitArray(BitArray&& other)
		: BitArray(std::move(other), *other.mPool)
	{
	}

	constexpr BitArray::BitArray(BitArray&& other, MemoryPool& pool)
		: mPool(&pool)
		, mSize(other.mSize)
		, mCapacity(other.mCapacity)
		, mData(other.mData)
	{
		other.mSize = 0;
		other.mCapacity = 0;
		other.mData = nullptr;
	}

	BitArray::~BitArray()
	{
		mPool->Deallocate(mData, mCapacity / 8);
	}

	BitArray& BitArray::operator=(const BitArray& other)
	{
		if (this != &other)
		{
			mPool->Deallocate(mData, mCapacity / 8);
			mPool = other.mPool;

			mSize = other.mSize;
			mCapacity = other.mCapacity;

			mData = reinterpret_cast<uint8_t*>(mPool->Allocate(mCapacity / 8));

			Memory::Memcpy(mData, other.mData, mCapacity / 8);
		}

		return *this;
	}

	BitArray& BitArray::operator=(BitArray&& other)
	{
		if (this != &other)
		{
			mPool->Deallocate(mData, mCapacity / 8);
			mPool = other.mPool;
			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mData = other.mData;

			other.mSize = 0;
			other.mCapacity = 0;
			other.mData = nullptr;
		}

		return *this;
	}

	constexpr bool BitArray::operator[](size_t index) const
	{
		assert(index < mSize);

		return mData[7 - (index / 8)] >> (7 - (index % 8));
	}

	constexpr bool BitArray::Get(size_t index) const
	{
		assert(index < mSize);

		return mData[7 - (index / 8)] >> (7 - (index % 8));
	}

	constexpr void BitArray::Set(size_t index, bool value)
	{
		assert(index < mCapacity);

		mData[7 - (index / 8)] = (mData[7 - (index / 8)] & ~(1ul << (7 - (index % 8))) | (static_cast<uint8_t>(value) << (7 - (index % 8))));
	}

	void BitArray::SetAll(bool value)
	{
		mSize = (mCapacity / 8) * static_cast<size_t>(value);

		Memory::Memset(mData, static_cast<int>(value), mCapacity / 8);
	}

	//BitArray BitArray::operator<<(size_t count) const
	//{
	//	BitArray bitArray;

	//	return bitArray;
	//}

	//BitArray BitArray::operator>>(size_t count) const
	//{
	//	BitArray bitArray;

	//	return bitArray;
	//}

	//BitArray BitArray::operator!() const
	//{
	//	BitArray bitArray;

	//	return bitArray;
	//}
}