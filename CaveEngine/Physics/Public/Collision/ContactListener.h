/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Physics.h"

namespace cave
{
	class ContactListener : public b2ContactListener
	{
	public:
		ContactListener();
		virtual ~ContactListener();

		virtual void BeginContact(b2Contact* contact) override
		{
			B2_NOT_USED(contact);
		}
		virtual void EndContact(b2Contact* contact) override
		{
			B2_NOT_USED(contact);
		}
		virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
		virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override
		{
			B2_NOT_USED(contact);
			B2_NOT_USED(impulse);
		}

	protected:

	};
}