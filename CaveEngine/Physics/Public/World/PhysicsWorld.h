/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"
#include "Body/PhysicsBody.h"

namespace cave
{
    class PhysicsWorld
    {
    public:
        PhysicsWorld(b2Vec2 gravity);
        ~PhysicsWorld();

        void SetGravity(b2Vec2 gravity);
        b2Vec2 GetGravity();

        void AddChild(PhysicsBody* physicsBody);

        void Update(float step, float velocityIterations, float positionIterations);
    private:
        b2World* mWorld;
    };
};