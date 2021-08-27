/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <cstdlib>
#include <ctime>

#include "CoreTypes.h"

#include "Debug/Log.h"
	
export module Math;

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
	export class Math final
	{
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
		static float Abs(float value);
		static float Mod(float numerator, float denominator);
		
		static float Pow(float base, int32_t exponent);

		// Square root & Inverse Square root
		static float Sqrt(float value);
		static float InverseSqrt(float value);

		static float Log(float value);
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

	float Math::Abs(float value)
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
		float x = 2;

		if (value <= 0.f)
		{
			return 0.f;
		}
		else
		{
			for (uint32_t i = 0; i < 1000; ++i)
			{
				x = (x + (value / x)) / 2;
			}

			return x;
		}
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

	export namespace MathTest
	{
		void Main()
		{
			float degree = 30.f * DEG_TO_RAD;

			srand(static_cast<uint32_t>(time(NULL)));

			for (uint32_t i = 0; i < 10; ++i)
			{
				float num = static_cast<float>((rand() - rand())/ 100.f);
				float num_2 = static_cast<float>((rand() - rand()) / 100.f);
				int32_t expo = rand() % 10;

				LOGDF(cave::eLogChannel::CORE_MATH, "Floor(%f): %d", num, Math::Floor(num));
				LOGDF(cave::eLogChannel::CORE_MATH, "Ceil(%f): %d", num, Math::Ceil(num));
				LOGDF(cave::eLogChannel::CORE_MATH, "Abs(%f): %f", num, Math::Abs(num));
				LOGDF(cave::eLogChannel::CORE_MATH, "Pow(%f, %d): %f", num, expo, Math::Pow(num, expo));
				LOGDF(cave::eLogChannel::CORE_MATH, "Mod(%f, %f): %f", num, num_2, Math::Mod(num, num_2));
				LOGDF(cave::eLogChannel::CORE_MATH, "Sqrt(%f): %f", num, Math::Sqrt(num));
				LOGDF(cave::eLogChannel::CORE_MATH, "Exp(%f): %f", num, Math::Exp(num));
				LOGDF(cave::eLogChannel::CORE_MATH, "Log(%f): %f", num, Math::Log(num));

				LOGD(cave::eLogChannel::CORE_MATH, "\n");
			}

			LOGDF(cave::eLogChannel::CORE_MATH, "Sin(%f): %f", degree, Math::Sin(degree)); // 30 degree == 0.5235 radian
			LOGDF(cave::eLogChannel::CORE_MATH, "Cos(%f): %f", degree, Math::Cos(degree));
			LOGDF(cave::eLogChannel::CORE_MATH, "Tan(%f): %f", degree, Math::Tan(degree));
			LOGDF(cave::eLogChannel::CORE_MATH, "ArcSin(%f): %f", degree, Math::ArcSin(degree));
			LOGDF(cave::eLogChannel::CORE_MATH, "ArcCos(%f): %f", degree, Math::ArcCos(degree));
			LOGDF(cave::eLogChannel::CORE_MATH, "ArcTan(%f): %f", degree, Math::ArcTan(degree));
		}
	}
}