/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Object/WindowsDrawableObject.h"

#ifdef __WIN32__
namespace cave
{
	constexpr WindowsDrawableObject::WindowsDrawableObject(uint32_t verticesCount, float*&& vertices, uint32_t indicesCount, float*&& indices)
		: GenericDrawableObject(verticesCount, std::move(vertices), indicesCount, std::move(indices))
	{
	}

	constexpr WindowsDrawableObject::WindowsDrawableObject(const WindowsDrawableObject& object);
	constexpr WindowsDrawableObject::WindowsDrawableObject(const WindowsDrawableObject&& object);
	constexpr WindowsDrawableObject::WindowsDrawableObject& operator=(const WindowsDrawableObject& object);
	constexpr WindowsDrawableObject::WindowsDrawableObject& operator=(const WindowsDrawableObject&& object);
	virtual WindowsDrawableObject::~WindowsDrawableObject();
} // namespace cave

#endif