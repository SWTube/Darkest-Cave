/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Object/PhysicsObject.h"

namespace cave
{
	void PhysicsObject::SetShape(b2Shape* shape)
	{
		mFixtureDef.shape = shape;
	}
	void PhysicsObject::SetDensity(float density)
	{
		mFixtureDef.density = density;
	}
	void PhysicsObject::SetFriction(float friction)
	{
		mFixtureDef.friction = friction;
	}
	void PhysicsObject::ApplyForce(b2Vec2 forceVec, b2Vec2 point, bool wake)
	{
		mBody->ApplyForce(forceVec, point, wake);
	}
	void PhysicsObject::SetType(b2BodyType objectType)
	{
		mBodyDef->type = objectType;
	}
	void PhysicsObject::SetPosition(b2Vec2 objectPosition)
	{
		mBodyDef->position.Set(objectPosition.x, objectPosition.y);
	}
	void PhysicsObject::SetPosition(float x, float y)
	{
		mBodyDef->position.Set(x, y);
	}
}
