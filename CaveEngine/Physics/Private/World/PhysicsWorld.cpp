/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "World/PhysicsWorld.h"

namespace cave
{
	PhysicsWorld::PhysicsWorld(b2Vec2 gravity)
	{
		mWorld = new b2World(gravity);
	}
	PhysicsWorld::~PhysicsWorld()
	{
		delete mWorld;
	}
	void PhysicsWorld::SetGravity(b2Vec2 gravity)
	{
		mWorld->SetGravity(gravity);
	}
	b2Vec2 PhysicsWorld::GetGravity()
	{
		return mWorld->GetGravity();
	}
	void PhysicsWorld::AddPhysicsObject(PhysicsBody* physicsBody)
	{
		physicsBody->SetBody(mWorld->CreateBody(physicsBody->GetBodyDef()));
	}
	void PhysicsWorld::SetContactListener(ContactListener* listener)
	{
		mWorld->SetContactListener(listener);
	}
	void PhysicsWorld::Update(float step, float velocityIterations, float positionIterations)
	{
		mWorld->Step(step, velocityIterations, positionIterations);
	}
}