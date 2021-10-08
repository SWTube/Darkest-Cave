/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "Assertion/Assert.h"

import cave.Core.Types.Float;

namespace cave
{
	class Transform final
	{
	public:
		Transform();
		Transform(const Transform& other);
		Transform(Transform&& other) noexcept;

		~Transform();
		Transform& operator=(const Transform& other);
		Transform& operator=(Transform&& other) noexcept;

		Float2* GetPosition() const;
		Float2* GetRotation() const;
		Float2* GetScale() const;

	private:
		Float2* mPosition;
		Float2* mRotation;
		Float2* mScale;
	};
}