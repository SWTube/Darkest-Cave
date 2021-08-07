/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "Device/DeviceResources.h"
#include "Renderer/Renderer.h"
#include "Game/GameInstance.h"

#define UPDATE_TIMESTEP (0.002)

namespace cave
{
	class GenericEngine
	{
	public:
		GenericEngine();
		virtual ~GenericEngine();

		virtual eResult Init(uint32_t screenWidth, uint32_t screenHeight) = 0;
		//virtual eResult Run(DeviceResources* deviceResources, Renderer* renderer);
		virtual eResult Run() = 0;
		virtual void Destroy() = 0;

		virtual Window* GetWindowHandle();
		virtual Renderer* GetRenderer();
		virtual GameInstance* GetGameInstance();

	protected:
		MemoryPool* mPool = nullptr;
		Renderer* mRenderer = nullptr;
		Window* mWindow = nullptr;

		GameInstance* mGameInstance = nullptr;

		static const wchar_t* msWindowClassName;
	};
}