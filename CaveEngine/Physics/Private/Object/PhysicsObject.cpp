/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Object/PhysicsObject.h"

namespace cave
{
	PhyscisObject::PhysicsObject()
	{
		
	}
	b2BodyDef* PhysicsObject::GetBodyDef()
	{
		return &mBodyDef;
	}
	b2FixtureDef* PhyscisObject::GetFixtureDef()
	{
		return &mFixtureDef;
	}
	// b2BodyDef properties
	void PhysicsObject::SetType(ePhysicsObjectTypes objectType)
	{
		if (objectType == ePhysicsObjectTypes::STATIC)
		{
			mBodyDef.type = b2_staticBody;
		}
		else if (objectType == ePhysicsObjectTypes::DYNAMIC)
		{
			mBodyDef.type = b2_dynamicBody;
		}
		else if (objectType == ePhysicsObjectTypes::KINEMATIC)
		{
			mBodyDef.type = b2_kinematicBody;
		}
	}
	void PhysicsObject::SetPosition(b2Vec2 objectPosition)
	{
		mBodyDef.position.Set(objectPosition.x, objectPosition.y);
	}
	// b2FixtureDef properties
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
	// PhysicsObject methods
	void PhysicsObject::ApplyForce(b2Vec2 forceVec, b2Vec2 point, bool wake)
	{
		mBody->ApplyForce(forceVec, point, wake);
	}
}
