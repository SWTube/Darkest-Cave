/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Renderer/WindowsRenderer.h"

#ifdef __WIN32__
#include <ppltasks.h>

#include "Debug/Log.h"
import DdsTextureLoader;

namespace cave
{
	WindowsRenderer::WindowsRenderer(DeviceResources* deviceResources)
		: GenericRenderer(deviceResources)
	{
	}

	//--------------------------------------------------------------------------------------
	// Destroy Renderer
	//--------------------------------------------------------------------------------------
	WindowsRenderer::~WindowsRenderer()
	{
		Destroy();
	}

	
	//--------------------------------------------------------------------------------------
	// Clean up the objects we've created
	//--------------------------------------------------------------------------------------
	void WindowsRenderer::cleanupDevice()
	{
		if (mConstantBufferNeverChanges)
		{
			mConstantBufferNeverChanges->Release();
		}
		if (mConstantBufferChangeOnResize)
		{
			mConstantBufferChangeOnResize->Release();
		}
	}

	//--------------------------------------------------------------------------------------
	// Destroy Renderer
	//--------------------------------------------------------------------------------------
	void WindowsRenderer::Destroy()
	{
		cleanupDevice();
		GenericRenderer::Destroy();
		mDeviceResources = nullptr;
	}

	//--------------------------------------------------------------------------------------
	// Render a frame
	//--------------------------------------------------------------------------------------
	void WindowsRenderer::Render()
	{
		ID3D11DeviceContext* context = mDeviceResources->GetDeviceContext();

		ID3D11RenderTargetView* renderTarget = mDeviceResources->GetRenderTarget();
		ID3D11DepthStencilView* depthStencil = mDeviceResources->GetDepthStencil();

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

		for (Shader& shader : mShaders)
		{
			shader.Render(context);
		}

		context->VSSetConstantBuffers(0, 1, &mConstantBufferNeverChanges);
		context->VSSetConstantBuffers(1, 1, &mConstantBufferChangeOnResize);

		for (Sprite& object : mSprites)
		{
			object.Render();
		}

		// ���� flip�̳� swap ���ؼ� front buffer�� ����
		// front buffer�� ������
		// ���� �׷����� ������ GPU Driver���� �ٸ�. ������ ���������� �񵿱�� �Ͼ
		// Present the information rendered to the back buffer to the front buffer (the screen)
		// gSwapChain->Present(0, 0);
	}

	void WindowsRenderer::CreateDeviceDependentResources()
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
		createObjects();
	}

	void WindowsRenderer::CreateWindowSizeDependentResources()
	{
		createView();
		createPerspective();
	}

	void WindowsRenderer::Update()
	{
		for (Sprite& object : mSprites)
		{
			object.Update();
		}

		++mFrameCount;
		if (mFrameCount == UINT32_MAX)
		{
			mFrameCount == 0u;
		}
	}

	eResult WindowsRenderer::createShader(Shader& shader)
	{
		return shader.Compile(mDeviceResources->GetDevice());
	}

	eResult WindowsRenderer::createObjects()
	{
		LOGDF(eLogChannel::GRAPHICS, "number of objects: %u", mSprites.size());

		for (Sprite& object : mSprites)
		{
			eResult result = object.Init(mDeviceResources->GetDevice(), mDeviceResources->GetDeviceContext(), mDeviceResources->GetWidth(), mDeviceResources->GetHeight());
			if (result != eResult::CAVE_OK)
			{
				return result;
			}

			result = object.SetInputLayout(mShaders.front().GetVertexShaderBlob());
			if (result != eResult::CAVE_OK)
			{
				return result;
			}
		}

		return eResult::CAVE_OK;
	}

	eResult WindowsRenderer::createObject(Sprite& object)
	{
		eResult result = object.Init(mDeviceResources->GetDevice(), mDeviceResources->GetDeviceContext(), mDeviceResources->GetWidth(), mDeviceResources->GetHeight());
		if (result != eResult::CAVE_OK)
		{
			return result;
		}

		result = object.SetInputLayout(mShaders.front().GetVertexShaderBlob());
		if (result != eResult::CAVE_OK)
		{
			return result;
		}

		return result;
	}

	eResult WindowsRenderer::createShaders()
	{
		ID3D11Device* device = mDeviceResources->GetDevice();
		for (Shader& shader : mShaders)
		{
			if (eResult result = shader.Compile(mDeviceResources->GetDevice()); result != eResult::CAVE_OK)
			{
				return result;
			}
		}

		// Create the constant buffers
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(ConstantBufferNeverChanges);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		int32_t result = device->CreateBuffer(&bd, nullptr, &mConstantBufferNeverChanges);
		if(FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}
		
		bd.ByteWidth = sizeof(ConstantBufferChangeOnResize);
		result = device->CreateBuffer(&bd, nullptr, &mConstantBufferChangeOnResize);
		if(FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}
		
		device->Release();

		return eResult::CAVE_OK;
	}

	void WindowsRenderer::createView()
	{
		// Initialize the view matrix
		DirectX::XMVECTOR eye = DirectX::XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
		DirectX::XMVECTOR at = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
		DirectX::XMVECTOR up = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
		mView = DirectX::XMMatrixLookAtLH(eye, at, up);
	}

	void WindowsRenderer::createPerspective()
	{
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

	bool WindowsRenderer::WindowShouldClose()
	{
		return false;
	}
}
#endif