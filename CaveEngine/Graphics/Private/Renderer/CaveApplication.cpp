/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Renderer/CaveApplication.h"

CaveApplication* CaveApplication::msInstance = 0;

CaveApplication* CaveApplication::GetInstance()
{
	if (msInstance == nullptr)
	{
		msInstance = new CaveApplication();
	}

	return msInstance;
}

CaveApplication::CaveApplication():
	mHWnd(nullptr)
{
	mpCaveRenderer = CaveRenderer::GetInstance();

	mWindowWidth = 640;
	mWindowHeight = 480;
}
CaveApplication::~CaveApplication()
{
	SAFE_DELETE(mpCaveRenderer);
}
void CaveApplication::RunMessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
HRESULT CaveApplication::Initialize(HINSTANCE hInstance)
{
	HRESULT hr = mpCaveRenderer->CreateDeviceIndependentResources();
	if (SUCCEEDED(hr))
	{
		WNDCLASSEX wcEX = { sizeof(WNDCLASSEX) };
		wcEX.style = CS_HREDRAW | CS_VREDRAW;
		wcEX.lpfnWndProc = CaveApplication::WndProc;
		wcEX.cbClsExtra = 0;
		wcEX.cbWndExtra = sizeof(LONG_PTR);
		wcEX.hInstance = hInstance;
		wcEX.hbrBackground = NULL;
		wcEX.lpszMenuName = NULL;
		wcEX.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcEX.lpszClassName = L"CaveApp";

		RegisterClassEx(&wcEX);
		mHWnd = CreateWindow(L"CaveApp", L"CaveWindow", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, mWindowWidth, mWindowHeight, NULL, NULL, HINST_THISCOMPONENT, this);

		hr = mHWnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			mpCaveRenderer->SethWnd(mHWnd);
			ShowWindow(mHWnd, SW_SHOWNORMAL);
			UpdateWindow(mHWnd);
		}
	}
	return hr;
}
LRESULT CALLBACK CaveApplication::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		CaveApplication* pCaveApp = (CaveApplication*)pcs->lpCreateParams;
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, PtrToUlong(pCaveApp));
		result = 1;
	}
	else
	{
		CaveApplication* pCaveApp = reinterpret_cast<CaveApplication*>(static_cast<LONG_PTR>(GetWindowLongPtrW(hWnd, GWLP_USERDATA)));
		bool bHandled = false;
		if (pCaveApp)
		{
			switch (message)
			{
			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pCaveApp->OnResize(width, height);
			}
			result = 0;
			bHandled = true;
			break;
			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hWnd, nullptr, FALSE);
			}
			result = 0;
			bHandled = true;
			break;
			case WM_PAINT:
			{
				pCaveApp->OnRender();
				ValidateRect(hWnd, nullptr);
			}
			result = 0;
			bHandled = true;
			break;
			case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
			result = 1;
			bHandled = true;
			break;
			}
		}
		if (!bHandled)
		{
			result = DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	return result;
}
HRESULT CaveApplication::OnRender()
{
	return mpCaveRenderer->OnRender();
}
void CaveApplication::OnResize(UINT width, UINT height)
{
	mpCaveRenderer->OnResize(width, height);
}

HWND CaveApplication::GethWnd() const 
{
	return mHWnd;
}

void CaveApplication::SethWnd(HWND hWnd)
{
	mHWnd = hWnd;
}
int CaveApplication::GetWindowWidth()
{
	return mWindowWidth;
}
int CaveApplication::GetWindowHeight() 
{
	return mWindowHeight;
}
void CaveApplication::SetWindowSize(int windowWidth, int windowHeight)
{
	mWindowWidth = windowWidth;
	mWindowHeight = windowHeight;
}