/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "WindowEngine.h"

#ifdef __WIN32__
namespace cave
{
	WindowEngine::WindowEngine()
		: GenericEngine()
		, mInstance(nullptr)
	{
	}

	WindowEngine::~WindowEngine()
	{
	}

	int32_t WindowEngine::CreateDesktopWindow()
	{
		// Window resources are dealt with here.
    
		if (mInstance == nullptr)
		{
			mInstance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));
		}

		// HICON hIcon = nullptr;
		// wchar_t szExePath[MAX_PATH];
		// GetModuleFileName(nullptr, szExePath, MAX_PATH);
		
		// // If the icon is NULL, then use the first one found in the exe
		// if(hIcon == NULL)
		// {
		// 	hIcon = ExtractIcon(mInstance, szExePath, 0);
		// }

		// Register the windows class
		WNDCLASS wndClass;
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = MainClass::StaticWindowProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = mInstance;
		// wndClass.hIcon = hIcon;
		wndClass.hIcon = LoadIcon(mInstance, reinterpret_cast<LPCTSTR>(107));
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = static_cast<HBRUSH>(COLOR_WINDOW + 1);
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = mWindowClassName;
		wndClass.hIconSm = LoadIcon(wndClass.hInstance, reinterpret_cast<LPCTSTR>(107));

		if(!RegisterClass(&wndClass))
		{
			DWORD dwError = GetLastError();
			if(dwError != ERROR_CLASS_ALREADY_EXISTS)
			{
				return HRESULT_FROM_WIN32(dwError);
			}
		}

		// Create window
		mRect;
		int32_t x = CW_USEDEFAULT;
		int32_t y = CW_USEDEFAULT;

		// No menu in this example.
		mMenu = nullptr;

		// This example uses a non-resizable 640 by 480 viewport for simplicity.
		int32_t defaultWidth = 640;
		int32_t defaultHeight = 480;
		SetRect(&mRect, 0, 0, defaultWidth, defaultHeight);        
		AdjustWindowRect(
			&mRect,
			WS_OVERLAPPEDWINDOW,
			(mMenu != nullptr) ? true : false
		);

		// Create the window for our viewport.
		mWindow = CreateWindow(
			mWindowClassName,
			L"CaveEngine",
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			x, y,
			(mRect.right - mRect.left), (mRect.bottom - mRect.top),
			nullptr,
			mMenu,
			mInstance,
			nullptr
		);

		if(mWindow == nullptr)
		{
			DWORD dwError = GetLastError();
			return HRESULT_FROM_WIN32(dwError);
		}

		return S_OK;
	}


	int32_t WindowEngine::Run(DeviceResources* deviceResources, Renderer* renderer)
	{
		int32_t hr = S_OK;

		if (!IsWindowVisible(mWindow))
		{
			ShowWindow(mWindow, SW_SHOW);
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
				renderer->Update();

				// Render frames during idle time (when no messages are waiting).
				renderer->Render();

				// Present the frame to the screen.
				deviceResources->Present();
			}
		}

		return hr;
	}

	static LRESULT CALLBACK WindowEngine::StaticWindowProc(HWND hWindow, uint32_t message, WPARAM wParam, LPARAM lParam)
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
				mWindowClassName,
				mInstance
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

	HWND WindowEngine::GetWindowHandle()
	{
		return mWindow;
	}
}
#endif