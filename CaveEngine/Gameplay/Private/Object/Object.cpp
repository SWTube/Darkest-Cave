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
		mOwner(this),
		mFlags(0x00000000),
		mInstanceID(0),
		mInternalIndex(0)
	{
		Log("Object::Object()");
	}

	Object::Object(const Object& other) :
		mOwner(this),
		mFlags(other.mFlags),
		mInstanceID(0),
		mInternalIndex(0)
	{
		Log("Object::Object(const Object&)");
	}

	Object::Object(Object&& other) noexcept :
		mOwner(this),
		mFlags(other.mFlags),
		mInstanceID(other.mInstanceID),
		mInternalIndex(other.mInternalIndex)
	{
		Log("Object::Object(Object&&)");
	}

	Object::~Object()
	{
		Log("Object::~Object()");
	}

	Object& Object::operator=(const Object& other)
	{
		Log("Object::operator=(const Object&)");

		mFlags = other.mFlags;
		mInstanceID = other.mInstanceID;
		mInternalIndex = other.mInternalIndex;

		return *this;
	}

	Object& Object::operator=(Object&& other) noexcept
	{
		Log("Object::operator=(Object&&)");

		mFlags = other.mFlags;
		mInstanceID = other.mInstanceID;

		return *this;
	}

	void Object::Print()
	{
		Log("Object::Print()");

		assert(mOwner != nullptr);

#ifdef _DEBUG
		std::cout << "===========================================================\n";
		std::cout << "Object[" << mInternalIndex << "]'s member\n\n";
		std::cout << "mOwner: " << mOwner << "\n";
		std::cout << "mFlags: " << mFlags << "\n";
		std::cout << "mInternalIndex: " << mInternalIndex << "\n";
		std::cout << "mInstanceID: " << mInstanceID << '\n';
#endif // _DEBUG
	}
}