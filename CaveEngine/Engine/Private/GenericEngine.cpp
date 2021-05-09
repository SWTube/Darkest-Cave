/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "GenericEngine.h"

namespace cave
{
	GenericEngine::GenericEngine()
		: mPool(&gCoreMemoryPool)
	{
	}

	const wchar_t* GenericEngine::msWindowClassName = L"GenericWindowClass";

	GenericEngine::GenericEngine()
		: mPool(new MemoryPool(1638400ul))
	{
	}

	GenericEngine::GenericEngine(MemoryPool& pool)
		: mPool(&pool)
	{
	}

	GenericEngine::~GenericEngine()
	{
		delete mPool;
	}

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

	Renderer* const GenericEngine::GetRenderer()
	{
		return mRenderer;
	}
}
