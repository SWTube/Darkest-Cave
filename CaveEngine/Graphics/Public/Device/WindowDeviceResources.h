/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "GraphicsApiPch.h"
#include "Device/GenericDeviceResources.h"

#ifdef __WIN32__
namespace cave
{
	class WindowDeviceResources final : public GenericDeviceResources
	{
	public:
		constexpr WindowDeviceResources() = default;
		constexpr WindowDeviceResources(const WindowDeviceResources&) = default;
		WindowDeviceResources& operator=(const WindowDeviceResources&) = default;
		virtual ~WindowDeviceResources() = default;

		int32_t CreateDeviceResources(HWND window) override;
		int32_t CreateWindowResources(HWND window) override;
		int32_t CreateDeviceResources() override;

		int32_t ConfigureBackBuffer() override;
		int32_t ReleaseBackBuffer() override;
		int32_t GoFullScreen() override;
		int32_t GoWindowed() override;

		float GetAspectRatio() override;

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetDeviceContext();
		ID3D11RenderTargetView* GetRenderTarget();
		ID3D11DepthStencilView* GetDepthStencil();

		void Present() override;
	private:
		//-----------------------------------------------------------------------------
		// Direct3D device
		//-----------------------------------------------------------------------------
		Microsoft::WRL::ComPtr<ID3D11Device>        mD3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mD3dDeviceContext; // immediate context
		Microsoft::WRL::ComPtr<IDXGISwapChain>      mDXGISwapChain;


		//-----------------------------------------------------------------------------
		// DXGI swap chain device resources
		//-----------------------------------------------------------------------------
		Microsoft::WRL::ComPtr < ID3D11Texture2D>        mBackBuffer;
		Microsoft::WRL::ComPtr < ID3D11RenderTargetView> mRenderTarget;


		//-----------------------------------------------------------------------------
		// Direct3D device resources for the depth stencil
		//-----------------------------------------------------------------------------
		Microsoft::WRL::ComPtr<ID3D11Texture2D>         mDepthStencil;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  mDepthStencilView;


		//-----------------------------------------------------------------------------
		// Direct3D device metadata and device resource metadata
		//-----------------------------------------------------------------------------
		D3D_FEATURE_LEVEL       mFeatureLevel;
		D3D11_TEXTURE2D_DESC    mBackBufferDesc;
		D3D11_VIEWPORT          mViewport;
	};

	typedef WindowDeviceResources DeviceResources;
}
#endif