/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Device/WindowDeviceResources.h"

#ifdef __WIN32__
namespace cave
{
	WindowDeviceResources::~WindowDeviceResources()
	{
		Destroy();
	}

	int32_t WindowDeviceResources::CreateDeviceResources()
	{
		int32_t result = S_OK;

		uint32_t createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(CAVE_BUILD_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		uint32_t numDriverTypes = ARRAYSIZE( driverTypes );

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};
		uint32_t numFeatureLevels = ARRAYSIZE( featureLevels );

		for(uint32_t driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
		{
			mDriverType = driverTypes[driverTypeIndex];

			result = D3D11CreateDevice(nullptr, mDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &mD3dDevice, &mFeatureLevel, &mImmediateContext);

			if (result == E_INVALIDARG)
			{
				// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
				result = D3D11CreateDevice(nullptr, mDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1, D3D11_SDK_VERSION, &mD3dDevice, &mFeatureLevel, &mImmediateContext);
			}

			if (SUCCEEDED(result))
			{
				break;
			}
		}
		if (FAILED(result))
		{
			return result;
		}

		return result;
	}

	int32_t WindowDeviceResources::CreateWindowResources(HWND window)
	{
		assert(window != nullptr);
		int32_t result = S_OK;

		// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
		IDXGIFactory1* dxgiFactory = nullptr;
		{
			IDXGIDevice* dxgiDevice = nullptr;
			result = static_cast<int32_t>(mD3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice)));
			if (SUCCEEDED(static_cast<uint32_t>(result)))
			{
				IDXGIAdapter* adapter = nullptr;
				result = static_cast<int32_t>(dxgiDevice->GetAdapter(&adapter));
				if (SUCCEEDED(static_cast<uint32_t>(result)))
				{
					result = static_cast<int32_t>(adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory)));
					adapter->Release();
				}
				dxgiDevice->Release();
			}
		}
		if (FAILED(result))
		{
			return result;
		}

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
		desc.Windowed = TRUE;
		desc.BufferCount = 2;
		desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SampleDesc.Count = 1;      //multisampling setting
		desc.SampleDesc.Quality = 0;    //vendor-specific flag
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		desc.OutputWindow = window;

		RECT rc;
		GetClientRect(window, &rc);
		uint32_t width = rc.right - rc.left;
		uint32_t height = rc.bottom - rc.top;

		// Create swap chain
		IDXGIFactory2* dxgiFactory2 = nullptr;
		result = dxgiFactory->QueryInterface( __uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
		if ( dxgiFactory2 )
		{
			// DirectX 11.1 or later
			result = mD3dDevice->QueryInterface( __uuidof(ID3D11Device1), reinterpret_cast<void**>(&mD3dDevice1));
			if (SUCCEEDED(result))
			{
				static_cast<void>(mImmediateContext->QueryInterface( __uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&mImmediateContext1) ));
			}

			DXGI_SWAP_CHAIN_DESC1 sd = {};
			sd.Width = width;
			sd.Height = height;
			sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.BufferCount = 1;

			result = dxgiFactory2->CreateSwapChainForHwnd( mD3dDevice, window, &sd, nullptr, nullptr, &mSwapChain1 );
			if (SUCCEEDED(result))
			{
				result = mSwapChain1->QueryInterface( __uuidof(IDXGISwapChain), reinterpret_cast<void**>(&mSwapChain) );
			}

			dxgiFactory2->Release();
		}
		else
		{
			// DirectX 11.0 systems
			DXGI_SWAP_CHAIN_DESC sd = {};
			sd.BufferCount = 2;
			sd.BufferDesc.Width = width;
			sd.BufferDesc.Height = height;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = window;
			sd.SampleDesc.Count = 1;	// multisampling setting
			sd.SampleDesc.Quality = 0;	// vendor-specific flag
			sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
			sd.Windowed = TRUE;

			result = dxgiFactory->CreateSwapChain( mD3dDevice, &sd, &mSwapChain );
		}

		dxgiFactory->Release();

		if (FAILED(result))
		{
			return result;
		}

		result = ConfigureBackBuffer();

		return result;
	}

	int32_t WindowDeviceResources::ConfigureBackBuffer()
	{
		int32_t result = S_OK;

		// Create a render target view
		result = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&mBackBuffer));
		if (FAILED(result))
		{
			return result;
		}
		mBackBuffer->GetDesc(&mBackBufferDesc);

		result = mD3dDevice->CreateRenderTargetView(mBackBuffer, nullptr, &mRenderTargetView);
		if(FAILED(result))
		{
			return result;
		}

		// Create depth stencil texture
		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width = mBackBufferDesc.Width;
		descDepth.Height = mBackBufferDesc.Height;
		descDepth.MipLevels = 1;	// Use a single mimap level
		descDepth.ArraySize = 1;	// this depth stencil view has only one texture
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		result = mD3dDevice->CreateTexture2D(&descDepth, nullptr, &mDepthStencil);
		if (FAILED(result))
		{
			return result;
		}

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		result = mD3dDevice->CreateDepthStencilView(mDepthStencil, &descDSV, &mDepthStencilView);
		if (FAILED(result))
		{
			return result;
		}

		// Setup the viewport
		D3D11_VIEWPORT vp;
		vp.Width = static_cast<float>(mBackBufferDesc.Width);
		vp.Height = static_cast<float>(mBackBufferDesc.Height);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		mImmediateContext->RSSetViewports(1, &vp);

		return result;
	}

	int32_t WindowDeviceResources::ReleaseBackBuffer()
	{
		int32_t result = S_OK;

		// Release the render target view based on the back buffer:
		if (mRenderTargetView != nullptr)
		{
			mRenderTargetView->Release();
		}

		// Release the back buffer itself:
		if (mBackBuffer != nullptr)
		{
			mBackBuffer->Release();
		}

		// The depth stencil will need to be resized, so release it (and view):
		if (mDepthStencilView != nullptr)
		{
			mDepthStencilView->Release();
		}

		if (mDepthStencil != nullptr)
		{
			mDepthStencil->Release();
		}

		// After releasing references to these resources, we need to call Flush() to 
		// ensure that Direct3D also releases any references it might still have to
		// the same resources - such as pipeline bindings.
		if (mImmediateContext != nullptr)
		{
			mImmediateContext->ClearState();
		}

		return result;
	}

	int32_t WindowDeviceResources::GoFullScreen()
	{
		int32_t result = S_OK;

		result = mSwapChain->SetFullscreenState(TRUE, NULL);

		// Swap chains created with the DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL flag need to
		// call ResizeBuffers in order to realize a full-screen mode switch. Otherwise, 
		// your next call to Present will fail.

		// Before calling ResizeBuffers, you have to release all references to the back 
		// buffer device resource.
		ReleaseBackBuffer();

		// Now we can call ResizeBuffers.
		result = mSwapChain->ResizeBuffers(
			0,                   // Number of buffers. Set this to 0 to preserve the existing setting.
			0, 0,                // Width and height of the swap chain. Set to 0 to match the screen resolution.
			DXGI_FORMAT_UNKNOWN, // This tells DXGI to retain the current back buffer format.
			0
		);

		// Then we can recreate the back buffer, depth buffer, and so on.
		result = ConfigureBackBuffer();

		return result;
	}
	
	int32_t WindowDeviceResources::GoWindowed()
	{
		int32_t result = S_OK;

		result = mSwapChain->SetFullscreenState(FALSE, NULL);

		// Swap chains created with the DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL flag need to
		// call ResizeBuffers in order to realize a change to windowed mode. Otherwise, 
		// your next call to Present will fail.

		// Before calling ResizeBuffers, you have to release all references to the back 
		// buffer device resource.
		ReleaseBackBuffer();

		// Now we can call ResizeBuffers.
		result = mSwapChain->ResizeBuffers(
			0,                   // Number of buffers. Set this to 0 to preserve the existing setting.
			0, 0,                // Width and height of the swap chain. MUST be set to a non-zero value. For example, match the window size.
			DXGI_FORMAT_UNKNOWN, // This tells DXGI to retain the current back buffer format.
			0
		);

		// Then we can recreate the back buffer, depth buffer, and so on.
		result = ConfigureBackBuffer();

		return result;
	}

	float WindowDeviceResources::GetAspectRatio()
	{
		return static_cast<float>(mBackBufferDesc.Width) / static_cast<float>(mBackBufferDesc.Height);
	}

	ID3D11Device* WindowDeviceResources::GetDevice()
	{
		return mD3dDevice;
	}
	
	ID3D11DeviceContext* WindowDeviceResources::GetDeviceContext()
	{
		return mImmediateContext;
	}

	ID3D11RenderTargetView* WindowDeviceResources::GetRenderTarget()
	{
		return mRenderTargetView;
	}

	ID3D11DepthStencilView* WindowDeviceResources::GetDepthStencil()
	{
		return mDepthStencilView;
	}

	D3D_DRIVER_TYPE WindowDeviceResources::GetDriverType() const
	{
		return mDriverType;
	}

	void WindowDeviceResources::Present()
	{
		mSwapChain->Present(1, 0);
	}

	void WindowDeviceResources::Destroy()
	{
		if (mImmediateContext != nullptr)
		{
			mImmediateContext->ClearState();
		}

		if (mDepthStencil != nullptr)
		{
			mDepthStencil->Release();
		}

		if (mDepthStencilView)
		{
			mDepthStencilView->Release();
		}

		if (mBackBuffer != nullptr)
		{
			mBackBuffer->Release();
		}

		if (mRenderTargetView != nullptr)
		{
			mRenderTargetView->Release();
		}
		
		if (mSwapChain1 != nullptr)
		{
			mSwapChain1->Release();
		}

		if (mSwapChain != nullptr)
		{
			mSwapChain->Release();
		}

		if (mImmediateContext1 != nullptr)
		{
			mImmediateContext1->Release();
		}

		if (mImmediateContext)
		{
			mImmediateContext->Release();
		}

		if (mD3dDevice1 != nullptr)
		{
			mD3dDevice1->Release();
		}

		if (mD3dDevice != nullptr)
		{
			mD3dDevice->Release();
		}
	}
} // namespace cave
#endif