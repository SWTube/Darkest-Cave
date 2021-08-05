/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"

namespace cave
{
	class PhysicsBody
	{
	public:
		PhysicsObject();

		b2BodyDef *GetBodyDef();

		void SetBodyDef();

		void SetType(b2BodyType objectType);
		void SetPosition(b2Vec2 objectPosition);
		void SetPosition(float x, float y);
		b2Vec2 GetPosition();

		void SetShape(b2Shape *shape);
		void SetDensity(float density);
		void SetFriction(float friction);

		void ApplyForce(b2Vec2 forceVec, b2Vec2 point, bool wake);

	private:
		b2BodyDef *mBodyDef;
		b2Body *mBody;
		b2FixtureDef mFixtureDef;
	};
}
