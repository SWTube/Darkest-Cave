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

		int32_t CreateDeviceResources() override;
		int32_t CreateWindowResources(GLFWwindow* window) override;
		int32_t CreateWindowResources();
		void Destroy() override;

		int32_t ConfigureBackBuffer() override;
		int32_t ReleaseBackBuffer() override;
		int32_t GoFullScreen() override;
		int32_t GoWindowed() override;

		float GetAspectRatio() override;

		uint32_t GetProgram() const;
		void SetProgram(uint32_t program);
		GLFWwindow* const GetWindow() const;

		void Present() override;
	private:
		static void errorCallback(int32_t errorCode, const char* description);

		static void windowSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
		static void keyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);
		static void charCallback(GLFWwindow* window, uint32_t codepoint);

		static char glfwKeyToChar(int32_t key);

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