#pragma once
#include "GraphicsCommon.h"

class CaveRenderer
{
public:
	static CaveRenderer* GetInstance();
	~CaveRenderer();

	HWND GethWnd() const;
	void SethWnd(HWND hWnd);

	void BeginDraw();
	HRESULT EndDraw();
	void ClearScreen();
	void ClearScreen(float r, float g, float b);

	HRESULT OnRender();
	void OnResize(UINT width, UINT height);
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

private:
	static CaveRenderer* msInstance;
	CaveRenderer();
	HWND mHWnd;

	ID2D1Factory* mpD2DFactory;
	ID2D1HwndRenderTarget* mpRenderTarget;
};