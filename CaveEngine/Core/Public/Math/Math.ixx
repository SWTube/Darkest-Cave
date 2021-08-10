/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <concepts>

#include "CoreTypes.h"

#include "Containers/Array.h"

export module Math;

namespace cave
{
	export class Math
	{
	public:
		static uint32_t GetFibonacciNumber(uint32_t number, TArray<uint32_t>& cache);
	protected:
		static uint32_t GetFibonacciNumberRecursive(uint32_t number, TArray<uint32_t>& cache);
	};

	uint32_t Math::GetFibonacciNumber(uint32_t number, TArray<uint32_t>& cache)
	{
		if (cache.GetCapacity() < number + 1)
		{
			cache.Resize(number + 1, 0u);
		}

		return GetFibonacciNumberRecursive(number, cache);
	}

	uint32_t Math::GetFibonacciNumberRecursive(uint32_t number, TArray<uint32_t>& cache)
	{
		if (number <= 1u)
		{
			return number;
		}

		if (cache[number] != 0u)
		{
			return cache[number];
		}

		uint32_t ret = GetFibonacciNumberRecursive(number - 2u, cache) 
			+ GetFibonacciNumberRecursive(number - 1u, cache);

		cache[number] = ret;

		return ret;
	}
}