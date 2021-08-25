/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Body/PhysicsBody.h"

namespace cave
{
  PhysicsBody::PhysicsBody()
  {

  }
  PhysicsBody::~PhysicsBody()
  {

  }
  void PhysicsBody::SetPosition(float x, float y)
  {

  }
  void PhysicsBody::SetPosition(b2Vec2 position)
  {
	  
  }
  b2Vec2 PhysicsBody::GetPosition()
  {
	  return mBody->GetPosition();
  }
  b2BodyDef* PhysicsBody::GetBodyDef()
  {
	  return &mBodyDef;
  }
  b2Body* PhysicsBody::GetBody()
  {
	  return mBody;
  }
  void PhysicsBody::SetBody(b2Body* body)
  {
  }
}