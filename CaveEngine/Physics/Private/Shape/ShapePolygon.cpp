/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Shape/ShapePolygon.h"

namespace cave
{
	ShapePolygon::ShapePolygon()
	{
		mPolygonShape = b2PolygonShape();
		mPolygonShape.SetAsBox(1.f, 1.f);
	}

	ShapePolygon::~ShapePolygon()
	{

	}

	b2PolygonShape& ShapePolygon::GetShape()
	{
		return mPolygonShape;
	}
}