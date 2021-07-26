/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "PhysicsWorld.h"

namespace cave
{
	PhysicsWorld::PhysicsWorld(b2Vec2 gravity)
	{
		mWorld = b2World(gravity);
	}
	PhysicsWorld::~PhysicsWorld()
	{
	}
	void PhysicsWorld::AddPhysicsObject(PhysicsObject* physicsObject)
	{
		mWorld.CreateBody(physicsObject->GetBodyDef());
		mPhysicsObjects.push_back(physicsObject);
	}
	void PhysicsWorld::Step()
	{
		mWorld.Step(timeStep, velocityIterations, positionIterations);
	}
}