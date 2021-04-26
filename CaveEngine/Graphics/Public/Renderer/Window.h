/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

// namespace cave
// {
// 	class Window
// 	{
// 		constexpr Window() = delete;
// 		Window(
// 			  uint32_t width
// 			, uint32_t height
// 			, const char* title
// #if defined(__UNIX__)
// 			, GLFWmonitor* monitor
// 			, GLFWwindow* share
// #endif
// 		);
	
// 		virtual void OnChar(uint32_t codepoint);
// 		virtual void OnKey(int32_t key, int32_t scancode, int32_t action, int32_t mods);
// 		virtual void Resize(uint32_t width, uint32_t height);
	
// 	protected:
// #if defined(__UNIX__)
// 		static void windowSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
// 		static void keyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);
// 		static void charCallback(GLFWwindow* window, uint32_t codepoint);
// #endif
// 	private:
// 		uint32_t mWidth = 0u;
// 		uint32_t mHeight = 0u;
// 		const char* mTitle = nullptr;
// #if defined(__UNIX__)
// 		GLFWmonitor* mMonitor = nullptr;
// 		GLFWwindow* mShare = nullptr;
// 		GLFWwindow* mWindow = nullptr;
// #endif
// 	};
// }
