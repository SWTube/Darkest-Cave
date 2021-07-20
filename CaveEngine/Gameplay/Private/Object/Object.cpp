/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "CoreGlobals.h"
#include "Object/Obejct.h"

namespace cave
{
	int Object::mNextGUID = 0;

	Object::Object()
		: mName()
	{
		assert(mNextGUID >= 0);
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(std::string& name)
		: mName(name)
	{
		assert(mNextGUID >= 0);
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(const char* name)
		: mName(name)
	{
		assert(name != nullptr);
		assert(mNextGUID >= 0);
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(const Object& other)
		: mName(other.mName)
	{
		assert(mNextGUID >= 0);
		mGUID = mNextGUID;
		assert(GetGUID() != other.GetGUID());
		++mNextGUID;
	}

	Object::Object(Object&& other) noexcept
		: mName(std::move(other.GetName()))
	{
		assert(mNextGUID >= 0);
		mGUID = mNextGUID;
		assert(GetGUID() != other.GetGUID());
		++mNextGUID;
	}

	Object::~Object()
	{
		assert(IsValid());
		mGUID = -1;
	}

	Object& Object::operator=(const Object& other)
	{
		assert(GetGUID() != other.GetGUID());
		mName = other.mName;

		return *this;
	}

	Object& Object::operator=(Object&& other) noexcept
	{
		assert(GetGUID() != other.GetGUID());

		return *this;
	}

	void Object::SetName(std::string& name)
	{
		assert(IsValid());
		mName = name;
	}

	void Object::SetName(const char* name)
	{
		assert(IsValid());
		assert(name != nullptr);
		mName = name;
	}
}