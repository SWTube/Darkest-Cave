/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "GraphicsApiPch.h"

namespace cave
{
	class GenericDeviceResources
	{
	public:
		constexpr GenericDeviceResources() = default;
		constexpr GenericDeviceResources(const GenericDeviceResources&) = default;
		GenericDeviceResources& operator=(const GenericDeviceResources&) = default;
		virtual ~GenericDeviceResources() = default;

#ifdef __WIN32__
		virtual int32_t CreateDeviceResources(HWND window) = 0;
		virtual int32_t CreateWindowResources(HWND window) = 0;
#else
		virtual int32_t CreateDeviceResources(GLFWwindow* window) = 0;
		virtual int32_t CreateWindowResources(GLFWwindow* window) = 0;
#endif
		virtual int32_t CreateDeviceResources() = 0;

		virtual int32_t ConfigureBackBuffer() = 0;
		virtual int32_t ReleaseBackBuffer() = 0;
		virtual int32_t GoFullScreen() = 0;
		virtual int32_t GoWindowed() = 0;

		virtual float GetAspectRatio() = 0;

		virtual void Present() = 0;
	};
}