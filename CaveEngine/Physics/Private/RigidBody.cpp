/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "RigidBody.h"

namespace cave
{
  void RigidBody::ApplyForce(b2Vec2 forceVec, b2Vec2 point, bool wake)
  {
    mBody->ApplyForce(forceVec, point, wake);
  }
}
