/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Object/Object.h"

namespace cave
{
	uint32_t Object::mNextGUID = 1;

	Object::Object(std::string& name)
		: mDuplicatedTarget(nullptr)
		, mDuplicatedNum(1)
		, mName(name)
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(const char* name)
		: mDuplicatedTarget(nullptr)
		, mDuplicatedNum(1)
		, mName(name)
	{
		assert((name != nullptr) & (mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		assert(IsValid());
		++mNextGUID;
	}

	Object::Object(const Object& other)
		: mDuplicatedNum(1)
	{
		assert((mNextGUID > 0) & (mNextGUID <= UINT32_MAX));
		mGUID = mNextGUID;
		Object* iter = &const_cast<Object&>(other);
		while (iter->mDuplicatedTarget != nullptr)
		{
			iter = iter->mDuplicatedTarget;
		}
		mDuplicatedTarget = iter;
		mName = other.mName + std::to_string(++(mDuplicatedTarget->mDuplicatedNum));
		assert(GetGUID() != other.GetGUID());
		++mNextGUID;
	}

	Object::~Object()
	{
		assert(IsValid());
		if (IsDuplicated())
		{
			--(mDuplicatedTarget->mDuplicatedNum);
			mDuplicatedTarget = nullptr;
		}

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

	uint32_t Object::getDuplicatedNum() const
	{
		return mDuplicatedNum;
	}
}