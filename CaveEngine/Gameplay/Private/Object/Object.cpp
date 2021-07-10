/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include <cassert>
#include <iostream>

#include "Object/Obejct.h"
#include "Tmp/Log.h"

namespace cave
{
	Object::Object() :
		mbVaild(true)
	{
		
	}

	Object::Object(const Object& other) :
		mFlags(other.mFlags),
		mbVaild(true)
	{

	}

	Object::Object(Object&& other) noexcept :
		mFlags(other.mFlags),
		mInstanceID(other.mInstanceID),
		mbVaild(true)
	{

	}

	Object::~Object()
	{
	
	}

	Object& Object::operator=(const Object& other)
	{
		mFlags = other.mFlags;

		return *this;
	}

	Object& Object::operator=(Object&& other) noexcept
	{
		mFlags = other.mFlags;
		mInstanceID = other.mInstanceID;

		return *this;
	}
}