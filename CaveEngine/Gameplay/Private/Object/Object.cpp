/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Object/Obejct.h"

namespace cave
{
	uint32_t Object::mNextGUID = 1;

	Object::Object()
		: mName()
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(std::string& name)
		: mName(name)
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(const char* name)
		: mName(name)
	{
		assert((name != nullptr) & (mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(const Object& other)
		: mName(other.GetName())
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(GetGUID() != other.GetGUID());
		++mNextGUID;
	}

	Object::Object(Object&& other) noexcept
		: mName(other.GetName())
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(GetGUID() != other.GetGUID());
		++mNextGUID;
	}

	Object::~Object()
	{
		assert(IsValid());
		mGUID = 0;
	}

	Object& Object::operator=(const Object& other)
	{
		assert(GetGUID() != other.GetGUID());
		return *this;
	}

	Object& Object::operator=(Object&& other) noexcept
	{
		assert(GetGUID() != other.GetGUID());
		return *this;
	}
}