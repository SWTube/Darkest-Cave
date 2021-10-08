/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Object/Transform.h"
#include "CoreGlobals.h"

namespace cave
{
	Transform::Transform()
		: mPosition(new Float2())
		, mRotation(new Float2())
		, mScale(new Float2())
	{

	}

	Transform::Transform(const Transform& other)
		: mPosition(new Float2(*other.mPosition))
		, mRotation(new Float2(*other.mRotation))
		, mScale(new Float2(*other.mScale))
	{

	}

	Transform::Transform(Transform&& other) noexcept
		: mPosition(other.mPosition)
		, mRotation(other.mRotation)
		, mScale(other.mScale)
	{
		other.mPosition = nullptr;
		other.mRotation = nullptr;
		other.mScale = nullptr;
	}

	Transform::~Transform()
	{
		if (mPosition != nullptr)
		{
			delete mPosition;
		}

		if (mRotation != nullptr)
		{
			delete mRotation;
		}

		if (mScale != nullptr)
		{
			delete mScale;
		}
	}

	Transform& Transform::operator=(const Transform& other)
	{
		*mPosition = *other.mPosition;
		*mRotation = *other.mRotation;
		*mScale = *other.mScale;

		return *this;
	}

	Transform& Transform::operator=(Transform&& other) noexcept
	{
		mPosition = other.mPosition;
		mRotation = other.mRotation;
		mScale = other.mScale;
		
		other.mPosition = nullptr;
		other.mRotation = nullptr;
		other.mScale = nullptr;

		return *this;
	}

	Float2* Transform::GetPosition() const
	{
		assert(mPosition != nullptr);
		return mPosition;
	}

	Float2* Transform::GetRotation() const
	{
		assert(mRotation != nullptr);
		return mRotation;
	}

	Float2* Transform::GetScale() const
	{
		return mScale;
	}
}