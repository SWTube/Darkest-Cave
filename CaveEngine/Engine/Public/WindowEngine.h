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
		WindowEngine() = default;
		virtual ~WindowEngine() = default;

		eResult Init() override;
		void Destroy() override;
		eResult Run() override;

		static LRESULT CALLBACK StaticWindowProc(HWND hWindow, uint32_t message, WPARAM wParam, LPARAM lParam);
		
	private:
		static HINSTANCE	msInstance;
		HMENU				mMenu = nullptr;
		RECT				mRect;
	};

	typedef WindowEngine Engine;
}
#endif