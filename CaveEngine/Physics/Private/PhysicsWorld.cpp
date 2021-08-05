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
	void PhysicsWorld::AddPhysicsBody(PhysicsBody* physicsBody)
	{
		// add bodyDef, fixtureDef to physics world
		b2Body* body = mWorld.CreateBody(physicsBody->GetBodyDef());
		body->CreateFixture(physicsBody->GetFixtureDef());
		// set body on physics object
		physicsBody->SetBody(body);
	}
	void PhysicsWorld::Step()
	{
		mWorld.Step(mTimeStep, mVelocityIterations, mPositionIterations);
	}
}