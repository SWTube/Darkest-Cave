/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */


#include <math.h>

#include "CoreTypes.h"

#include "Debug/Log.h"

export module cave.Core.RandomNumberGenerator;

namespace cave
{
	export constexpr int64_t GetUniformRandomNumber(const uint32_t size);
	export constexpr double GetNormalizedUniformRandomNumber();
	export const int64_t GetBernoulliRandomNumber(const uint32_t size);
	export const int64_t GetExpRandomNumber(const uint32_t size);
	export constexpr void SetRandomSeed(const uint32_t newSeedNum);

	static int64_t seed = 123456789;

	constexpr int64_t GetUniformRandomNumber(const uint32_t size)
	{
		constexpr int64_t mult = 16807;
		constexpr int64_t mod = 2147483647;
		seed = (seed * mult + 1) % mod;
		const int64_t random = (static_cast<double>(seed) / static_cast<double>(mod)) * static_cast<double>(size);
		return random;
	}

	constexpr double GetNormalizedUniformRandomNumber()
	{
		constexpr int64_t mult = 16807;
		constexpr int64_t mod = 2147483647;
		seed = (seed * mult + 1) % mod;
		const double random = static_cast<double>(seed) / static_cast<double>(mod);
		return random;
	}

	const int64_t GetBernoulliRandomNumber(const uint32_t size)
	{
		const double normalizedRandomNumber = GetNormalizedUniformRandomNumber();
		double random = static_cast<int64_t>(log10(normalizedRandomNumber / (1.0 - normalizedRandomNumber)) * size / 5 + size / 2);
		if (random >= size || random < 0)
		{
			random = size / 2;
		}
		return static_cast<int64_t>(random);
	}

	const int64_t GetExpRandomNumber(const uint32_t size)
	{
		const double normalizedRandomNumber = GetNormalizedUniformRandomNumber();
		double random = -1 * log10(1.0 - normalizedRandomNumber);
		return static_cast<int64_t>(random * size / 3) % size;
	}

	constexpr void SetRandomSeed(const uint32_t newSeedNum)
	{
		seed = newSeedNum;
	}

#ifdef CAVE_BUILD_DEBUG
	export namespace RandomNumberGeneratorTest
	{
	#define SIZE (10)
	#define COUNT (10000)

		void Main()
		{
			LOGD(cave::eLogChannel::CORE_RNG, "===RandomNumberGenerator Test===");
			LOGDF(cave::eLogChannel::CORE_RNG, "Current Seed : %d", seed);

			LOGD(cave::eLogChannel::CORE_RNG, "-- GetUniformRandomNumber --");
			int32_t uniformTestArr[SIZE] = { 0 };
			for (size_t i = 0; i < COUNT; i++)
			{
				const int64_t temp = GetUniformRandomNumber(SIZE);
				uniformTestArr[temp]++;
			}
			for (size_t i = 0; i < SIZE; i++)
			{
				LOGDF(cave::eLogChannel::CORE_RNG, "%u : %d", i, uniformTestArr[i]);
			}

			LOGD(cave::eLogChannel::CORE_RNG, "-- GetBernoulliRandomNumber --");
			int32_t bernoulliTestArr[SIZE] = { 0 };
			for (size_t i = 0; i < COUNT; i++)
			{
				const int32_t temp = GetBernoulliRandomNumber(SIZE);
				bernoulliTestArr[temp]++;
			}
			for (size_t i = 0; i < SIZE; i++)
			{
				LOGDF(cave::eLogChannel::CORE_RNG, "%u : %d", i, bernoulliTestArr[i]);
			}

			LOGD(cave::eLogChannel::CORE_RNG, "-- GetExpRandomNumber --");
			int32_t expTestArr[SIZE] = { 0 };
			for (size_t i = 0; i < COUNT; i++)
			{
				const int32_t temp = GetExpRandomNumber(SIZE);
				expTestArr[temp]++;
			}
			for (size_t i = 0; i < SIZE; i++)
			{
				LOGDF(cave::eLogChannel::CORE_RNG, "%u : %d", i, expTestArr[i]);
			}
		}
	}
#endif
}

