/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "GraphicsApiPch.h"
#include "Renderer/CaveRenderer.h"

#ifdef __WIN32__

#ifndef HINST_THISCOMPONENT
	EXTERN_C IMAGE_DOS_HEADER __ImageBase;
	#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

class CaveApplication
{
public:
	static CaveApplication* GetInstance();
	~CaveApplication();
		
	HRESULT Initialize(HINSTANCE hInstance);
	HWND GethWnd() const;
	void SethWnd(HWND hWnd);

	void RunMessageLoop();

	int GetWindowWidth();
	int GetWindowHeight();
	void SetWindowSize(int windowWidth, int windowHeight);

private:
	CaveApplication();
	static CaveApplication* msInstance;

	CaveRenderer* mpCaveRenderer;
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HRESULT OnRender();
	void OnResize(UINT width, UINT height);

	HWND mHWnd;

	int mWindowWidth;
	int mWindowHeight;
};
#endif