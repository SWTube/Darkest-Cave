/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreTypes.h"

export module cave.Core.Types.Float;

namespace cave
{
	//--------------------------------------------------------------------------------------
	// Structures
	//--------------------------------------------------------------------------------------
	export struct Float2
	{
		float X = 0.0f;
		float Y = 0.0f;

		Float2() = default;
		Float2(const Float2& other) = default;
		Float2& operator=(const Float2& other) = default;
		constexpr Float2(Float2&& other) noexcept;
		constexpr Float2& operator=(Float2&& other) noexcept;
		constexpr Float2 operator+(const Float2& other);
		constexpr Float2(float x, float y);
		constexpr Float2(float* array);
	};

	export struct Float3 : public Float2
	{
		float Z = 0.0f;

		Float3() = default;
		Float3(const Float3& other) = default;
		Float3& operator=(const Float3& other) = default;
		constexpr Float3(Float3&& other) noexcept;
		constexpr Float3& operator=(Float3&& other) noexcept;
		constexpr Float3(float x, float y, float z);
		constexpr Float3(float* array);

		constexpr bool operator==(const Float3& rhs) const;
	};

	export struct Float4 : public Float3
	{
		float W = 0.0f;

		Float4() = default;
		Float4(const Float4& other) = default;
		Float4& operator=(const Float4& other) = default;
		constexpr Float4(Float4&& other) noexcept;
		constexpr Float4& operator=(Float4&& other) noexcept;
		constexpr Float4(float x, float y, float z, float w);
		constexpr Float4(float* array);

		constexpr bool operator==(const Float4& rhs) const;
	};

	constexpr Float2::Float2(Float2&& other) noexcept
		: X(other.X)
		, Y(other.Y)
	{
	}

	constexpr Float2 Float2::operator+(const Float2& other) {
		return Float2(X + other.X, Y + other.Y);
	}

	constexpr Float2& Float2::operator=(Float2&& other) noexcept
	{
		X = other.X;
		Y = other.Y;

		return *this;
	}

	constexpr Float2::Float2(float* array)
		: X(array[0])
		, Y(array[1])
	{
	}

	constexpr Float2::Float2(float x, float y)
		: X(x)
		, Y(y)
	{
	}

	constexpr Float3::Float3(Float3&& other) noexcept
		: Float2(std::move(other))
	{
		if (this != &other)
		{
			Z = other.Z;
		}
	}

	constexpr Float3& Float3::operator=(Float3&& other) noexcept
	{
		if (this != &other)
		{
			Float2::operator=(std::move(other));
			Z = other.Z;
		}

		return *this;
	}

	constexpr Float3::Float3(float* array)
		: Float2(array)
		, Z(array[2])
	{
	}

	constexpr Float3::Float3(float x, float y, float z)
		: Float2(x, y)
		, Z(z)
	{
	}

	constexpr bool Float3::operator==(const Float3& rhs) const
	{
		return (X == rhs.X) && (Y == rhs.Y) && (Z == rhs.Z);
	}

	constexpr Float4::Float4(Float4&& other) noexcept
		: Float3(std::move(other))
	{
		if (this != &other)
		{
			W = other.W;
		}
	}

	constexpr Float4& Float4::operator=(Float4&& other) noexcept
	{
		if (this != &other)
		{
			Float3::operator=(std::move(other));
			W = other.W;
		}

		return *this;
	}

	constexpr Float4::Float4(float* array)
		: Float3(array)
		, W(array[3])
	{
	}

	constexpr Float4::Float4(float x, float y, float z, float w)
		: Float3(x, y, z)
		, W(w)
	{
	}

	constexpr bool Float4::operator==(const Float4& rhs) const
	{
		return (X == rhs.X) && (Y == rhs.Y) && (Z == rhs.Z) && (W == rhs.W);
	}
} // namespace cave
