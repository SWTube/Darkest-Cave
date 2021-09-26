/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Collision/ContactListener.h"

namespace cave
{
	ContactListener::ContactListener()
	{
		b2Vec2 gravity;
		gravity.Set(0.0f, -10.0f);
		mWorld = new b2World(gravity);
		mPointCount = 0;

		mWorld->SetContactListener(this);

		mStepCount = 0;

		b2BodyDef bodyDef;
		mGroundBody = mWorld->CreateBody(&bodyDef);
	}

	ContactListener::~ContactListener()
	{
		delete mWorld;
		mWorld = NULL;
	}

	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		b2Body* bodyA = fixtureA->GetBody();
		b2Body* bodyB = fixtureB->GetBody();
	}

	void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		const b2Manifold* manifold = contact->GetManifold();

		if (manifold->pointCount == 0)
		{
			return;
		}

		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
		b2GetPointStates(state1, state2, oldManifold, manifold);

		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);

		for (int32 i = 0; i < manifold->pointCount && mPointCount < kMaxContactPoints; ++i)
		{
			ContactPoint* cp = mPoints + mPointCount;
			cp->fixtureA = fixtureA;
			cp->fixtureB = fixtureB;
			cp->position = worldManifold.points[i];
			cp->normal = worldManifold.normal;
			cp->state = state2[i];
			cp->normalImpulse = manifold->points[i].normalImpulse;
			cp->tangentImpulse = manifold->points[i].tangentImpulse;
			cp->separation = worldManifold.separations[i];
			++mPointCount;
		}
	}

	ContactPoint* ContactListener::Step()
	{
		return mPoints;
	}
}