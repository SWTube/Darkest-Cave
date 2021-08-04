/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreTypes.h"

export module Point;

// https://github.com/POCU/COMP3500CodeSamples/blob/master/07/src/academy/pocu/comp3500samples/w07/quadtree/Point.java
namespace cave
{
	export class Point final
	{
	public:
		Point() = delete;
		constexpr explicit Point(uint32_t x, uint32_t y);
		constexpr explicit Point(const Point& other) = default;
		constexpr explicit Point(Point&& other) = default;
		constexpr Point& operator=(const Point& other) = default;
		constexpr Point& operator=(Point && other) = default;
		~Point() = default;

		constexpr uint32_t GetX() const;
		constexpr uint32_t GetY() const;
	private:
		uint32_t mX;
		uint32_t mY;
	};

	constexpr Point::Point(uint32_t x, uint32_t y)
		: mX(x)
		, mY(y)
	{
	}

	constexpr uint32_t Point::GetX() const
	{
		return mX;
	}

	constexpr uint32_t Point::GetY() const
	{
		return mY;
	}
}