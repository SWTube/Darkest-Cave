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
	PhysicsBody::PhysicsBody(ePhysicsType type)
  {
	  SetType(type);
  }
  PhysicsBody::~PhysicsBody()
  {
	  mBody->DestroyFixture(mFixture);
  }
  ePhysicsType PhysicsBody::GetType()
  {
	  b2BodyType type = mBodyDef.type;
	  if (type == b2_staticBody) return ePhysicsType::Static;
	  else if (type == b2_dynamicBody) return ePhysicsType::Dynamic;
	  else if (type == b2_kinematicBody) return ePhysicsType::Kinematic;
  }
  void PhysicsBody::SetType(ePhysicsType type)
  {
	  if (type == ePhysicsType::Static) mBodyDef.type = b2_staticBody;
	  else if (type == ePhysicsType::Dynamic) mBodyDef.type = b2_dynamicBody;
	  else if (type == ePhysicsType::Kinematic) mBodyDef.type = b2_kinematicBody;
  }
  b2Transform PhysicsBody::GetTransform()
  {
	  return mBody->GetTransform();
  }
  void PhysicsBody::SetTransform(b2Vec2 position, float angle)
  {
	  mBody->SetTransform(position, angle);
  }
  b2Vec2 PhysicsBody::GetPosition()
  {
	  return mBody->GetPosition();
  }
  void PhysicsBody::SetPosition(float x, float y)
  {
	  mBodyDef.position.Set(x, y);
  }
  void PhysicsBody::SetPosition(b2Vec2 position)
  {
	  mBodyDef.position = position;
  }
  float PhysicsBody::GetAngle()
  {
	  return mBody->GetAngle();
  }
  void PhysicsBody::SetAngle(float angle)
  {
	  mBodyDef.angle = angle;
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
	  mBody = body;
  }
  b2FixtureDef PhysicsBody::GetFixtureDef()
  {
	  return mFixtureDef;
  }
  b2Fixture* PhysicsBody::GetFixture()
  {
	  return mFixture;
  }
  void PhysicsBody::SetFixture(b2Fixture* fixture)
  {
	  mFixture = fixture;
  }
  void PhysicsBody::CreateFixture()
  {
	  mFixture = mBody->CreateFixture(&mFixtureDef);
  }
  float PhysicsBody::GetDensity()
  {
	  return mFixture->GetDensity();
  }
  b2Shape* PhysicsBody::GetShape()
  {
	  return mFixture->GetShape();
  }
  void PhysicsBody::SetShape()
  {
	  // TODO. temp code. change to Shape.h we made.
	  b2PolygonShape s;
	  s.SetAsBox(1.0f, 1.0f);
	  mFixtureDef.shape = &s;
	  mFixtureDef.density = 1.0f;
	  mFixtureDef.friction = 0.5f;
  }
  void PhysicsBody::SetDensity(float density)
  {
	  mFixture->SetDensity(density);
	  mBody->ResetMassData();
  }
  float PhysicsBody::GetFriction()
  {
	  return mFixture->GetFriction();
  }
  void PhysicsBody::SetFriction(float friction)
  {
	  mFixture->SetFriction(friction);
  }
  void PhysicsBody::SetAllowSleep(bool allowSleep)
  {
	  mBodyDef.allowSleep = allowSleep;
  }
  bool PhysicsBody::IsAwake()
  {
	  return mBody->IsAwake();
  }
  void PhysicsBody::SetAwake(bool awake)
  {
	  mBody->SetAwake(awake);
  }
}