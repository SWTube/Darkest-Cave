/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "Device/Window.h"

namespace cave
{
	class GenericDeviceResources
	{
	public:
		constexpr GenericDeviceResources() = default;
		constexpr GenericDeviceResources(const GenericDeviceResources&) = default;
		GenericDeviceResources& operator=(const GenericDeviceResources&) = default;
		virtual ~GenericDeviceResources() = default;

		virtual eResult Init(Window* window) = 0;
		virtual eResult CreateWindowResources(Window* window) = 0;
		virtual eResult CreateDeviceResources() = 0;
		virtual void Destroy() = 0;

		virtual int32_t ConfigureBackBuffer() = 0;
		virtual int32_t ReleaseBackBuffer() = 0;
		virtual int32_t GoFullScreen() = 0;
		virtual int32_t GoWindowed() = 0;

		virtual float GetAspectRatio() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Present() = 0;
	};
}