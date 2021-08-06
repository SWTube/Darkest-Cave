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
		constexpr explicit Point(float x, float y);
		constexpr explicit Point(const Point& other) = default;
		constexpr explicit Point(Point&& other) = default;
		constexpr Point& operator=(const Point& other) = default;
		constexpr Point& operator=(Point && other) = default;
		~Point() = default;

		constexpr float GetX() const;
		constexpr float GetY() const;
	private:
		float mX;
		float mY;
	};

	constexpr Point::Point(float x, float y)
		: mX(x)
		, mY(y)
	{
	}

	constexpr float Point::GetX() const
	{
		return mX;
	}

	constexpr float Point::GetY() const
	{
		return mY;
	}
}