/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"
#include <vector>

namespace cave
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld(b2Vec2 gravity);
		~PhysicsWorld();

		void AddPhysicsObject(PhysicsObject* physicsObject);

		void Step();

	private:
		b2Vec2 mGravity;
		b2World mWorld;
		std::vector<PhysicsObject*> mPhysicsObjects;

		float timeStep = 1.0f / 60.0f;
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
	};
}

