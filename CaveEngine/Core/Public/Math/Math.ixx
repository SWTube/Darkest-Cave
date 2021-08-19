/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <concepts>

#include "CoreTypes.h"

#include "Assertion/Assert.h"

export module Math;

import cave.Core.Containers.Array;

namespace cave
{
	export class Math
	{
	public:
		static uint32_t GetFibonacciNumber(uint32_t number, uint32_t* cache, size_t size);
		static uint32_t GetFibonacciNumberRecursive(uint32_t number, uint32_t* cache, size_t size);
		static constexpr size_t GetMaxSizeType(size_t a, size_t b);
	};

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

	constexpr size_t Math::GetMaxSizeType(size_t a, size_t b)
	{
		return (a > b) ? a : b;
	}
}