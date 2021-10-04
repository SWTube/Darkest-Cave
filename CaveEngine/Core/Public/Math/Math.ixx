/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <concepts>

#include "CoreTypes.h"

#include "Assertion/Assert.h"

export module cave.Core.Math;

import cave.Core.Containers.Array;

namespace cave
{
	export class Math
	{
	public:
		static size_t GetBitCount8(uint8_t data);
		static size_t GetBitCount16(uint16_t data);
		static size_t GetBitCount32(uint32_t data);
		static size_t GetBitCount64(uint64_t data);

		static uint32_t GetFibonacciNumber(uint32_t number, uint32_t* cache, size_t size);
		static uint32_t GetFibonacciNumberRecursive(uint32_t number, uint32_t* cache, size_t size);
		static FORCEINLINE constexpr size_t GetMaxSizeType(size_t x, size_t y);
		static FORCEINLINE constexpr size_t GetMinSizeType(size_t x, size_t y);
	};


	size_t Math::GetBitCount8(uint8_t data)
	{
		uint8_t temp = data - ((data >> 1) & 0333) - ((data >> 2) & 0111);

		return ((temp + (temp >> 3)) & 0307) % 63;
	}

	size_t Math::GetBitCount16(uint16_t data)
	{
		uint16_t temp = data - ((data >> 1) & 0133333) - ((data >> 2) & 011111);

		return ((temp + (temp >> 3)) & 070707) % 63;
	}

	size_t Math::GetBitCount32(uint32_t data)
	{
		uint32_t temp = data - ((data >> 1) & 033333333333) - ((data >> 2) & 011111111111);

		return ((temp + (temp >> 3)) & 030707070707) % 63;
	}

	size_t Math::GetBitCount64(uint64_t data)
	{
		uint64_t temp = data - ((data >> 1) & 0x5555555555555555);
		temp = (temp & 0x3333333333333333) + ((temp >> 2) & 0x3333333333333333);
		return (((temp + (temp >> 4)) & 0xF0F0F0F0F0F0F0F) * 0x101010101010101) >> 56;
	}

	uint32_t Math::GetFibonacciNumber(uint32_t number, uint32_t* cache, size_t size)
	{
		assert(number <= size);

		if (cache[0] != 0u)
		{
			cache[0] = 0u;
		}

		if (cache[1] == 0u)
		{
			cache[1] = 0u;
		}

		for (uint32_t i = 2u; i <= number; ++i)
		{
			cache[i] = cache[i - 2] + cache[i - 1];
		}

		return cache[number];
	}

	uint32_t Math::GetFibonacciNumberRecursive(uint32_t number, uint32_t* cache, size_t size)
	{
		assert(number <= size);

		if (number <= 1u)
		{
			return number;
		}

		if (cache[number] != 0u)
		{
			return cache[number];
		}

		uint32_t ret = GetFibonacciNumberRecursive(number - 2u, cache, size) 
			+ GetFibonacciNumberRecursive(number - 1u, cache, size);

		cache[number] = ret;

		return ret;
	}

	constexpr size_t Math::GetMaxSizeType(size_t x, size_t y)
	{
		size_t a = x - y;

		return (x - (a & (a >> (sizeof(size_t) * 8 - 1))));
	}

	constexpr size_t Math::GetMinSizeType(size_t x, size_t y)
	{
		size_t a = x - y;

		return (x - (a & ~(a >> (sizeof(size_t) * 8 - 1))));
	}
}