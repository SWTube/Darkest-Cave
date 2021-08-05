/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"

namespace cave
{
	class RigidBody : public PhysicsBody
	{
	public:
		RigidBody();

		void SetDensity(float density);
		void SetFriction(float friction);

		void ApplyForce(b2Vec2 forceVec, b2Vec2 point, bool wake);
	};
}
