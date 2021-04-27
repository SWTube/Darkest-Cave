/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "GenericEngine.h"

namespace cave
{
	const wchar_t* GenericEngine::msWindowClassName = L"GenericWindowClass";

	Window* GenericEngine::GetWindowHandle()
	{
		return mWindow;
	}

	eResult GenericEngine::Run(DeviceResources* deviceResources, Renderer* renderer)
	{
		mDeviceResources = deviceResources;
		mRenderer = renderer;

		return Run();
	}

	void GenericEngine::AddDrawableObject(DrawableObject*&& object)
	{
		mRenderer->AddDrawableObject(std::move(object));
		object = nullptr;
	}
}
