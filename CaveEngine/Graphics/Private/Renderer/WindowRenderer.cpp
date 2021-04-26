/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <ppltasks.h>

#include "Debug/Log.h"
#include "Renderer/WindowRenderer.h"

#ifdef __WIN32__
import DdsTextureLoader;

namespace cave
{
	WindowRenderer::WindowRenderer(DeviceResources* deviceResources)
		: GenericRenderer(deviceResources)
	{
	}

	//--------------------------------------------------------------------------------------
	// Destroy Renderer
	//--------------------------------------------------------------------------------------
	WindowRenderer::~WindowRenderer()
	{
		Destroy();
	}

	
	//--------------------------------------------------------------------------------------
	// Clean up the objects we've created
	//--------------------------------------------------------------------------------------
	void WindowRenderer::cleanupDevice()
	{
		if (mSamplerLinear)
		{
			mSamplerLinear->Release();
		}
		if (mTextureRv)
		{
			mTextureRv->Release();
		}
		if (mConstantBufferNeverChanges)
		{
			mConstantBufferNeverChanges->Release();
		}
		if (mConstantBufferChangeOnResize)
		{
			mConstantBufferChangeOnResize->Release();
		}
		if (mConstantBufferChangesEveryFrame)
		{
			mConstantBufferChangesEveryFrame->Release();
		}
		if (mVertexBuffer)
		{
			mVertexBuffer->Release();
		}
		if (mIndexBuffer)
		{
			mIndexBuffer->Release();
		}
		if (mVertexLayout)
		{
			mVertexLayout->Release();
		}
		if (mVertexShader)
		{
			mVertexShader->Release();
		}
		if (mPixelShader)
		{
			mPixelShader->Release();
		}
	}

	//--------------------------------------------------------------------------------------
	// Helper for compiling shaders with D3DCompile
	//
	// With VS 11, we could load up prebuilt .cso files instead...
	//--------------------------------------------------------------------------------------
	int32_t WindowRenderer::compileShaderFromFile(const wchar_t* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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
		mDeviceResources = nullptr;
	}

	//--------------------------------------------------------------------------------------
	// Render a frame
	//--------------------------------------------------------------------------------------
	void WindowRenderer::Render()
	{
		ID3D11DeviceContext* context = mDeviceResources->GetDeviceContext();

		ID3D11RenderTargetView* renderTarget = mDeviceResources->GetRenderTarget();
		ID3D11DepthStencilView* depthStencil = mDeviceResources->GetDepthStencil();

		//
		// Update variables for the first cube
		//
		ConstantBufferChangesEveryFrame constantBuffer;
		constantBuffer.mWorld = DirectX::XMMatrixTranspose(mWorld);
		constantBuffer.mMeshColor = mMeshColor;
		context->UpdateSubresource(mConstantBufferChangesEveryFrame, 0, nullptr, &constantBuffer, 0, 0);


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
		context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

		// Set index buffer
		context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);


		// Set primitive topology
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// IA. Input Assembly
		// Set the input layout
		context->IASetInputLayout(mVertexLayout);

		//
		// Render the first cube
		//
		context->VSSetShader(mVertexShader, nullptr, 0);
		context->VSSetConstantBuffers(0, 1, &mConstantBufferNeverChanges);
		context->VSSetConstantBuffers(1, 1, &mConstantBufferChangeOnResize);
		context->VSSetConstantBuffers(2, 1, &mConstantBufferChangesEveryFrame);
		context->PSSetShader(mPixelShader, nullptr, 0);
		context->PSSetConstantBuffers(2, 1, &mConstantBufferChangesEveryFrame);
		context->PSSetShaderResources(0, 1, &mTextureRv);
		context->PSSetSamplers(0, 1, &mSamplerLinear);
		// ���� production level���� Draw���ٴ� DrawIndexed�� �� ���� ���
		// ù��°�� ���ؽ� ����. 3
		// back buffer�� �׸���
		//context->Draw(3, 0);
		context->DrawIndexed(mIndexCount, 0, 0);        // 36 vertices needed for 12 triangles in a triangle list

