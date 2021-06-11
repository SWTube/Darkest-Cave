/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "Object/Obejct.h"

namespace cave
{
	class Actor;

	class Component : public Object
	{
	public:
		Component();
		Component(const Component& other);
		Component(Component&& other) noexcept;

		virtual ~Component();
		Component& operator=(const Component& other);
		Component& operator=(Component&& other) noexcept;

	private:
		
	};

}