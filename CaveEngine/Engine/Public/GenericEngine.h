/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "Device/DeviceResources.h"
#include "Renderer/Renderer.h"

namespace cave
{
	class GenericEngine
	{
	public:
		GenericEngine();
		virtual ~GenericEngine() = default;

#ifdef __WIN32__
		virtual HWND GetWindowHandle() = 0;
#else
		virtual const GLFWwindow* GetWindowHandle() = 0;
#endif

		virtual int32_t CreateDesktopWindow() = 0;
		virtual int32_t Run(DeviceResources* deviceResources, Renderer* renderer) = 0;

	protected:
		const wchar_t* mWindowClassName = nullptr;
	};
}