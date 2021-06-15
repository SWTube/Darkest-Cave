/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "Object/Obejct.h"

namespace cave
{
	enum class eComponentType : unsigned char
	{
		Graphics = 0,
		Physics = 1,
		AI = 2,
		Audio = 3,
	};

	class Component : public Object
	{
	public:
		Component();
		Component(const Component& other);
		Component(Component&& other) noexcept;

		virtual ~Component();
		Component& operator=(const Component& other);
		Component& operator=(Component&& other) noexcept;

		__forceinline eComponentType GetComponentType()
		{
			return mComponentType;
		}

	protected:
		__forceinline void SetComponentType(eComponentType componentType)
		{
			mComponentType = componentType;
		}

	private:
		eComponentType mComponentType;
	};

}