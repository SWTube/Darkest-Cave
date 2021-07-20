/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Object/Transform.h"
#include "CoreGlobals.h"

namespace cave
{
	Transform::Transform()
		: mLocation({.x = 0.f, .y = 0.f})
		, mRotation({.x = 0.f, .y = 0.f})
		, mScale({.x = 1.f, .y = 1.f})
	{

	}

	Transform::Transform(const Transform& other)
		: Object(other)
		, mLocation(other.mLocation)
		, mRotation(other.mRotation)
		, mScale(other.mScale)
	{

	}

	Transform::Transform(Transform&& other) noexcept
		: Object(std::move(other))
		, mLocation(std::move(other.mLocation))
		, mRotation(std::move(other.mRotation))
		, mScale(std::move(other.mScale))
	{

	}

	Transform::~Transform()
	{

	}

	Transform& Transform::operator=(const Transform& other)
	{
		Object::operator=(other);
		mLocation = other.mLocation;
		mRotation = other.mRotation;
		mScale = other.mScale;

		return *this;
	}

	Transform& Transform::operator=(Transform&& other) noexcept
	{
		Object::operator=(std::move(other));
		mLocation = other.mLocation;
		mRotation = other.mRotation;
		mScale = other.mScale;

		return *this;
	}
}