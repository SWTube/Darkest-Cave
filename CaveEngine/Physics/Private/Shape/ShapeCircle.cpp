/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Shape/ShapeCircle.h"

namespace cave
{
	ShapeCircle::ShapeCircle()
	{
		mCircleShape = b2CircleShape();

	}

	ShapeCircle::~ShapeCircle()
	{

	}

	b2CircleShape& ShapeCircle::GetShape()
	{
		return mCircleShape;
	}
}