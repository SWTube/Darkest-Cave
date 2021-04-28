/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreTypes.h"

namespace cave
{
	class GenericWindow
	{
	public:
		GenericWindow() = delete;
#ifdef __WIN32__
		GenericWindow(uint32_t width, uint32_t height, const wchar_t* title);
#else
		GenericWindow(uint32_t width, uint32_t height, const char* title);
#endif
		GenericWindow(const GenericWindow&) = delete;
		GenericWindow(const GenericWindow&&) = delete;
		GenericWindow& operator=(const GenericWindow&) = delete;
		virtual ~GenericWindow() = default;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

#ifdef __WIN32__
		virtual HWND GetWindow() = 0;
#else
		virtual GLFWwindow* GetWindow() = 0;
#endif
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
	protected:
		uint32_t mWidth = 0u;
		uint32_t mHeight = 0u;
#ifdef __WIN32__
		const wchar_t* mTitle = nullptr;
#else
		const char* mTitle = nullptr;
#endif
	};
}
