/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "GenericEngine.h"

#ifdef __WIN32__
namespace cave
{
	class WindowEngine final : public GenericEngine
	{
	public:
		WindowEngine();
		virtual ~WindowEngine();

		HWND GetWindowHandle() override;
		int32_t CreateDesktopWindow() override;
		int32_t Run(DeviceResources* deviceResources, Renderer* renderer) override;

		static LRESULT CALLBACK StaticWindowProc(HWND hWindow, uint32_t message, WPARAM wParam, LPARAM lParam);
		
	private:
		HINSTANCE	mInstance = nullptr;
		HWND		mWindow = nullptr;
		HMENU		mMenu = nullptr;
		RECT		mRect;
	};

	typedef WindowEngine Engine;
}
#endif