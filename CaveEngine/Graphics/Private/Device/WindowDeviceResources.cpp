/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Device/WindowDeviceResources.h"

#ifdef __WIN32__
namespace cave
{
	int32_t WindowDeviceResources::CreateDeviceResources(HWND window)
	{
		int32_t result = S_OK;

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

		uint32_t createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(CAVE_BUILD_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
		desc.Windowed = TRUE;
		desc.BufferCount = 2;
		desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SampleDesc.Count = 1;      //multisampling setting
		desc.SampleDesc.Quality = 0;    //vendor-specific flag
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		desc.OutputWindow = hWnd;

		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;

		for(uint32_t driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
		{
			mDriverType = driverTypes[driverTypeIndex];

			result = D3D11CreateDevice(nullptr, mDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &mDevice, &mFeatureLevel, &mDeviceContext);

			if (result == E_INVALIDARG)
			{
				// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
				result = D3D11CreateDevice(nullptr, mDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1, D3D11_SDK_VERSION, &mDevice, &mFeatureLevel, &mDeviceContext);
			}

			if (SUCCEEDED(result))
			{
				break;
			}
		}
		if (FAILED(result)))
		{
			return result;
		}

		// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
		IDXGIFactory1* dxgiFactory = nullptr;
		{
			IDXGIDevice* dxgiDevice = nullptr;
			result = reinterpret_cast<int32_t>(mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice)));
			if (SUCCEEDED(reinterpret_cast<uint32_t>(result)))
			{
				IDXGIAdapter* adapter = nullptr;
				result = reinterpret_cast<int32_t>(dxgiDevice->GetAdapter(&adapter));
				if (SUCCEEDED(reinterpret_cast<uint32_t>(result)))
				{
					result = reinterpret_cast<int32_t>(adapter->GetParent( __uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory)));
					adapter->Release();
				}
				dxgiDevice->Release();
			}
		}
		if (FAILED(result)))
		{
			return result;
		}

		// Create swap chain
		IDXGIFactory2* dxgiFactory2 = nullptr;
		result = dxgiFactory->QueryInterface( __uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
		if ( dxgiFactory2 )
		{
			// DirectX 11.1 or later
			result = mDevice->QueryInterface( __uuidof(ID3D11Device1), reinterpret_cast<void**>(&g_pd3dDevice1));
			if (SUCCEEDED(result))
			{
				static_cast<void>(g_pImmediateContext->QueryInterface( __uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&g_pImmediateContext1) ));
			}

			DXGI_SWAP_CHAIN_DESC1 sd = {};
			sd.Width = width;
			sd.Height = height;
			sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.BufferCount = 1;

			result = dxgiFactory2->CreateSwapChainForHwnd( g_pd3dDevice, g_hWnd, &sd, nullptr, nullptr, &g_pSwapChain1 );
			if (SUCCEEDED(result))
			{
				result = g_pSwapChain1->QueryInterface( __uuidof(IDXGISwapChain), reinterpret_cast<void**>(&g_pSwapChain) );
			}

			dxgiFactory2->Release();
		}
		else
		{
			// DirectX 11.0 systems
			DXGI_SWAP_CHAIN_DESC sd = {};
			sd.BufferCount = 1;
			sd.BufferDesc.Width = width;
			sd.BufferDesc.Height = height;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator = 60;
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = g_hWnd;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.Windowed = TRUE;

			result = dxgiFactory->CreateSwapChain( g_pd3dDevice, &sd, &g_pSwapChain );
		}

		// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
		dxgiFactory->MakeWindowAssociation( g_hWnd, DXGI_MWA_NO_ALT_ENTER );

		dxgiFactory->Release();

		if (FAILED(result))
		{
			return result;
		}


		return result;
	}

	int32_t WindowDeviceResources::CreateDeviceResources()
	{
		int32_t result = S_OK;

		return result;
	}

	int32_t WindowDeviceResources::CreateWindowResources(HWND window)
	{
		int32_t result = S_OK;

		return result;
	}

	int32_t WindowDeviceResources::ConfigureBackBuffer()
	{
		int32_t result = S_OK;

		return result;
	}

	int32_t WindowDeviceResources::ReleaseBackBuffer()
	{
		int32_t result = S_OK;

		return result;
	}

	int32_t WindowDeviceResources::GoFullScreen()
	{
		int32_t result = S_OK;

		return result;
	}
	
	int32_t WindowDeviceResources::GoWindowed()
	{
		int32_t result = S_OK;

		return result;
	}

	float WindowDeviceResources::GetAspectRatio()
	{
		return 0.0f;
	}

	ID3D11Device* WindowDeviceResources::GetDevice()
	{
		return nullptr;
	}
	
	ID3D11DeviceContext* WindowDeviceResources::GetDeviceContext()
	{
		return nullptr;
	}

	ID3D11RenderTargetView* WindowDeviceResources::GetRenderTarget()
	{
		return nullptr;
	}

	ID3D11DepthStencilView* WindowDeviceResources::GetDepthStencil()
	{
		return nullptr;
	}

	void WindowDeviceResources::Present()
	{
	}
} // namespace cave
#endif