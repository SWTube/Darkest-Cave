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
	void PhysicsWorld::SetGravity(b2Vec2 gravity)
	{
		mWorld.SetGravity(gravity);
	}
	void PhysicsWorld::SetTimeStep(float timeStep)
	{
		mTimeStep = timeStep;
	}
	void PhysicsWorld::AddPhysicsObject(PhysicsObject* physicsObject)
	{
		// add bodyDef, fixtureDef to physics world
		b2Body* physicsBody = mWorld.CreateBody(physicsObject->GetBodyDef());
		physicsBody->CreateFixture(physicsObject->GetFixtureDef());
		// set body on physics object
		physicsObject->SetBody(physicsBody);
		// push physics object
		mPhysicsObjects.push_back(physicsObject);
	}
	void PhysicsWorld::Step()
	{
		mWorld.Step(mTimeStep, mVelocityIterations, mPositionIterations);
	}
}