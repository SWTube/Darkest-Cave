/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"

namespace cave
{
	class ShapeCircle
	{
	public:
		ShapeCircle();

		~ShapeCircle();

		b2CircleShape& GetShape();

	private:
		b2CircleShape mCircleShape;
	};
}