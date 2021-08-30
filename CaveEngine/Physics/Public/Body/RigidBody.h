/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"
#include "PhysicsBody.h"

namespace cave
{
    class RigidBody : public PhysicsBody
    {
    public:
        RigidBody(ePhysicsType type) : PhysicsBody(type) {};
        ~RigidBody();

        void SetGravityScale(float gravityScale);
        void SetFixedRotation(bool fixedRotation);
        void SetAsBullet(bool isBullet);
        
        void ApplyForce(const b2Vec2& force);
        void ApplyForce(const b2Vec2& force, const b2Vec2& point);
        void ApplyTorque(float torque);
        void ApplyLinearImpulse(b2Vec2 impulse);
        void ApplyLinearImpulse(b2Vec2 impulse, b2Vec2 point);
        void ApplyAngularImpulse(float impulse);
    };
};