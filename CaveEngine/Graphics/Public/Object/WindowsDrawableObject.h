/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreMinimal.h"
#include "Object/GenericDrawableObject.h"

#ifdef __WIN32__
namespace cave
{
	class WindowsDrawableObject final : public GenericDrawableObject
	{
	public:
		WindowsDrawableObject() = delete;
		constexpr WindowsDrawableObject(uint32_t verticesCount, float*&& vertices, uint32_t indicesCount, float*&& indices);
		constexpr WindowsDrawableObject(const WindowsDrawableObject& object);
		constexpr WindowsDrawableObject(const WindowsDrawableObject&& object);
		constexpr WindowsDrawableObject& operator=(const WindowsDrawableObject& object);
		constexpr WindowsDrawableObject& operator=(const WindowsDrawableObject&& object);
		virtual ~WindowsDrawableObject();
	};

	typedef WindowsDrawableObject DrawableObject;
} // namespace cave
#endif