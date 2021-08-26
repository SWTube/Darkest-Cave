/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "Physics.h"

export module ShapeCircle;

namespace cave
{
	export class ShapeCircle final
	{
	public:
		ShapeCircle();

		~ShapeCircle();

		b2CircleShape& GetShape();

	private:
		b2CircleShape mCircleShape;
	};

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