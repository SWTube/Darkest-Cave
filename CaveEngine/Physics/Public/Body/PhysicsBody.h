/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"

namespace cave
{
    enum class ePhysicsBodyType
    {
        Static,
        Dynamic,
        Kinematic
    };

    class PhysicsBody
    {
    public:
        PhysicsBody();
        ~PhysicsBody();

        ePhysicsBodyType GetType();
        void SetType(ePhysicsBodyType type);

        b2Vec2 GetPosition();
        void SetPosition(float x, float y);
        void SetPosition(b2Vec2 position);

        b2BodyDef* GetBodyDef();

        b2Body* GetBody();
        void SetBody(b2Body* body);

        b2Fixture* GetFixture();

        b2Shape* GetShape();
        void SetShape(); // TODO. change to Shape.h we made.

        float GetDensity();
        void SetDensity(float density);

        float GetFriction();
        void SetFriction(float friction);

        void SetAllowSleep(bool allowSleep);

        bool IsAwake();
        void SetAwake(bool awake);
    protected:
        b2BodyDef mBodyDef;
        b2Body* mBody;
        b2FixtureDef mFixtureDef;
        b2Fixture* mFixture;
    };
};