		// ���� flip�̳� swap ���ؼ� front buffer�� ����
		// front buffer�� ������
		// ���� �׷����� ������ GPU Driver���� �ٸ�. ������ ���������� �񵿱�� �Ͼ
		// Present the information rendered to the back buffer to the front buffer (the screen)
		// gSwapChain->Present(0, 0);
	}

	void WindowRenderer::CreateDeviceDependentResources()
	{
		//auto createShadersTask = Concurrency::create_task(
		//	[this]()
		//	{
		//		createShaders();
		//	}
		//);

		//auto createCubeTask = createShadersTask.then(
		//	[this]()
		//	{
		//		createCube();
		//	}
		//);
		createShaders();
		createCube();
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
			t += static_cast<float>(DirectX::XM_PI) * 0.0125f;
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
		mWorld = DirectX::XMMatrixRotationY(t);

		// Modify the color
		mMeshColor.x = (sinf(t * 1.0f) + 1.0f) * 0.5f;
		mMeshColor.y = (cosf(t * 3.0f) + 1.0f) * 0.5f;
		mMeshColor.z = (sinf(t * 5.0f) + 1.0f) * 0.5f;

		if (mFrameCount == UINT32_MAX)
		{
			mFrameCount = 0;
		}
	}

	int32_t WindowRenderer::createShaders()
	{
		int32_t result = S_OK;

		// Use the Direct3D device to load resources into graphics memory.
		ID3D11Device* device = mDeviceResources->GetDevice();
		
		// Compile the vertex shader
		ID3DBlob* pVSBlob = nullptr;
		result = compileShaderFromFile(L"Graphics/Shader/DirectXTest.fxh", "VS", "vs_4_0", &pVSBlob);
		if(FAILED(result))
		{
			MessageBox(nullptr,
						L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return result;
		}

		// Create the vertex shader
		result = device->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &mVertexShader);
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
											pVSBlob->GetBufferSize(), &mVertexLayout );
		pVSBlob->Release();
		if(FAILED(result))
		{
			return result;
		}

		// Compile the pixel shader
		ID3DBlob* pPSBlob = nullptr;
		result = compileShaderFromFile(L"Graphics/Shader/DirectXTest.fxh", "PS", "ps_4_0", &pPSBlob);
		if(FAILED(result))
		{
			MessageBox(nullptr,
						L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return result;
		}

		// Create the pixel shader
		result = device->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &mPixelShader);
		pPSBlob->Release();
		if(FAILED(result))
		{
			return result;
		}

		// Create the constant buffers
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBufferNeverChanges);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		result = device->CreateBuffer(&bd, nullptr, &mConstantBufferNeverChanges);
		if(FAILED(result))
		{
			return result;
		}
		
		bd.ByteWidth = sizeof(ConstantBufferChangeOnResize);
		result = device->CreateBuffer(&bd, nullptr, &mConstantBufferChangeOnResize);
		if(FAILED(result))
		{
			return result;
		}
		
		bd.ByteWidth = sizeof(ConstantBufferChangesEveryFrame);
		result = device->CreateBuffer( &bd, nullptr, &mConstantBufferChangesEveryFrame );
		if(FAILED(result))
		{
			return result;
		}

		// Load the Texture
		result = DdsTextureLoader::CreateDDSTextureFromFile(device, L"Graphics/Resource/seafloor.dds", nullptr, &mTextureRv);
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
		result = device->CreateSamplerState(&sampDesc,&mSamplerLinear);
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
			{ DirectX::XMFLOAT3( -1.0f, 1.0f, -1.0f ), DirectX::XMFLOAT2( 1.0f, 0.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, 1.0f, -1.0f ), DirectX::XMFLOAT2( 0.0f, 0.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT2( 0.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( -1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT2( 1.0f, 1.0f ) },

			{ DirectX::XMFLOAT3( -1.0f, -1.0f, -1.0f ), DirectX::XMFLOAT2( 0.0f, 0.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, -1.0f, -1.0f ), DirectX::XMFLOAT2( 1.0f, 0.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, -1.0f, 1.0f ), DirectX::XMFLOAT2( 1.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( -1.0f, -1.0f, 1.0f ), DirectX::XMFLOAT2( 0.0f, 1.0f ) },

			{ DirectX::XMFLOAT3( -1.0f, -1.0f, 1.0f ), DirectX::XMFLOAT2( 0.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( -1.0f, -1.0f, -1.0f ), DirectX::XMFLOAT2( 1.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( -1.0f, 1.0f, -1.0f ), DirectX::XMFLOAT2( 1.0f, 0.0f ) },
			{ DirectX::XMFLOAT3( -1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT2( 0.0f, 0.0f ) },

			{ DirectX::XMFLOAT3( 1.0f, -1.0f, 1.0f ), DirectX::XMFLOAT2( 1.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, -1.0f, -1.0f ), DirectX::XMFLOAT2( 0.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, 1.0f, -1.0f ), DirectX::XMFLOAT2( 0.0f, 0.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT2( 1.0f, 0.0f ) },

			{ DirectX::XMFLOAT3( -1.0f, -1.0f, -1.0f ), DirectX::XMFLOAT2( 0.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, -1.0f, -1.0f ), DirectX::XMFLOAT2( 1.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, 1.0f, -1.0f ), DirectX::XMFLOAT2( 1.0f, 0.0f ) },
			{ DirectX::XMFLOAT3( -1.0f, 1.0f, -1.0f ), DirectX::XMFLOAT2( 0.0f, 0.0f ) },

			{ DirectX::XMFLOAT3( -1.0f, -1.0f, 1.0f ), DirectX::XMFLOAT2( 1.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, -1.0f, 1.0f ), DirectX::XMFLOAT2( 0.0f, 1.0f ) },
			{ DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT2( 0.0f, 0.0f ) },
			{ DirectX::XMFLOAT3( -1.0f, 1.0f, 1.0f ), DirectX::XMFLOAT2( 1.0f, 0.0f ) },
		};

		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * 24;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = {};
		InitData.pSysMem = vertices;
		result = device->CreateBuffer(&bd, &InitData, &mVertexBuffer);
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
		DirectX::XMVECTOR eye = DirectX::XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
		DirectX::XMVECTOR at = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
		DirectX::XMVECTOR up = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
		mView = DirectX::XMMatrixLookAtLH(eye, at, up);
	}

	void WindowRenderer::createPerspective()
	{
		mView = DirectX::XMMatrixIdentity();

		float aspectRatioX = mDeviceResources->GetAspectRatio();
		float aspectRatioY = aspectRatioX < (16.0f / 9.0f) ? aspectRatioX / (16.0f / 9.0f) : 1.0f;

		ID3D11DeviceContext* context = mDeviceResources->GetDeviceContext();

		ConstantBufferNeverChanges constantBufferNeverChanges;
		constantBufferNeverChanges.mView = DirectX::XMMatrixTranspose(mView);
		context->UpdateSubresource(mConstantBufferNeverChanges, 0, nullptr, &constantBufferNeverChanges, 0, 0);

		// 2.0f * std::atan(std::tan(DirectX::XMConvertToRadians(70) * 0.5f)
		mProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, aspectRatioX, 0.01f, 100.0f);

		ConstantBufferChangeOnResize constantBufferChangesOnResize;
		constantBufferChangesOnResize.mProjection = DirectX::XMMatrixTranspose(mProjection);
		context->UpdateSubresource(mConstantBufferChangeOnResize, 0, nullptr, &constantBufferChangesOnResize, 0, 0);
	}

	bool WindowRenderer::WindowShouldClose()
	{
		return false;
	}
}
#endif