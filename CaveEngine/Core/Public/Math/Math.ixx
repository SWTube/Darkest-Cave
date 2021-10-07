/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <concepts>
#include <cstdlib>
#include <ctime>

#include "CoreTypes.h"

#include "Assertion/Assert.h"
#include "Debug/Log.h"

export module cave.Core.Math;

import cave.Core.Containers.Array;

constexpr float EPSILON = 0.000001;
constexpr float PI = 3.141592;
constexpr float TWO_PI = 2.f * PI;
constexpr float HALF_PI = PI / 2.f;
constexpr float INV_PI = 1.f / PI;
constexpr float INV_TWO_PI = 1.f / TWO_PI;
constexpr float DEG_TO_RAD = 0.0174533;
constexpr float RAD_TO_DEG = 57.2958;

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
	public:
		static int32_t RecursiveFactorial(int32_t number);

		// trigonometric functions
		static float Sin(float angle);
		static float Cos(float angle);
		static float Tan(float angle);
		static float ArcSin(float angle);
		static float ArcCos(float angle);
		static float ArcTan(float angle);

		// Ceiling & Floor functions
		static int32_t Ceil(float value);
		static int32_t Floor(float value);

		static float Exp(float value);
		static int32_t Abs(int32_t value);
		static float FAbs(float value);
		static float Mod(float numerator, float denominator);

		static float Pow(float base, int32_t exponent);

		// Square root & Inverse Square root
		static float Sqrt(float value);
		static float InverseSqrt(float value);

		static float Log(float value);

		static float Lerp(const float one, const float other, float alpha);
		static float NearestNeighbor(const float f0, const float f1, float t);
		static float CatmullRomSpline(const float f0, const float f1, const float f2, const float f3, float f);
	};

	int32_t Math::RecursiveFactorial(int32_t number)
	{
		if (number <= 1)
		{
			return 1;
		}
		else
		{
			return number * RecursiveFactorial(number - 1);
		}
	}

	float Math::Sin(float angle)
	{
		float result = 0.f;

		for (uint32_t i = 0; i < 10; ++i)
		{
			result += Pow(-1.f, i) * (Pow(angle, (2 * i + 1)) / static_cast<float>(RecursiveFactorial(2 * i + 1)));
		}

		return result;
	}

	float Math::Cos(float angle)
	{
		float result = 0.f;

		for (uint32_t i = 0; i < 10; ++i)
		{
			result += Pow(-1.f, i) * (Pow(angle, (2 * i)) / static_cast<float>(RecursiveFactorial(2 * i)));
		}

		return result;
	}

	float Math::Tan(float angle)
	{
		return Sin(angle) / Cos(angle);
	}

	float Math::ArcSin(float angle)
	{
		return ArcTan(angle / Sqrt(1.f - Pow(angle, 2)));
	}

	float Math::ArcCos(float angle)
	{
		return (HALF_PI - ArcSin(angle));
	}

	float Math::ArcTan(float angle)
	{
		float result = 0.f;

		for (uint32_t i = 0; i < 10; ++i)
		{
			result += Pow(-1.f, i) * (Pow(angle, (2 * i + 1)) / static_cast<float>(2 * i + 1));
		}

		return result;
	}

	int32_t Math::Ceil(float value)
	{
		if (value - static_cast<int32_t>(value) == 0) // integer
		{
			return value;
		}
		else // float
		{
			return value > 0 ? static_cast<int32_t>(value) + 1 : static_cast<int32_t>(value);
		}
	}

	int32_t Math::Floor(float value)
	{
		return value >= 0 ? static_cast<int32_t>(value) : static_cast<int32_t>(value) - 1;
	}

	float Math::Exp(float value)
	{
		float sum = 0.f;

		for (uint32_t i = 0; i < 10; ++i)
		{
			sum += Pow(value, i) / static_cast<float>(RecursiveFactorial(i));
		}

		return sum;
	}

	int32_t Math::Abs(int32_t value)
	{
		int32_t movedValue = value >> 31; // if first bit is 1 -> movedValue == 1, else 0

		return ((value ^ movedValue) - movedValue);
	}

	float Math::FAbs(float value)
	{
		return value >= 0 ? value : -value;
	}

	float Math::Mod(float numerator, float denominator)
	{
		return (numerator - (denominator * static_cast<int32_t>(numerator / denominator)));
	}

	float Math::Pow(float base, int32_t exponent)
	{
		float result = 1.f;

		if (exponent == 0)
		{
			return 1.f;
		}

		if (exponent > 0)
		{
			for (uint32_t i = 0; i < exponent; ++i)
			{
				result *= base;
			}

			return result;
		}
		else
		{
			for (uint32_t i = 0; i < exponent; ++i)
			{
				result *= (1.f / base);
			}

			return result;
		}
	}

	float Math::Sqrt(float value)
	{
		assert(value >= 0.f);

		float x = 2;

		for (uint32_t i = 0; i < 1000; ++i)
		{
			x = (x + (value / x)) / 2;
		}

		return x;
	}

	float Math::InverseSqrt(float value)
	{
		if (Abs(Sqrt(value) - 0.f) < EPSILON)
		{
			return 0.f;
		}
		else
		{
			return 1.f / Sqrt(value);
		}
	}

	// Natural Logarithm (base-e)

	float Math::Log(float value)
	{
		assert(value >= 0.f);

		float result = 0.f;

		if ((value - 1.f) < EPSILON)
		{
			return 0.f;
		}
		else if (value <= 0.f)
		{
			return 0.f;
		}
		else
		{
			for (uint32_t i = 1; i < 15; ++i)
			{
				result += (1.f / static_cast<float>(2 * i - 1)) * Pow(((value - 1.f) / (value + 1.f)), (2 * i - 1));
			}

			return 2.f * result;
		}
	}

	float Math::Lerp(const float one, const float other, float alpha)
	{
		return (one * (1.f - alpha)) + (other * alpha);
	}

	float Math::NearestNeighbor(const float f0, const float f1, float t)
	{
		return (t < 0.5) ? f0 : f1;
	}

	float Math::CatmullRomSpline(const float f0, const float f1, const float f2, const float f3, float f)
	{
		float d1 = (f2 - f0) / 2.f;
		float d2 = (f3 - f1) / 2.f;
		float D1 = f2 - f1;

		float a3 = d1 + d2 - 2.f * D1;
		float a2 = 3.f * D1 - 2.f * d1 - d2;
		float a1 = d1;
		float a0 = f1;

		return a3 * Pow(f, 3) + a2 * Pow(f, 2) + a1 * f + a0;
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