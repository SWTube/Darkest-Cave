/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "Object/Obejct.h"

namespace cave
{
	enum eComponentType : char
	{
		NONE = -1,
		RENDERER = 0,
		RIGIDBODY = 1,
		COLLIDER = 2,
		AUDIO = 3,
		AI = 4,
	};

	class Component : public Object
	{
	public:
		Component(eComponentType type);
		Component(const Component& other);
		Component(Component&& other) noexcept;

		virtual ~Component();
		Component& operator=(const Component& other);
		Component& operator=(Component&& other) noexcept;

		__forceinline eComponentType GetComponentType() const
		{
			return mComponentType;
		}

	protected:
		Component();

		__forceinline void SetComponentType(eComponentType componentType)
		{
			mComponentType = componentType;
		}

	private:
		eComponentType mComponentType;
	};

}