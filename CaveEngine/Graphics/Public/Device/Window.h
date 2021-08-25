/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */


#pragma once

#include "GraphicsApiPch.h"
#include "CoreTypes.h"

namespace cave
{
	class Window
	{
	public:
		Window() = delete;
		Window(uint32_t width, uint32_t height, const wchar_t* title, HINSTANCE hInstance, LRESULT(CALLBACK* windowProc)(HWND, uint32_t, WPARAM, LPARAM));

		Window(const Window&) = delete;
		Window(const Window&&) = delete;
		Window& operator=(const Window&) = delete;
		~Window() = default;

		void Resize(uint32_t width, uint32_t height);

		HWND GetWindow();
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		constexpr float GetNear() const;
		constexpr float GetFar() const;

		constexpr bool IsFullScreen() const;
		constexpr void SetFullScreen();
		constexpr void SetWindowed();

	private:
		bool mbIsFullScreen = false;
		uint32_t mWidth = 0u;
		uint32_t mHeight = 0u;
		float mNear = 0.1f;
		float mFar = 1000.0f;
		const wchar_t* mTitle = nullptr;
		HWND mWindow = nullptr;
		HMENU mMenu = nullptr;
		RECT mRect;

	};

	constexpr bool Window::IsFullScreen() const
	{
		return mbIsFullScreen;
	}

	constexpr void Window::SetFullScreen()
	{
		mbIsFullScreen = true;
	}

	constexpr void Window::SetWindowed()
	{
		mbIsFullScreen = false;
	}

	constexpr float Window::GetNear() const
	{
		return mNear;
	}

	constexpr float Window::GetFar() const
	{
		return mFar;
	}



}