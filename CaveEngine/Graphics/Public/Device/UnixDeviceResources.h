/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "GraphicsApiPch.h"
#include "Device/GenericDeviceResources.h"

#ifdef __UNIX__
namespace cave
{
	class UnixDeviceResources final : public GenericDeviceResources
	{
	public:
		constexpr UnixDeviceResources() = default;
		constexpr UnixDeviceResources(const UnixDeviceResources&) = default;
		UnixDeviceResources& operator=(const UnixDeviceResources&) = default;
		virtual ~UnixDeviceResources() = default;

		eResult Init(Window* window) override;
		eResult CreateDeviceResources() override;
		eResult CreateWindowResources(Window* window) override;
		eResult CreateWindowResources(GLFWwindow* window);
		eResult Destroy() override;

		int32_t ConfigureBackBuffer() override;
		int32_t ReleaseBackBuffer() override;
		int32_t GoFullScreen() override;
		int32_t GoWindowed() override;

		float GetAspectRatio() override;

		uint32_t GetProgram() const;
		void SetProgram(uint32_t program);
		GLFWwindow* const GetWindow() const;

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		void Present() override;
	private:
		static void errorCallback(int32_t errorCode, const char* description);

		//-----------------------------------------------------------------------------
		// OpenGL device
		//-----------------------------------------------------------------------------
		uint32_t	mProgram = 0u;
		uint32_t	mWidth = 0u;
		uint32_t	mHeight = 0u;
		GLFWwindow*	mWindow = nullptr;
	};

	typedef UnixDeviceResources DeviceResources;
}
#endif