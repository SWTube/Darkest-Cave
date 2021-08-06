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
		constexpr explicit BoundingRect(const Point& topLeft, float width, float height);
		constexpr explicit BoundingRect(const BoundingRect& other);
		constexpr explicit BoundingRect(BoundingRect&& other);
		constexpr BoundingRect& operator=(const BoundingRect& other) = delete;
		constexpr BoundingRect& operator=(BoundingRect && other) = delete;
		~BoundingRect() = default;

		constexpr float GetWidth() const;
		constexpr float GetHeight() const;
		constexpr const Point& GetTopLeft() const;
		constexpr const Point& GetBottomRight() const;
		constexpr bool Contains(const Point& point) const;
		constexpr bool Contains(const BoundingRect& other) const;
	private:
		const Point mTopLeft;
		const Point mBottomRight;
	};

	constexpr BoundingRect::BoundingRect(const Point& topLeft, float width, float height)
		: mTopLeft(topLeft)
		, mBottomRight(Point(mTopLeft.GetX() + width, mTopLeft.GetY() + height))
	{
	}

	constexpr BoundingRect::BoundingRect(const BoundingRect& other)
		: mTopLeft(other.mTopLeft)
		, mBottomRight(other.mBottomRight)
	{
	}

	constexpr BoundingRect::BoundingRect(BoundingRect&& other)
		: mTopLeft(std::move(other.mTopLeft))
		, mBottomRight(std::move(other.mBottomRight))
	{
	}

	constexpr float BoundingRect::GetWidth() const
	{
		float x1 = mTopLeft.GetX();
		float x2 = mBottomRight.GetX();

		return (x1 - x2) > 0 ? (x1 - x2) : (x2 - x1);
	}

	constexpr float BoundingRect::GetHeight() const
	{
		float y1 = mTopLeft.GetY();
		float y2 = mBottomRight.GetY();

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
		float pX = point.GetX();
		float pY = point.GetY();

		return pX >= mTopLeft.GetX() && pX <= mBottomRight.GetX() && pY >= mTopLeft.GetY() && pY <= mBottomRight.GetY();
	}

	constexpr bool BoundingRect::Contains(const BoundingRect& other) const
	{
		float x1 = mTopLeft.GetX();
		float x2 = mBottomRight.GetX();
		float y1 = mTopLeft.GetY();
		float y2 = mBottomRight.GetY();

		float otherX1 = other.mTopLeft.GetX();
		float otherX2 = other.mBottomRight.GetX();
		float otherY1 = other.mTopLeft.GetY();
		float otherY2 = other.mBottomRight.GetY();

		return x1 <= otherX1 && x2 >= otherX2 && y1 <= otherY1 && y2 >= otherY2;
	}
}