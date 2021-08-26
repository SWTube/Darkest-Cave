/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once
#include "Physics.h"

namespace cave
{
	enum class eShapeType
	{
		Polygon,
		Circle,
		Edge
	};

	class Shape
	{
	public:
		Shape() = delete;

		Shape(eShapeType shapeType);
		
		virtual ~Shape();

		template <class T>
		T& GetShape();

	private:
		eShapeType mShapeType;
		b2PolygonShape mPolygonShape;
		b2CircleShape mCircleShape;
		b2EdgeShape mEdgeShape;
	};
}