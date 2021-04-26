/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "UnixEngine.h"

#ifdef __UNIX__
namespace cave
{
	UnixEngine::UnixEngine()
		: GenericEngine()
		, mWindow(nullptr)
	{
	}

	int32_t UnixEngine::CreateDesktopWindow()
	{
		return 0;
	}


	int32_t UnixEngine::Run(DeviceResources* deviceResources, Renderer* renderer)
	{
		while (renderer->WindowShouldClose())
		{
			// Update the scene.
			renderer->Update();

			// Render frames during idle time (when no messages are waiting).
			renderer->Render();

			// Present the frame to the screen.
			renderer->GetDeviceResources()->Present();
		}

		return 0;
	}

	const GLFWwindow* UnixEngine::GetWindowHandle()
	{
		return mWindow;
	}
}
#endif