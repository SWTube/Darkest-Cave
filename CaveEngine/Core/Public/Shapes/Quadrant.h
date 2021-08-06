/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <vector>

#include "CoreTypes.h"

#include "CoreGlobals.h"

#include "Debug/Log.h"

import BoundingRect;
import Point;
import TempObject;

// https://github.com/POCU/COMP3500CodeSamples/blob/master/07/src/academy/pocu/comp3500samples/w07/quadtree/Quadrant.java

namespace cave
{
	class Quadrant final
	{
	public:
		constexpr explicit Quadrant(const BoundingRect& boundingRect);
		constexpr explicit Quadrant(BoundingRect&& boundingRect);
		Quadrant(const Quadrant& other) = delete;
		Quadrant(Quadrant&& other) = delete;
		Quadrant& operator=(const Quadrant& other) = delete;
		Quadrant& operator=(Quadrant&& other) = delete;
		~Quadrant();

		bool Insert(const TempObject* tempObject);
		constexpr std::vector<const TempObject*> GetGameObjects(const BoundingRect& rect) const;
	private:
		constexpr void createChildren();

		constexpr static uint32_t MIN_QUAD_DIMENSION = 2u;

		const BoundingRect mBoundingRect;
		Quadrant* mTopLeft = nullptr;
		Quadrant* mTopRight = nullptr;
		Quadrant* mBottomLeft = nullptr;
		Quadrant* mBottomRight = nullptr;
		std::vector<const TempObject*> mGameObjects;
	};

#ifdef CAVE_BUILD_DEBUG
	namespace QuadrantTest
	{
		void Main();
		void Print(const std::vector<const TempObject*> tempObjects);
	}
#endif
}