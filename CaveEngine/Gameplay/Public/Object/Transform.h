/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "CoreTypes.h"
#include "Assertion/Assert.h"
#include "Object/Object.h"
#include "Containers/Vertex.h"

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

		FORCEINLINE Float2* GetPosition();
		FORCEINLINE Float2* GetRotation();
		FORCEINLINE Float2* GetScale();

	private:
		Float2 mPosition;
		Float2 mRotation;
		Float2 mScale;
	};

	FORCEINLINE Float2* Transform::GetPosition()
	{
		assert(IsValid());
		return &mPosition;
	}

	FORCEINLINE Float2* Transform::GetRotation()
	{
		assert(IsValid());
		return &mRotation;
	}

	FORCEINLINE Float2* Transform::GetScale()
	{
		assert(IsValid());
		return &mScale;
	}
#ifdef CAVE_BUILD_DEBUG
	namespace TransformTest
	{
		void Test();
	}
#endif //CAVE_BUILD_DEBUG
}