/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Body/RigidBody.h"

namespace cave
{
	RigidBody::~RigidBody()
	{

	}
	void RigidBody::SetGravityScale(float gravityScale)
	{
		mBody->SetGravityScale(gravityScale);
	}
	void RigidBody::SetFixedRotation(bool fixedRotation)
	{
		mBody->SetFixedRotation(fixedRotation);
	}
	void RigidBody::SetAsBullet(bool isBullet)
	{
		mBody->SetBullet(isBullet);
	}
	void RigidBody::ApplyForce(const b2Vec2& force)
	{
		mBody->ApplyForce(force, mBody->GetWorldCenter(), mBody->IsAwake());
	}
	void RigidBody::ApplyForce(const b2Vec2& force, const b2Vec2& point)
	{
		mBody->ApplyForce(force, point, mBody->IsAwake());
	}
	void RigidBody::ApplyTorque(float torque)
	{
		mBody->ApplyTorque(torque, mBody->IsAwake());
	}
	void RigidBody::ApplyLinearImpulse(b2Vec2 impulse)
	{
		mBody->ApplyLinearImpulseToCenter(impulse, mBody->IsAwake());
	}
	void RigidBody::ApplyLinearImpulse(b2Vec2 impulse, b2Vec2 point)
	{
		mBody->ApplyLinearImpulse(impulse, point, mBody->IsAwake());
	}
	void RigidBody::ApplyAngularImpulse(float impulse)
	{
		mBody->ApplyAngularImpulse(impulse, mBody->IsAwake());
	}
}