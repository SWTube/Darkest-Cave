/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "CoreTypes.h"
#include "Assertion/Assert.h"
#include "Object/Obejct.h"
#include "Math/Vector2.h"

namespace cave
{
	class Transform final : public Object
	{
	public:
		Transform();
		Transform(const Transform& other);
		Transform(Transform&& other) noexcept;

		~Transform();
		Transform& operator=(const Transform& other);
		Transform& operator=(Transform&& other) noexcept;

		FORCEINLINE Vector2* GetLocation();
		FORCEINLINE Vector2* GetRotation();
		FORCEINLINE Vector2* GetScale();

	private:
		Vector2 mLocation;
		Vector2 mRotation;
		Vector2 mScale;
	};

	FORCEINLINE Vector2* Transform::GetLocation()
	{
		assert(IsValid());
		return &mLocation;
	}

	FORCEINLINE Vector2* Transform::GetRotation()
	{
		assert(IsValid());
		return &mRotation;
	}

	FORCEINLINE Vector2* Transform::GetScale()
	{
		assert(IsValid());
		return &mScale;
	}
}