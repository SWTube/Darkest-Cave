/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "PhysicsBody.h"

namespace cave
{
  void PhysicsBody::SetShape(b2Shape *shape)
  {
    mFixtureDef.shape = shape;
  }
  void PhysicsBody::SetType(b2BodyType objectType)
  {
    mBodyDef->type = objectType;
  }
  void PhysicsBody::SetPosition(b2Vec2 objectPosition)
  {
    mBodyDef->position.Set(objectPosition.x, objectPosition.y);
  }
  void PhysicsBody::SetPosition(float x, float y)
  {
    mBodyDef->position.Set(x, y);
  }
  b2Vec2 PhysicsBody::GetPosition()
  {
    return mBody->GetPosition();
  }
  void PhysicsBody::SetDensity(float density)
  {
    mFixtureDef.density = density;
  }
  void PhysicsBody::SetFriction(float friction)
  {
    mFixtureDef.friction = friction;
  }
  void PhysicsBody::AddChild(PhysicsBody* child)
  {
    mChildren.push_back(child);
  }
  std::vector<PhysicsBody*> PhysicsBody::GetChildren()
  {
    return mChildren;
  }
}
