/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Body/RigidBody.h"

namespace cave
{
	RigidBody::RigidBody()
	{
		
	}
	RigidBody::~RigidBody()
	{

	}
	void RigidBody::ApplyForce(b2Vec2 force, b2Vec2 point)
	{
		mBody->ApplyForce(force, mBody->GetWorldCenter(), mBody->IsAwake());
	}
}