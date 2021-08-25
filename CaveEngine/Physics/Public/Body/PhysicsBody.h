/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"

namespace cave
{
    class PhysicsBody
    {
    public:
        PhysicsBody();
        ~PhysicsBody();

        void SetPosition(float x, float y);
        void SetPosition(b2Vec2 position);
        b2Vec2 GetPosition();

        b2BodyDef* GetBodyDef();

        b2Body* GetBody();
        void SetBody(b2Body* body);
    protected:
        b2BodyDef mBodyDef;
        b2Body* mBody;
    };
};
