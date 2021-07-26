/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"

namespace cave
{
	class PhysicsObject
	{
	public:
		PhysicsObject();

		b2BodyDef* GetBodyDef();
		b2FixtureDef* GetFixtureDef();

		void SetBodyDef();

		// bodyDef properties
		void SetType(b2BodyType objectType);
		void SetPosition(b2Vec2 objectPosition);
		void SetPosition(float x, float y);

		// b2FixtureDef properties
		void SetShape(b2Shape* shape);
		void SetDensity(float density);
		void SetFriction(float friction);

		// PhysicsObject methods
		void ApplyForce(b2Vec2 forceVec, b2Vec2 point, bool wake);

	private:
		b2BodyDef mBodyDef;
		b2FixtureDef mFixtureDef;
	};
}

