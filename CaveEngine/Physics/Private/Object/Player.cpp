/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Object/Player.h"

namespace cave
{
	void Player::Move(b2Vec2 movementVec)
	{
		
	}
	void Player::Jump(b2Vec2 forceVec)
	{
		mPhysicsObject.ApplyForce(forceVec);
	}
}
