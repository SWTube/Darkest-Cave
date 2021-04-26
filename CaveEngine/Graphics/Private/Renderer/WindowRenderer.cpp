/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Renderer/WindowRenderer.h"

#ifdef __WIN32__
namespace cave
{
	ID3D11VertexShader*			WindowRenderer::msVertexShader = nullptr;
	ID3D11PixelShader*			WindowRenderer::msPixelShader = nullptr;
	ID3D11InputLayout*			WindowRenderer::msVertexLayout = nullptr;
	ID3D11Buffer*				WindowRenderer::msVertexBuffer = nullptr;
	ID3D11Buffer*				WindowRenderer::msIndexBuffer = nullptr;
	ID3D11Buffer*				WindowRenderer::msConstantBufferNeverChanges = nullptr;
	ID3D11Buffer*				WindowRenderer::msConstantBufferChangeOnResize = nullptr;
	ID3D11Buffer*				WindowRenderer::msConstantBufferChangesEveryFrame = nullptr;
	ID3D11ShaderResourceView*	WindowRenderer::msTextureRv = nullptr;
	ID3D11SamplerState*			WindowRenderer::msSamplerLinear = nullptr;
	DirectX::XMMATRIX			WindowRenderer::msWorld;
	DirectX::XMMATRIX			WindowRenderer::msView;
	DirectX::XMMATRIX			WindowRenderer::msProjection;
	DirectX::XMFLOAT4			WindowRenderer::msMeshColor = DirectX::XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);

	DeviceResources*			WindowRenderer::msDeviceResources = nullptr;
	uint32_t					WindowRenderer::msIndexCount = 0u;
	uint32_t					WindowRenderer::msFrameCount = 0u;
	ID3D11InputLayout*			WindowRenderer::msInputLayoutExtended;
	
	//--------------------------------------------------------------------------------------
	// Clean up the objects we've created
	//--------------------------------------------------------------------------------------
	void WindowRenderer::cleanupDevice()
	{
		if (msSamplerLinear)
		{
			msSamplerLinear->Release();
		}
		if (msTextureRv)
		{
			msTextureRv->Release();
		}
		if (msConstantBufferNeverChanges)
		{
			msConstantBufferNeverChanges->Release();
		}
		if (msConstantBufferChangeOnResize)
		{
			msConstantBufferChangeOnResize->Release();
		}
		if (msConstantBufferChangesEveryFrame)
		{
			msConstantBufferChangesEveryFrame->Release();
		}
		if (msVertexBuffer)
		{
			msVertexBuffer->Release();
		}
		if (msIndexBuffer)
		{
			msIndexBuffer->Release();
		}
		if (msVertexLayout)
		{
			msVertexLayout->Release();
		}
		if (msVertexShader)
		{
			msVertexShader->Release();
		}
		if (msPixelShader)
		{
			msPixelShader->Release();
		}
		if (msDepthStencil)
		{
			msDepthStencil->Release();
		}
		if (msDepthStencilView)
		{
			msDepthStencilView->Release();
		}
		if (msRenderTargetView)
		{
			msRenderTargetView->Release();
		}
	}

	//--------------------------------------------------------------------------------------
	// Helper for compiling shaders with D3DCompile
	//
	// With VS 11, we could load up prebuilt .cso files instead...
	//--------------------------------------------------------------------------------------
	int32_t WindowRenderer::compileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		// szFileName ���� �̸�
		// szEntryPoint �� ������ � �Լ� �������ҰŴ�
		// szShaderModel ���̴� ��
		HRESULT hResult = S_OK;

		// ������ �ɼ�
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
		// �̰� ���� ������. ���̴� ������� �� ���� ��. �����ϸ� �ϱ� ������ ���� �������� �������� ����� ����

		// Disable optimizations to further improve shader debugging
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		// ID3DBlob �ؽ�Ʈ ������ ���𰡸� ������ ��. ���̴� ������ �� ���� �ֳ�...?
		// �̸� ���̴� ������ �صΰ� ��Ÿ�ӿ� ���̴� ���̳ʸ��� �ٷ� Blob�� �������� ������ ���� ����� �� ����
		// ��κ��� ��� ���̴��� �ɼǿ� ���� ������ �ٸ��� �ؾ��� ���� ����
		// �̷� �� ifdef�� ������ ��ÿ� �־��༭ �ٸ��� ���� ����
		ID3DBlob* pErrorBlob = nullptr;

		// GLUTó�� D3DX��� ���� ���̺귯���� ����. 12���� �����
		// MS�� ��� ���� 11���� D3DX ���� ����
		// d3dx���� prod �������� ���־� 12 ������ �� ����
		// ���� �ι�° �Ű������� PDefines�ε� ���⿡ ifdef�� �ش��ϴ� �� �� �־���� �� ����
		// ���̴� ������ ���Ƶ� ������ �� def�� ���� �ٸ� ���̳ʸ� �� ����
		// �Ź� ������ �ٽ��ϸ� �������ϱ� ���̴� ĳ�� ���
		// �� ������ �� ���̴� ������ ���� ������, ���� ���̴� ĳ�ö� ���ؼ�, 
		// ������ / ���빰 �ٲ������ �������ؼ� ���̳ʸ��� ĳ�� �ʿ� ����
		// ���̴� ĳ�� ���̳ʸ��κ��� ���̴� ����
		// ���� ���� ������ �׳� ĳ�ÿ��� �ٷ� �о ����
		hResult = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
		if (FAILED(hResult))
		{
			if (pErrorBlob)
			{
				OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
				pErrorBlob->Release();
			}
			return hResult;
		}
		if (pErrorBlob)
		{
			pErrorBlob->Release();
		}

		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	// Destroy Renderer
	//--------------------------------------------------------------------------------------
	void WindowRenderer::Destroy()
	{
		cleanupDevice();
		msDeviceResources->Destroy();
	}

	//--------------------------------------------------------------------------------------
	// Initialize Renderer
	//--------------------------------------------------------------------------------------
	int32_t WindowRenderer::Init(HINSTANCE hInstance, int nCmdShow, LPCWSTR className, LPCWSTR windowName)
	{
		int32_t hResult = FAILED(initWindow(hInstance, nCmdShow, className, windowName));
		if (FAILED(hResult))
		{
			return hResult;
		}

		hResult = initDevice();
		if (FAILED(hResult))
		{
			Destroy();
			return hResult;
		}

		return hResult;
	}

	//--------------------------------------------------------------------------------------
	// Create Direct3D device and swap chain
	//--------------------------------------------------------------------------------------
	HRESULT WindowRenderer::initDevice()
	{
		HRESULT hResult = S_OK;

		RECT rect;    // ȭ�� ũ��
		GetClientRect(msHWindow, &rect);
		UINT width = rect.right - rect.left;
		UINT height = rect.bottom - rect.top;

		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] = {
			D3D_DRIVER_TYPE_HARDWARE,   // GPU��
			D3D_DRIVER_TYPE_WARP,       // CPU��
			D3D_DRIVER_TYPE_REFERENCE,  // ��Ʈ�� GPU ������ ����
		};
		UINT numDriverTypes = ARRAYSIZE(driverTypes);

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0, // �� �־ �Ǳ� �ϴµ�, �ֿ켱���� ���ϴ� �� ������ �Ǿ��ִ� ��. �ǳ� ���δ� GPU�� ����
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
		{
			msDriverType = driverTypes[driverTypeIndex];
			hResult = D3D11CreateDevice(nullptr, msDriverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
				D3D11_SDK_VERSION, &msD3dDevice, &msFeatureLevel, &msImmediateContext);

			if (hResult == E_INVALIDARG)
			{
				// DirectX 11.0 platforg will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
				hResult = D3D11CreateDevice(nullptr, msDriverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
					D3D11_SDK_VERSION, &msD3dDevice, &msFeatureLevel, &msImmediateContext);
				// ������ featureLevel�� msFeatureLevel�� ��������
			}

			if (SUCCEEDED(hResult))
			{
				break;
			}
		}
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
		IDXGIFactory1* dxgiFactory = nullptr;
		{
			IDXGIDevice* dxgiDevice = nullptr;
			hResult = msD3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
			if (SUCCEEDED(hResult))
			{
				IDXGIAdapter* adapter = nullptr;
				hResult = dxgiDevice->GetAdapter(&adapter);
				if (SUCCEEDED(hResult))
				{
					hResult = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
					adapter->Release();
				}
				dxgiDevice->Release();
			}
		}
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Create swap chain
		IDXGIFactory2* dxgiFactory2 = nullptr;
		hResult = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory2));
		if (dxgiFactory2)
		{
			// DirectX 11.1 or later
			hResult = msD3dDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&msD3dDevice1));
			if (SUCCEEDED(hResult))
			{
				static_cast<void>(msImmediateContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&msImmediateContext1)));
			}

			DXGI_SWAP_CHAIN_DESC1 sd = {};
			sd.Width = width;
			sd.Height = height;
			sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.BufferCount = 1;

			hResult = dxgiFactory2->CreateSwapChainForHwnd(msD3dDevice, msHWindow, &sd, nullptr, nullptr, &gSwapChain1);
			if (SUCCEEDED(hResult))
			{
				hResult = gSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&gSwapChain));
			}

			dxgiFactory2->Release();
		}
		else
		{
			// DirectX 11.0 systeg
			DXGI_SWAP_CHAIN_DESC sd = {};   // w buffering. flip / bullet
											// flip: front buffer�� back buffer�� ���������� �ٲ�
											// bullet: back buffer�� front buffer�� ����
			sd.BufferCount = 1; // �̰ŷ� ���� ���۸� / Ʈ���� ���۸� ���� ����
			sd.BufferDesc.Width = width;
			sd.BufferDesc.Height = height;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;  // UNORM -> 0.0 ~ 1.0
			sd.BufferDesc.RefreshRate.Numerator = 60;   // 60 fps
			sd.BufferDesc.RefreshRate.Denominator = 1;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow = msHWindow;
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
			sd.Windowed = TRUE; // window ����?

			hResult = dxgiFactory->CreateSwapChain(msD3dDevice, &sd, &gSwapChain);
		}

		// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
		dxgiFactory->MakeWindowAssociation(msHWindow, DXGI_MWA_NO_ALT_ENTER);

		dxgiFactory->Release();

		if (FAILED(hResult))
		{
			return hResult;
		}

		// Create a render target view
		// view��� ���� ���� ���ҽ��� ��� �����ϰ�, �� ���ҽ��� ����ϱ� ���� �Ļ� �������̽�. ������ read-only
		// shader resource view�� shader �ȿ��� ����� resource�ε�, �� �ٿ��� �ؽ�ó. �̰� �� ���� / ���� ���� ����
		// �� �� shader resource view�� �ƴ�
		// �ؽ�ó�� �о ����Ϸ���, �ش� �ؽ�ó�� ����Ű�� �����͸� ���� �������̽��� �����ؼ� �����ֱ� (shader resource view)
		// ȭ�� ���۵� �ؽ�ó ���ҽ�. ���⿡ write�� �ҰŸ� render target view�� �Ǿ����
		ID3D11Texture2D* pBackBuffer = nullptr;
		hResult = gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
		// swap chain�� ���� �ִ� �� ���� �����
		if (FAILED(hResult))
		{
			return hResult;
		}

		// ID3D11Device         ��ü
			// ���� / �����ϴ� ���
		// ID3D11DeviceContext  �帧
			// �׸��� / ���� �ٲٱ�. ��ü���� ���� ����
			// ���� ���¿��� �ؽ�ó ����, �����, ȭ�� Ŭ���� ���̶�� �� ���� "���� ����"�� context
			// opengl�� �Ϲ������� ���� �������ϰ� ���� ���´� �ϳ���� �����ϰ� �������� ȣ��
			// 12���ʹ� ��Ƽ ������ ������ �����ؼ� ��������� context ����. context ���� ���� �� �� �ִ�
			// ���� 12��� �ؼ� ���� context�� ���� �� ��������� ����. ���� ���� �ִµ� �� �� �ϳ��� �ַ� ����ϴ� ��.
				// �װ� immediate context
		// ID3D11RenderTargetView ȭ�鿡 write �Ǵ� ����
			// ���̴��� ���� ȭ�鿡 �׸���, ���������� ȭ�� Ŭ������ �� ���
		hResult = msD3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &msRenderTargetView);
		pBackBuffer->Release(); // �̰� �� ������?
								// gRenderTargetView�� pBackBuffer�� �����ؼ� ref count�� 1 �����ع����� ����
								// ���� pBackBuffer �� �� �����״ϱ�...
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Create depth stencil texture
		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width = width;
		descDepth.Height = height;
		descDepth.MipLevels = 1;
		descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;
		descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;
		descDepth.MiscFlags = 0;
		hResult = msD3dDevice->CreateTexture2D(&descDepth, nullptr, &msDepthStencil);
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		hResult = msD3dDevice->CreateDepthStencilView(msDepthStencil, &descDSV, &msDepthStencilView);
		if (FAILED(hResult))
		{
			return hResult;
		}

		// gRenderTargetView�� ���� �� �������� �׸� ����?
		// viewport�� 3ds max ����ٰ� �����ϸ� ȭ�� 4�����ؼ�
		// ���� �������ϸ� ���� �ϳ��� viewport�� ���� 4������ ����ŭ �־ 
		// �������� �� ���� RSSetViewports���ָ� ��
		// Setup the viewport
		D3D11_VIEWPORT vp;
		vp.Width = static_cast<FLOAT>(width);
		vp.Height = static_cast<FLOAT>(height);
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		// Rasterizer Stage
		msImmediateContext->RSSetViewports(1, &vp);

		// ȭ���� �׸� ���ۿ� ���� ���� ���� �Ϸ�

		// ���̴� ������
		// 9 -> 10 �Ѿ �� iPhone ��õǸ鼭 ����� ȯ���� �������鼭 9 -> 11�� �ȳѾ
		// �� ������ shader. DX9������ ���̴��� �ɼ��̾��µ� ���Ŀ� ���̴��� �ʼ��� ��
		// ���������� fvf�� �����ؼ� ���� ���������� ��� (���̴� �� ����)
		// 9.3.9.0c ������ GPU�� �������� ���̴� ��ĥ ����
		// ���� ���������� ������. ���̴� �ϳ��� ������ ������ �ȵ�
		// Compile the vertex shader
		ID3DBlob* pVSBlob = nullptr;
		// shader ���� vs 4.0�̱���~
		// 4.0�� ��� 10 �����̰� 11�� 5.0�����ε� ������ �� ȣȯ ��
		// �����̴ϱ� directx device�� ��� �ִ� �� �ƴϰڱ���~
		// �̰� �� ���� �Լ���
		hResult = compileShaderFromFile(L"Graphics/Shader/DirectXTest.fxh", "VS", "vs_4_0", &pVSBlob);
		if (FAILED(hResult))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return hResult;
		}

		// Create the vertex shader
		// ������ ��ü����. Blob���� get�ϱ�
		// ���� ���� ���� ���� ���� ���� Compile Shader���� �ɸ�
		// ���̴� �ڵ尡 �����ѵ� ����ī�尡 feature level�� 10.0 ���� �����ϴµ�
		// ���̴� ��带 5.0�� ¥�� �����ϸ� �ǰ� ���̳ʸ��� ���̴� ������ �ȵ�

		// ������ �Լ��� �����ߴ��� ���� ������ watch���� @err, hr�ϸ� ���� �����忡�� ������ �Լ��� ���� ������ �� �� �� ����
		hResult = msD3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &msVertexShader);
		if (FAILED(hResult))
		{
			pVSBlob->Release();
			return hResult;
		}

		// layout�� GPU�� ������ ���ؽ��� � Ÿ������, ������Ұ� ��� �Ǵ��� �˷��ִ� ��
		// DirectXTest.fxh �ڵ� �����غ���
		// Vulkan�̳� Metal, DX11 �̻��� struct�� ��.
		// �� ����ó�� simple�� Shader�� ��� 16byte ¥�� float ���� �ϳ���
		// hlsl / glsl ���� ū �κ��� �տ� struct �����ϴ� �κ�
		// glsl�� uniform���� string���� �̸� ����
		// hlsl�� ����ü ������ �ۼ�
		// "POSITION"�� �׳� D3D Semantic��
		// 32bit RGB Float. �Է� ���� ��ü�� ������ float4. 16 byte ���ĵǾ��־��
		// layout�� ���� ���� ������. position ��ǥ, �ؽ�ó ��ǥ �� �����ؼ�
		// layout�� �������� ���� �ٸ��� ���� ���� ���� ����
		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(layout);

		// gVertexLayout. ID3D11InputLayout ��ü. COM ��ü��.
		// Create the input layout
		hResult = msD3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
			pVSBlob->GetBufferSize(), &gVertexLayout);
		pVSBlob->Release();
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Compile the pixel shader
		ID3DBlob* pPSBlob = nullptr;
		hResult = compileShaderFromFile(L"Graphics/Shader/DirectXTest.fxh", "PS", "ps_4_0", &pPSBlob);
		if (FAILED(hResult))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return hResult;
		}

		// Create the pixel shader
		hResult = msD3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &msPixelShader);
		pPSBlob->Release();
		if (FAILED(hResult))
		{
			return hResult;
		}

		// XMFLOAT3 32bit
		// LHS. x ����(�ʺ�) y ����(����) z ����
		// �� ���������� ȭ�� ���ۿ��� �ٷ� �� �� �ְ� x, y�� -1.0 ~ 1.0, z�� 0.0 ~ 1.0���� �־��ִ� ��
		// Matrix ��ȯ �ϳ��� ����.
		// Create vertex buffer
		SimpleVertex vertices[] = {
			{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
			{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
			{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },

			{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
			{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
			{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
			{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },

			{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
			{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
			{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },

			{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
			{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },

			{ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
			{ DirectX::XMFLOAT3(-1.0f, 1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },

			{ DirectX::XMFLOAT3(-1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, -1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) },
			{ DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) },
			{ DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) },
		};
		D3D11_BUFFER_DESC bd = {};
		// IMMUTABLE: ������ ��� �� ���ۿ� ���� �����ͷ� ������ ���� ���� �ǵ帮�� �ʱ�
		// DYNAMIC: �� ������ �� �ɾ ���. ������ DEFAULT ���� ���. �ִ��� GPU �޸� �ȿ� ���ҽ� ��ġ. DYNAMIC ���� 
		// �� ������ ���� �� �� �ִٴ� ��. �ý��� �޸𸮿� ���� GPU �޸𸮿� ���������� �����ϴ� ����
		// STAGING�� GPU �޸� �ƴ�. ���� GPU�� ���� ����. DX ���ҽ� �ٷ�� ������� copy�� �� ȣȯ�� ������ ��
			// GPU �޸� �ȿ� � ���� �˰� ������ ȭ�� ������ �����͸� staging���� copy�ؼ� �о����.
			// GPU �޸𸮸� �ٷ� �� ����
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * 24;
		// ���� �޸� ����
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		// �ؽ�ó
		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = vertices;
		hResult = msD3dDevice->CreateBuffer(&bd, &InitData, &gVertexBuffer);
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Create index buffer
		WORD indices[] = {
			3,1,0,
			2,1,3,

			6,4,5,
			7,4,6,

			11,9,8,
			10,9,11,

			14,12,13,
			15,12,14,

			19,17,16,
			18,17,19,

			22,20,21,
			23,20,22
		};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;
		hResult = msD3dDevice->CreateBuffer(&bd, &InitData, &gIndexBuffer);
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Create the constant buffer
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBufferNeverChanges);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hResult = msD3dDevice->CreateBuffer(&bd, nullptr, &msConstantBufferNeverChanges);
		if (FAILED(hResult))
		{
			return hResult;
		}

		bd.ByteWidth = sizeof(ConstantBufferChangeOnResize);
		hResult = msD3dDevice->CreateBuffer(&bd, nullptr, &msConstantBufferChangeOnResize);
		if (FAILED(hResult))
		{
			return hResult;
		}

		bd.ByteWidth = sizeof(ConstantBufferChangesEveryFrame);
		hResult = msD3dDevice->CreateBuffer(&bd, nullptr, &msConstantBufferChangesEveryFrame);
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Load the Texture
		hResult = cave::DdsTextureLoader::CreateDDSTextureFromFile(msD3dDevice, L"Graphics/Resource/seafloor.dds", nullptr, &msTextureRv);
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Create the sample state
		D3D11_SAMPLER_DESC sampDesc = {};
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		hResult = msD3dDevice->CreateSamplerState(&sampDesc, &gSamplerLinear);
		if (FAILED(hResult))
		{
			return hResult;
		}

		// Initialize the world matrix
		msWorld = DirectX::XMMatrixIdentity();

		// Initialize the view matrix
		DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 3.0f, -6.0f, 0.0f);
		DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		gView = DirectX::XMMatrixLookAtLH(eye, at, up);

		ConstantBufferNeverChanges constantBufferNeverChanges;
		constantBufferNeverChanges.mView = DirectX::XMMatrixTranspose(gView);
		msImmediateContext->UpdateSubresource(msConstantBufferNeverChanges, 0, nullptr, &constantBufferNeverChanges, 0, 0);

		// Initialize the projection matrix
		gProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, width / static_cast<FLOAT>(height), 0.01f, 100.0f);

		ConstantBufferChangeOnResize constantBufferChangesOnResize;
		constantBufferChangesOnResize.mProjection = DirectX::XMMatrixTranspose(gProjection);
		msImmediateContext->UpdateSubresource(msConstantBufferChangeOnResize, 0, nullptr, &constantBufferChangesOnResize, 0, 0);

		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	// Register class and create window
	//--------------------------------------------------------------------------------------
	HRESULT WindowRenderer::initWindow(HINSTANCE hInstance, int nCmdShow, LPCWSTR className, LPCWSTR windowName)
	{
		// Register class
		WNDCLASSEX windowClassEx;
		windowClassEx.cbSize = sizeof(WNDCLASSEX);
		windowClassEx.style = CS_HREDRAW | CS_VREDRAW;
		windowClassEx.lpfnWndProc = wndProc;
		windowClassEx.cbClsExtra = 0;
		windowClassEx.cbWndExtra = 0;
		windowClassEx.hInstance = hInstance;
		windowClassEx.hIcon = LoadIcon(hInstance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1));
		windowClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
		windowClassEx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		windowClassEx.lpszMenuName = nullptr;
		windowClassEx.lpszClassName = className;
		windowClassEx.hIconSm = LoadIcon(windowClassEx.hInstance, reinterpret_cast<LPCTSTR>(IDI_TUTORIAL1));
		if (!RegisterClassEx(&windowClassEx))
		{
			return E_FAIL;
		}

		// Create window
		msHInstance = hInstance;
		RECT rect = {0, 0, 800, 600};
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
		msHWindow = CreateWindow(className, windowName,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance,
			nullptr);
		if (!msHWindow)
		{
			return E_FAIL;
		}

		ShowWindow(msHWindow, nCmdShow);

		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	// Render a frame
	//--------------------------------------------------------------------------------------
	void WindowRenderer::Render()
	{
		 ID3D11DeviceContext* context = msDeviceResources->GetDeviceContext();

		ID3D11RenderTargetView* renderTarget = msDeviceResources->GetRenderTarget();
		ID3D11DepthStencilView* depthStencil = msDeviceResources->GetDepthStencil();

		//
		// Update variables for the first cube
		//
		context->UpdateSubresource(msConstantBuffer, 0, nullptr, &msConstantBufferData, 0, 0);


		// ���� layout ����, topology �ٲٴ°�, vertex buffer �ٲٴ°� rendering �Լ� �ȿ� ���� ��찡 ����
		// vertex buffer�� pixel shader �� ���� �ʼ�
		// Clear the back buffer 
		context->ClearRenderTargetView(renderTarget, DirectX::Colors::MidnightBlue);

		//
		// Clear the depth buffer to 1.0 (max depth)
		//
		context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH, 1.0f, 0);

		// ���� target ���� ����. ������ 8 ����� ����
		// ������ parameter�� depth buffer.
		// �տ� OM �پ��ִٴ� �� Output Manager. ���ۿ� ���� ���ϰ� �ϴ� ���� ���ξ OM���� �Ǿ�����
		// �츮�� �׸� buffer ����
		context->OMSetRenderTargets(1, &renderTarget, depthStencil);

		// ���� context�� �����ֱ�
		// Set vertex buffer
		uint32_t stride = sizeof(SimpleVertex);
		uint32_t offset = 0;
		context->IASetVertexBuffers(0, 1, &msVertexBuffer, &stride, &offset);

		// Set index buffer
		context->IASetIndexBuffer(msIndexBuffer, DXGI_FORMAT_R16_UINT, 0);


		// Set primitive topology
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// IA. Input Assembly
		// Set the input layout
		context->IASetInputLayout(msVertexLayout);

		//
		// Render the first cube
		//
		context->VSSetShader(msVertexShader, nullptr, 0);
		context->VSSetConstantBuffers(0, 1, &msConstantBufferNeverChanges);
		context->PSSetShader(msPixelShader, nullptr, 0);
		context->PSSetConstantBuffers(2, 1, &msConstantBufferChangesEveryFrame);
		context->PSSetShaderResources(0, 1, &msTextureRv);
		context->PSSetSamplers(0, 1, &msSamplerLinear);
		// ���� production level���� Draw���ٴ� DrawIndexed�� �� ���� ���
		// ù��°�� ���ؽ� ����. 3
		// back buffer�� �׸���
		//context->Draw(3, 0);
		context->DrawIndexed(msIndexCount, 0, 0);        // 36 vertices needed for 12 triangles in a triangle list

		// ���� flip�̳� swap ���ؼ� front buffer�� ����
		// front buffer�� ������
		// ���� �׷����� ������ GPU Driver���� �ٸ�. ������ ���������� �񵿱�� �Ͼ
		// Present the information rendered to the back buffer to the front buffer (the screen)
		// gSwapChain->Present(0, 0);
	}

	//--------------------------------------------------------------------------------------
	// Called every time the application receives a message
	//--------------------------------------------------------------------------------------
	LRESULT CALLBACK WindowRenderer::wndProc(HWND hWindow, UINT message, WPARAM wParam, LPARAM lParam)
	{
		PAINTSTRUCT paintStruct;
		HDC handleDeviceContext;

		switch (message)
		{
		case WM_PAINT:
			handleDeviceContext = BeginPaint(hWindow, &paintStruct);
			EndPaint(hWindow, &paintStruct);
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

	int32_t WindowRenderer::Init(DeviceResources* deviceResources)
	{
		msFrameCount = 0u;
		msDeviceResources = deviceResources;
	}

	void WindowRenderer::CreateDeviceDependentResources()
	{
		auto createShadersTask = Concurrency::create_task(
			[this]()
			{
				createShaders();
			}
		);

		auto createCubeTask = CreateShadersTask.then(
			[this]()
			{
				createCube();
			}
		);
	}

	void WindowRenderer::CreateWindowSizeDependentResources()
	{
		createView();
		createPerspective();
	}

	void WindowRenderer::Update()
	{
		// Update our time
		static float t = 0.0f;
		D3D_DRIVER_TYPE driverType = mDeviceResources->GetDriverType();
		if(driverType == D3D_DRIVER_TYPE_REFERENCE)
		{
			t += static_cast<float>(XM_PI) * 0.0125f;
		}
		else
		{
			static uint64_t timeStart = 0ul;
			uint64_t timeCur = GetTickCount64();
			if (timeStart == 0)
			{
				timeStart = timeCur;
			}
			t = (timeCur - timeStart) / 1000.0f;
		}

		// Rotate cube around the origin
		msConstantBufferData.mWorld = XMMatrixRotationY(t);

		// Modify the color
		msConstantBufferData.mMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
		msConstantBufferData.mMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
		msConstantBufferData.mMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

		if (msFrameCount == UINT32_MAX)
		{
			msFrameCount = 0;
		}
	}

	int32_t WindowRenderer::createShaders()
	{
		int32_t result = S_OK;

		// Use the Direct3D device to load resources into graphics memory.
		ID3D11Device* device = mDeviceResources->GetDevice();
		
		// Compile the vertex shader
		ID3DBlob* pVSBlob = nullptr;
		result = CompileShaderFromFile(L"DirectXTest.fxh", "VS", "vs_4_0", &pVSBlob);
		if(FAILED(result))
		{
			MessageBox(nullptr,
						L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return result;
		}

		// Create the vertex shader
		result = device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &msVertexShader);
		if( FAILED( result ) )
		{    
			pVSBlob->Release();
			return result;
		}

		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		uint32_t numElements = ARRAYSIZE(layout);

		// Create the input layout
		result = device->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
											pVSBlob->GetBufferSize(), &msVertexLayout );
		pVSBlob->Release();
		if(FAILED(result))
		{
			return result;
		}

		// Compile the pixel shader
		ID3DBlob* pPSBlob = nullptr;
		result = CompileShaderFromFile(L"DirectXTest.fxh", "PS", "ps_4_0", &pPSBlob);
		if(FAILED(result))
		{
			MessageBox(nullptr,
						L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return result;
		}

		// Create the pixel shader
		result = device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &msPixelShader);
		pPSBlob->Release();
		if(FAILED(result))
		{
			return result;
		}

		// Create the constant buffers
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBufferNeverChanges);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		result = device->CreateBuffer(&bd, nullptr, &msConstantBufferNeverChanges);
		if(FAILED(result))
		{
			return result;
		}
		
		bd.ByteWidth = sizeof(ConstantBufferChangeOnResize);
		result = device->CreateBuffer(&bd, nullptr, &msConstantBufferChangeOnResize);
		if(FAILED(result))
		{
			return result;
		}
		
		bd.ByteWidth = sizeof(ConstantBufferChangesEveryFrame);
		result = device->CreateBuffer( &bd, nullptr, &msConstantBufferChangesEveryFrame );
		if(FAILED(result))
		{
			return result;
		}

		// Load the Texture
		result = cave::DdsTextureLoader::CreateDDSTextureFromFile(device, L"seafloor.dds", nullptr, &msTextureRv);
		if(FAILED(result))
		{
			return result;
		}

		// Create the sample state
		D3D11_SAMPLER_DESC sampDesc = {};
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		result = device->CreateSamplerState(&sampDesc,&msSamplerLinear);
		if(FAILED(result))
		{
			return result;
		}
		
		return result;
	}

	int32_t WindowRenderer::createCube()
	{
		int32_t result = S_OK;

		// Use the Direct3D device to load resources into graphics memory.
		ID3D11Device* device = mDeviceResources->GetDevice();

		// Create vertex buffer
		SimpleVertex vertices[] =
		{
			{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
			{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
			{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
			{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },

			{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
			{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
			{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
			{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

			{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
			{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
			{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
			{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },

			{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
			{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
			{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
			{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },

			{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
			{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
			{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
			{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },

			{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
			{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
			{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
			{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
		};

		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * 24;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = vertices;
		result = device->CreateBuffer(&bd, &InitData, &msVertexBuffer);
		if(FAILED(result))
		{
			return result;
		}

		// Create index buffer
		uint16_t indices[] =
		{
			3,1,0,
			2,1,3,

			6,4,5,
			7,4,6,

			11,9,8,
			10,9,11,

			14,12,13,
			15,12,14,

			19,17,16,
			18,17,19,

			22,20,21,
			23,20,22
		};

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(uint16_t) * 36;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = indices;
		result = device->CreateBuffer(&bd, &InitData, &mIndexBuffer);
		if(FAILED(result))
		{
			return result;
		}

		return result;
	}

	void WindowRenderer::createView()
	{
		// Initialize the view matrix
		XMVECTOR eye = DirectX::XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
		XMVECTOR at = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
		XMVECTOR up = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
		msView = DirectX::XMMatrixLookAtLH(eye, at, up);
	}

	void WindowRenderer::createPerspective()
	{
		msView = DirectX::XMMatrixIdentity();

		float aspectRatioX = msDeviceResources->GetAspectRatio();
		float aspectRatioY = aspectRatioX < (16.0f / 9.0f) ? aspectRatioX / (16.0f / 9.0f) : 1.0f;

		ID3D11DeviceContext* context = msDeviceResources->GetDeviceContext();

		ConstantBufferNeverChanges constantBufferNeverChanges;
		constantBufferNeverChanges.mView = DirectX::XMMatrixTranspose(msView);
		context->UpdateSubresource(msConstantBufferNeverChanges, 0, nullptr, &constantBufferNeverChanges, 0, 0);

		// 2.0f * std::atan(std::tan(DirectX::XMConvertToRadians(70) * 0.5f)
		msProjection= XMMatrixPerspectiveFovLH(XM_PIDIV4, aspectRatioX, 0.01f, 100.0f);

		ConstantBufferChangeOnResize constantBufferChangesOnResize;
		constantBufferChangesOnResize.mProjection = DirectX::XMMatrixTranspose(msProjection);
		context->UpdateSubresource(msConstantBufferChangeOnResize, 0, nullptr, &constantBufferChangesOnResize, 0, 0);
}
#endif