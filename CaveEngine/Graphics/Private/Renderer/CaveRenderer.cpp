#include "Renderer/CaveRenderer.h"

CaveRenderer* CaveRenderer::msInstance = 0;

CaveRenderer* CaveRenderer::GetInstance()
{
	if (msInstance == nullptr)
	{
		msInstance = new CaveRenderer();
	}

	return msInstance;
}

CaveRenderer::CaveRenderer() :
	mHWnd(nullptr)
	, mpD2DFactory(nullptr)
	, mpRenderTarget(nullptr)
{
}
CaveRenderer::~CaveRenderer()
{
	DiscardDeviceResources();
	SAFE_RELEASE(mpD2DFactory);
}

HRESULT CaveRenderer::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mpD2DFactory);

	return hr;
}

HRESULT CaveRenderer::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (!mpRenderTarget)
	{
		RECT rc;
		GetClientRect(mHWnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		hr = mpD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(mHWnd, size),
			&mpRenderTarget);

		/*
		* Add device dependent resources
		* ex)
		* if(SUCCEEDED(hr))
		* {
		*	hr = mpRenderTarget->CreateSolidColorBrush(
		*				D2D1::ColorF(D2D1::ColorF::LightSlateGray), &mpLightSlateGrayBrush);
		*/
	}

	return hr;
}

void CaveRenderer::DiscardDeviceResources()
{
	SAFE_RELEASE(mpRenderTarget);
}
HRESULT CaveRenderer::OnRender()
{
	HRESULT hr = S_OK;
	hr = CreateDeviceResources();

	if (SUCCEEDED(hr))
	{
		BeginDraw();
		mpRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		ClearScreen();

		/*
		* Drawing here
		*/



		/*
		* Drawing end
		*/

		hr = EndDraw();
	}
	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
	return hr;
}
void CaveRenderer::OnResize(UINT width, UINT height)
{
	if (mpRenderTarget)
	{
		mpRenderTarget->Resize(D2D1::SizeU(width, height));
	}
}
void CaveRenderer::BeginDraw()
{
	mpRenderTarget->BeginDraw();
}
HRESULT CaveRenderer::EndDraw()
{
	return mpRenderTarget->EndDraw();
}
void CaveRenderer::ClearScreen()
{
	mpRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}
void CaveRenderer::ClearScreen(float r, float g, float b)
{
	mpRenderTarget->Clear(D2D1::ColorF(r, g, b));
}
HWND CaveRenderer::GethWnd() const
{
	return mHWnd;
}
void CaveRenderer::SethWnd(HWND hWnd)
{
	mHWnd = hWnd;
}