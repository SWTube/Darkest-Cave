/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"

namespace cave
{
	constexpr int32 kMaxContactPoints = 2048;

	struct ContactPoint
	{
		b2Fixture* fixtureA;
		b2Fixture* fixtureB;
		b2Vec2 normal;
		b2Vec2 position;
		b2PointState state;
		float normalImpulse;
		float tangentImpulse;
		float separation;
	};

	class ContactListener : public b2ContactListener
	{
	public:
		ContactListener();
		virtual ~ContactListener();

		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override
		{
			B2_NOT_USED(contact);
		}
		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
		virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
		{
			B2_NOT_USED(contact);
			B2_NOT_USED(impulse);
		}

		virtual ContactPoint* Step();

		virtual b2Contact* GetContacts();

	private:
		b2Body* mGroundBody;
		b2AABB mWorldAABB;
		ContactPoint mPoints[kMaxContactPoints];
		int32 mPointCount;
		b2World* mWorld;
		int32 mStepCount;
	};
}