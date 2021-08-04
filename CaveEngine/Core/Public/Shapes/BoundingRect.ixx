/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreTypes.h"

export module BoundingRect;

import Point;

// https://github.com/POCU/COMP3500CodeSamples/blob/master/07/src/academy/pocu/comp3500samples/w07/quadtree/BoundingRect.java

namespace cave
{
	export class BoundingRect final
	{
	public:
		BoundingRect() = delete;
		constexpr explicit BoundingRect(const Point& topLeft, uint32_t width, uint32_t height);
		constexpr explicit BoundingRect(const BoundingRect& other) = default;
		constexpr explicit BoundingRect(BoundingRect&& other) = default;
		constexpr BoundingRect& operator=(const BoundingRect& other) = delete;
		constexpr BoundingRect& operator=(BoundingRect && other) = delete;
		~BoundingRect() = default;

		constexpr uint32_t GetWidth() const;
		constexpr uint32_t GetHeight() const;
		constexpr const Point& GetTopLeft() const;
		constexpr const Point& GetBottomRight() const;
		constexpr bool Contains(const Point& point) const;
		constexpr bool Contains(const BoundingRect& other) const;
	private:
		const Point mTopLeft;
		const Point mBottomRight;
	};

	constexpr BoundingRect::BoundingRect(const Point& topLeft, uint32_t width, uint32_t height)
		: mTopLeft(topLeft)
		, mBottomRight(Point(mTopLeft.GetX() + width, mTopLeft.GetY() + height))
	{
	}

	constexpr uint32_t BoundingRect::GetWidth() const
	{
		uint32_t x1 = mTopLeft.GetX();
		uint32_t x2 = mBottomRight.GetX();

		return (x1 - x2) > 0 ? (x1 - x2) : (x2 - x1);
	}

	constexpr uint32_t BoundingRect::GetHeight() const
	{
		uint32_t y1 = mTopLeft.GetY();
		uint32_t y2 = mBottomRight.GetY();

		return (y1 - y2) > 0 ? (y1 - y2) : (y2 - y1);
	}


	constexpr const Point& BoundingRect::GetTopLeft() const
	{
		return mTopLeft;
	}

	constexpr const Point& BoundingRect::GetBottomRight() const
	{
		return mBottomRight;
	}

	constexpr bool BoundingRect::Contains(const Point& point) const
	{
		uint32_t pX = point.GetX();
		uint32_t pY = point.GetY();

		return pX >= mTopLeft.GetX() && pX <= mBottomRight.GetX() && pY >= mTopLeft.GetY() && pY <= mBottomRight.GetY();
	}

	constexpr bool BoundingRect::Contains(const BoundingRect& other) const
	{
		uint32_t x1 = mTopLeft.GetX();
		uint32_t x2 = mBottomRight.GetX();
		uint32_t y1 = mTopLeft.GetY();
		uint32_t y2 = mBottomRight.GetY();

		uint32_t otherX1 = other.mTopLeft.GetX();
		uint32_t otherX2 = other.mBottomRight.GetX();
		uint32_t otherY1 = other.mTopLeft.GetY();
		uint32_t otherY2 = other.mBottomRight.GetY();

		return x1 <= otherX1 && x2 >= otherX2 && y1 <= otherY1 && y2 >= otherY2;
	}
}