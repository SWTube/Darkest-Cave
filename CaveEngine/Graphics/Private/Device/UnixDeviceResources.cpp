/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Device/UnixDeviceResources.h"

namespace cave
{
	int32_t UnixDeviceResources::CreateDeviceResources(GLFWwindow* window)
	{
		int32_t result = GLFW_NO_ERROR;

		int32_t glfwInitResult = glfwInit();
		if (glfwInitResult == GLFW_FALSE)
		{
			glfwTerminate();
			return glfwInitResult;
		}

		return result;
	}

	int32_t UnixDeviceResources::CreateDeviceResources()
	{
		int32_t result = GLFW_NO_ERROR;

		return result;
	}

	int32_t UnixDeviceResources::CreateWindowResources(GLFWwindow* window)
	{
		int32_t result = GLFW_NO_ERROR;

		return result;
	}

	int32_t UnixDeviceResources::ConfigureBackBuffer()
	{
		int32_t result = GLFW_NO_ERROR;

		return result;
	}

	int32_t UnixDeviceResources::ReleaseBackBuffer()
	{
		int32_t result = GLFW_NO_ERROR;

		return result;
	}

	int32_t UnixDeviceResources::GoFullScreen()
	{
		int32_t result = GLFW_NO_ERROR;

		return result;
	}
	
	int32_t UnixDeviceResources::GoWindowed()
	{
		int32_t result = GLFW_NO_ERROR;

		return result;
	}

	float UnixDeviceResources::GetAspectRatio()
	{
		return 0.0f;
	}

	void UnixDeviceResources::Present()
	{
	}
} // namespace cave
