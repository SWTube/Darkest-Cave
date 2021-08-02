/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"

namespace cave
{
	enum class ePhysicsObjectTypes {
		STATIC,
		DYNAMIC,
		KINEMATIC
	};

	class PhysicsObject
	{
	public:
		PhysicsObject();

		b2BodyDef* GetBodyDef();
		b2FixtureDef* GetFixtureDef();

		b2Body* GetBody();

		// set body from physics world
		void SetBody(b2Body* body);

		// bodyDef properties
		b2Vec2 GetPosition();

		void SetType(ePhysicsObjectTypes physicsObjectType);
		void SetPosition(b2Vec2 objectPosition);

		// b2FixtureDef properties
		void SetShape(b2Shape* shape);
		void SetDensity(float density);
		void SetFriction(float friction);

		// PhysicsObject methods
		void ApplyForce(b2Vec2 forceVec, b2Vec2 point, bool wake);

		// PhysicsObject child
		void AddChild(PhysicsObject* physicsObject);

	private:
		bool hasBody();

		b2BodyDef mBodyDef;
		b2FixtureDef mFixtureDef;
		b2Body* mBody;
	};
}

