/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Device/UnixDeviceResources.h"

#ifdef __UNIX__
namespace cave
{
	int32_t UnixDeviceResources::CreateDeviceResources()
	{
		glfwSetErrorCallback(errorCallback);
		int32_t result = GLFW_NO_ERROR;
		GLenum glError = GL_NO_ERROR;

		int32_t glfwInitResult = glfwInit();
		if (glfwInitResult == GLFW_FALSE)
		{
			glfwTerminate();
			return glfwInitResult;
		}

		return result;
	}

	int32_t UnixDeviceResources::CreateWindowResources()
	{
		int32_t result = GLFW_NO_ERROR;

		mWidth = 1024;
		mHeight = 960;
		// Register class

		// Create window
		mWindow = glfwCreateWindow(static_cast<int32_t>(mWidth), static_cast<int32_t>(mHeight), "CaveEngine", nullptr, nullptr);
		if (mWindow == nullptr)
		{
			return glfwGetError(nullptr);
		}

		glfwSetWindowSizeCallback(mWindow, windowSizeCallback);
		glfwSetKeyCallback(mWindow, keyCallback);
		glfwSetCharCallback(mWindow, charCallback);

		// 2. Make Context Current ---------------------------------------------------------------------------------------------
		glfwMakeContextCurrent(mWindow);
		if (result = glfwGetError(nullptr); result != GLFW_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glfwMakeContextCurrent error code: 0x%x", result);
		}
		gl3wInit();

		LOGIF(eLogChannel::GRAPHICS, std::cout, "Renderer: %s", glGetString(GL_RENDERER));
		LOGIF(eLogChannel::GRAPHICS, std::cout, "OpenGL version supported: %s", glGetString(GL_VERSION));
		int32_t major = 0;
		int32_t minor = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		LOGIF(eLogChannel::GRAPHICS, std::cout, "OpenGL version supported: %d", major);
		LOGIF(eLogChannel::GRAPHICS, std::cout, "OpenGL version supported: %d", minor);

		return result;
	}

	int32_t UnixDeviceResources::CreateWindowResources(GLFWwindow* window)
	{
		int32_t result = GLFW_NO_ERROR;

		assert(window != nullptr);
		mWindow = window;

		mWidth = 1024;
		mHeight = 960;
		// Register class

		// Create window
		mWindow = glfwCreateWindow(static_cast<int32_t>(mWidth), static_cast<int32_t>(mHeight), "CaveEngine", nullptr, nullptr);
		if (mWindow == nullptr)
		{
			return glfwGetError(nullptr);
		}

		glfwSetWindowSizeCallback(mWindow, windowSizeCallback);
		glfwSetKeyCallback(mWindow, keyCallback);
		glfwSetCharCallback(mWindow, charCallback);

		// 2. Make Context Current ---------------------------------------------------------------------------------------------
		glfwMakeContextCurrent(mWindow);
		if (result = glfwGetError(nullptr); result != GLFW_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glfwMakeContextCurrent error code: 0x%x", result);
		}
		gl3wInit();

		LOGIF(eLogChannel::GRAPHICS, std::cout, "Renderer: %s", glGetString(GL_RENDERER));
		LOGIF(eLogChannel::GRAPHICS, std::cout, "OpenGL version supported: %s", glGetString(GL_VERSION));
		int32_t major = 0;
		int32_t minor = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		LOGIF(eLogChannel::GRAPHICS, std::cout, "OpenGL version supported: %d", major);
		LOGIF(eLogChannel::GRAPHICS, std::cout, "OpenGL version supported: %d", minor);

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

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowMonitor(mWindow, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
		if (mWindow == nullptr)
		{
			return glfwGetError(nullptr);
		}

		return result;
	}
	
	int32_t UnixDeviceResources::GoWindowed()
	{
		int32_t result = GLFW_NO_ERROR;

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowMonitor(mWindow, nullptr, 0, 0, static_cast<int32_t>(mWidth), static_cast<int32_t>(mHeight), mode->refreshRate);
		if (mWindow == nullptr)
		{
			return glfwGetError(nullptr);
		}

		return result;
	}

	float UnixDeviceResources::GetAspectRatio()
	{
		return static_cast<float>(mWidth) / static_cast<float>(mHeight);
	}

	void UnixDeviceResources::Present()
	{
		// 6. Swap buffers ---------------------------------------------------------------------------------------------
		glfwSwapBuffers(mWindow);
	}

	void UnixDeviceResources::errorCallback(int32_t errorCode, const char* description)
	{
		LOGE(eLogChannel::GRAPHICS, std::cerr, description);
	}

	void UnixDeviceResources::Destroy()
	{
		if (mWindow != nullptr)
		{
			glfwDestroyWindow(mWindow);
		}

		glfwTerminate();
	}

	uint32_t UnixDeviceResources::GetProgram() const
	{
		return mProgram;
	}

	void UnixDeviceResources::SetProgram(uint32_t program)
	{
		mProgram = program;
	}

	GLFWwindow* const UnixDeviceResources::GetWindow() const
	{
		return mWindow;
	}
} // namespace cave
#endif