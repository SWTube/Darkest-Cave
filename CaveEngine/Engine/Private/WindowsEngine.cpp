/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "WindowsEngine.h"

#ifdef __WIN32__
namespace cave
{
	HINSTANCE	WindowsEngine::msInstance = nullptr;

	eResult WindowsEngine::Init()
	{
		eResult result = eResult::CAVE_OK;

#ifdef __WIN32__
		mWindow = new Window(640u, 480u, L"Test", msInstance, StaticWindowProc);
#else
		mWindow = new Window(640u, 480u, "Test", nullptr);
#endif

		// Instantiate the device manager class.
		mDeviceResources = new DeviceResources();
		// Create device resources.
		result = mDeviceResources->CreateDeviceResources();
		if (result != eResult::CAVE_OK)
		{
			return result;
		}

		// Instantiate the renderer.
		mRenderer = new Renderer(mDeviceResources);
		mRenderer->CreateDeviceDependentResources();
	
		// We have a window, so initialize window size-dependent resources.
		mDeviceResources->CreateWindowResources(mWindow);
		if (result != eResult::CAVE_OK)
		{
			return result;
		}

		mRenderer->CreateWindowSizeDependentResources();
		
		return result;
	}

	void WindowsEngine::Destroy()
	{
		if (mRenderer != nullptr)
		{
			mRenderer->Destroy();
			delete mRenderer;
		}

		if (mDeviceResources != nullptr)
		{
			mDeviceResources->Destroy();
			delete mDeviceResources;
		}

		if (mWindow != nullptr)
		{
			delete mWindow;
		}
	}

	eResult WindowsEngine::Run()
	{
		int32_t hr = S_OK;
		HWND window = mWindow->GetWindow();
		if (!IsWindowVisible(window))
		{
			ShowWindow(window, SW_SHOW);
		}

		// The render loop is controlled here.
		bool bGotMsg;
		MSG  msg;
		msg.message = WM_NULL;
		PeekMessage(&msg, nullptr, 0u, 0u, PM_NOREMOVE);
		while (WM_QUIT != msg.message)
		{
			// Process window events.
			// Use PeekMessage() so we can use idle time to render the scene. 
			bGotMsg = (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE) != 0);

			if (bGotMsg)
			{
				// Translate and dispatch the message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// Update the scene.
				mRenderer->Update();

				// Render frames during idle time (when no messages are waiting).
				mRenderer->Render();

				// Present the frame to the screen.
				mDeviceResources->Present();
			}
		}

		return eResult::CAVE_OK;
	}

	LRESULT CALLBACK WindowsEngine::StaticWindowProc(HWND hWindow, uint32_t message, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT ps;
		HDC hdc;

		switch(message)
		{
		case WM_PAINT:
			hdc = BeginPaint(hWindow, &ps);
			EndPaint(hWindow, &ps);
			break;
		
		case WM_CLOSE:
			HMENU hMenu;
			hMenu = GetMenu(hWindow);
			if (hMenu != nullptr)
			{
				DestroyMenu(hMenu);
			}
			DestroyWindow(hWindow);
			UnregisterClass(
				msWindowClassName,
				msInstance
			);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

			// Note that this tutorial does not handle resizing (WM_SIZE) requests,
			// so we created the window without the resize border.

		default:
			return DefWindowProc(hWindow, message, wParam, lParam);
		}

		return 0;
	}
}
#endif