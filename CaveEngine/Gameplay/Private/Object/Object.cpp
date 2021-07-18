/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Object/Obejct.h"
#include "Memory/MemoryPool.h"

namespace cave
{
	int Object::mNextGUID = 0;

	Object::Object()
	{
		assert(mNextGUID >= 0);
		mGUID = mNextGUID;
		++mNextGUID;
	}

	Object::Object(const Object& other)
		: mFlags(other.mFlags)
	{
		assert(mNextGUID >= 0);
		mGUID = mNextGUID;
		++mNextGUID;
	}

	Object::Object(Object&& other)
		: mFlags(other.GetFlags())
	{
		assert(mGUID >= 0);
		mGUID = mNextGUID;
		++mGUID;
	}

	Object::~Object()
	{
		assert(IsValid());
		mFlags = 0;
		mGUID = -1;
	}

	Object& Object::operator=(const Object& other)
	{
		assert(other.IsValid());
		mFlags = other.GetFlags();

		return *this;
	}

	Object& Object::operator=(Object&& other)
	{
		assert(other.IsValid());
		mFlags = other.GetFlags();
		mGUID = other.GetGUID();

		return *this;
	}

	int Object::GetGUID() const
	{
		assert(IsValid());
		return mGUID;
	}

	void Object::SetFlags(unsigned char flags)
	{
		mFlags = flags;
	}

	unsigned char Object::GetFlags() const
	{
		assert(IsValid());
		return mFlags;
	}

	bool Object::IsValid() const
	{
		return mGUID == -1 ? false : true;
	}
}