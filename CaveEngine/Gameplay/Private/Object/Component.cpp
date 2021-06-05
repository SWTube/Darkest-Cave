/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include <cassert>

#include "Object/Component.h"

namespace cave
{
	Component::Component()
	{

	}

	Component::Component(const Component& other)
	{

	}

	Component::Component(Component&& other) noexcept :
		mTarget(other.mTarget)
	{
		other.mTarget = nullptr;
	}

	Component::~Component()
	{

	}

	Component& Component::operator=(const Component& other)
	{
		return *this;
	}

	Component& Component::operator=(Component&& other) noexcept
	{
		mTarget = other.mTarget;
		other.mTarget = nullptr;

		return *this;
	}

	void Component::SetTarget(Actor& target)
	{
		mTarget = &target;
	}

	Actor& Component::GetTarget() const
	{
		return *mTarget;
	}
}