/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "PhysicsShape.h"

namespace cave
{
	Shape::Shape(eShapeType shapeType)
	{
		mShapeType = shapeType;

		switch (mShapeType)
		{
		case cave::eShapeType::Polygon:
			mPolygonShape = b2PolygonShape();
			mPolygonShape.SetAsBox(1.f, 1.f);
			break;
		case cave::eShapeType::Circle:
			mCircleShape = b2CircleShape();
			mCircleShape.m_radius = 1.f;
			break;
		case cave::eShapeType::Edge:
			mEdgeShape = b2EdgeShape();
			break;
		default:
			break;
		}
	}

	Shape::~Shape()
	{
		
	}

	template <class T>
	T& Shape::GetShape()
	{
		switch (mShapeType)
		{
		case cave::eShapeType::Polygon:
			return mPolygonShape;
		case cave::eShapeType::Circle:
			return mCircleShape;
		case cave::eShapeType::Edge:
			return mEdgeShape;
		default:
			break;
		}
	}
}