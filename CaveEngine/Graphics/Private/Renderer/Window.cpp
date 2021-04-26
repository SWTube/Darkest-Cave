/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

// #include "Renderer/Window.h"

// namespace cave
// {
// 	Window::Window(
// 		  uint32_t width
// 		, uint32_t height
// 		, const char* title
// #if defined(__UNIX__)
// 		, GLFWmonitor* monitor
// 		, GLFWwindow* share
// #endif
// 	)
// 		: mWidth(width)
// 		, mHeight(height)
// 		, mTitle(title)
// #if defined(__UNIX__)
// 		, mMonitor(monitor)
// 		, mShare(share)
// 		, mWindow(glfwCreateWindow(mWidth, mHeight, mTitle, mMonitor, mShare))
// #endif
// 	{
// 		assert(mWindow != nullptr);

// #if defined(__UNIX__)
// 		glfwSetWindowUserPointer(mWindow, this);
// 		glfwSetWindowSizeCallback(mWindow, windowSizeCallback);
// 		glfwSetKeyCallback(mWindow, keyCallback);
// 		glfwSetCharCallback(mWindow, charCallback);
// #endif
// 	}

// 	void Window::OnChar(uint32_t codepoint)
// 	{
// 		LOGIF(eLogChannel::GRAPHICS, std::cout, "Codepoint: %u", codepoint);
// 	}

// 	void Window::OnKey(int32_t key, int32_t scancode, int32_t action, int32_t mods)
// 	{
// 		LOGIF(eLogChannel::GRAPHICS, std::cout, "Key: %d, Scancode: %d, Action: %d, Mods: %d", key, scancode, action, mods);
// 	}

// 	void Window::Resize(uint32_t width, uint32_t height)
// 	{
// 		mWidth = width;
// 		mHeight = height;
// #if defined(__UNIX__)
// 		glViewport(0, 0, static_cast<int32_t>(mWidth), static_cast<int32_t>(mHeight));
// #endif
// 	}

// #if defined(__UNIX__)
// 	void Window::windowSizeCallback(GLFWwindow* window, int32_t width, int32_t height)
// 	{	
// 		reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->Resize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
// 	}

// 	void Window::keyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
// 	{
// 		reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->OnKey(key, scancode, action, mods);
// 	}

// 	void Window::charCallback(GLFWwindow* window, uint32_t codepoint)
// 	{
// 		reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->OnChar(codepoint);
// 	}
// #endif
// }