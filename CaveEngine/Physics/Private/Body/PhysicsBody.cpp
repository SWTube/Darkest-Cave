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
  // Contact Filtering
  void SetCategory(int16 category)
  {
    b2Filter filter = mFixture->GetFilterData();
    filter.categoryBits = category;
    mFixture->SetFilterData(filter);
  }
  void SetMask(int16 mask)
  {
    b2Filter filter = mFixture->GetFilterData();
    filter.maskBits = mask;
    mFixture->SetFilterData(filter);
  }
  void GroupIndex(int groupIndex)
  {
    b2Filter filter = mFixture->GetFilterData();
    filter.groupIndex = groupIndex;
    mFixture->SetFilterData(filter);
  }
  void SetFilter(int16 category, int16 mask, int groupIndex)
  {
    b2Filter filter = mFixture->GetFilterData();
    filter.categoryBits = category;
    filter.maskBits = mask;
    filter.groupIndex = groupIndex;
    mFixture->SetFilterData(filter);
  }
}