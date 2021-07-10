/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include <cassert>

#include "Object/Component.h"

namespace cave
{
	Component::Component() :
		mComponentType(eComponentType::NONE)
	{

	}

	Component::Component(eComponentType type) :
		mComponentType(type)
	{

	}

	Component::Component(const Component& other) :
		mComponentType(other.mComponentType)
	{

	}

	Component::Component(Component&& other) noexcept :
		mComponentType(other.mComponentType)
	{
		
	}

	Component::~Component()
	{

	}

	Component& Component::operator=(const Component& other)
	{
		mComponentType = other.mComponentType;
		return *this;
	}

	Component& Component::operator=(Component&& other) noexcept
	{
		mComponentType = other.mComponentType;
		return *this;
	}
}