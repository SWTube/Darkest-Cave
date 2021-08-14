/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Renderer/WindowsRenderer.h"

#ifdef __WIN32__
#include <ppltasks.h>

#include "Debug/Log.h"


namespace cave
{
	//--------------------------------------------------------------------------------------
	// Destroy Renderer
	//--------------------------------------------------------------------------------------
	WindowsRenderer::~WindowsRenderer()
	{
		Destroy();
	}

	eResult WindowsRenderer::Init(Window* window)
	{
		CreateDeviceDependentResources();
		CreateWindowSizeDependentResources(window);
		// set camera
		mCamera = reinterpret_cast<Camera*>(mPool->Allocate(sizeof(Camera)));
		new(mCamera) Camera();
		if (mCamera == nullptr)
		{
			return eResult::CAVE_OUT_OF_MEMORY;
		}
		mCamera->SetPosition(0.0f, 0.0f, -100.f);
		
		//set TextureManager device.
		TextureManager::GetInstance().SetDevice(mDeviceResources->GetDevice());

		mBufferManager = reinterpret_cast<BufferManager*>(mPool->Allocate(sizeof(BufferManager)));
		new(mBufferManager) BufferManager();
		mBufferManager->Init(mDeviceResources, 1000);

		// set color shader
		// set texture shader
		mShader = reinterpret_cast<Shader*>(mPool->Allocate(sizeof(Shader)));
		new(mShader) cave::Shader(L"DirectXTest.fxh", *mPool);
		mShader->Compile(mDeviceResources->GetDevice());

		return eResult::CAVE_OK;
	}

	//--------------------------------------------------------------------------------------
	// Destroy Renderer
	//--------------------------------------------------------------------------------------
	void WindowsRenderer::Destroy()
	{
		GenericRenderer::Destroy();
	}

	//--------------------------------------------------------------------------------------
	// Render a frame
	//--------------------------------------------------------------------------------------
	void WindowsRenderer::Render()
	{
		ID3D11DeviceContext* context = mDeviceResources->GetDeviceContext();

		mDeviceResources->RenderStart();

		mCamera->Render();

		DirectX::XMMATRIX& worldMatrix = mDeviceResources->GetWorldMatrix();
		const DirectX::XMMATRIX& viewMatrix = mCamera->GetViewMatrix();
		//DirectX::XMMATRIX& projection = mDeviceResources->GetProjectionMatrix();
		DirectX::XMMATRIX& ortho = mDeviceResources->GetOrthoMatrix();

		// 모든 2D 렌더링을 시작하려면 Z 버퍼를 끕니다.
		//mDeviceResources->TurnZBufferOff(); // 이거 없으면 안 그려짐...
		mDeviceResources->TurnOnAlphaBlending();

		std::vector<VertexT> vertexData;
		// 3. Set Render Data ---------------------------------------------------------------------------------------------
		for (Sprite* const object : mSprites)
		{
			object->Render(mDeviceResources->GetDeviceContext());
			VertexT* vertices = object->GetVertices();
			for (unsigned int i = 0; i < 4; i++) {
				
				vertexData.push_back(vertices[i]);
			}

		}

		mBufferManager->UpdateVertexBuffer(vertexData.data(), mSprites.size());
		int count = 0;
		for (Sprite* const object : mSprites)
		{
			mShader->Render(context, object->GetIndicesCount(), count * object->GetIndicesCount(), worldMatrix, viewMatrix, ortho, object->GetTexture()->GetTexture());
			count++;
		}


		mDeviceResources->TurnOffAlphaBlending();
		//mDeviceResources->TurnZBufferOn();
		// Present the frame to the screen.
		mDeviceResources->RenderEnd();

	
	}

	eResult WindowsRenderer::CreateDeviceDependentResources()
	{
		// Instantiate the device manager class.
		mDeviceResources = reinterpret_cast<DeviceResources*>(mPool->Allocate(sizeof(DeviceResources)));
		new(mDeviceResources) DeviceResources(*mPool);
		// Create device resources.
		eResult result = mDeviceResources->CreateDeviceResources();
		if (result != eResult::CAVE_OK)
		{
			return result;
		}

		return result;
	}

	eResult WindowsRenderer::CreateWindowSizeDependentResources(Window* window)
	{
		// We have a window, so initialize window size-dependent resources.

		return 	mDeviceResources->CreateWindowResources(window);
	}

	void WindowsRenderer::Update()
	{
		for (Sprite* const object : mSprites)
		{
			object->Update();
		}

		++mFrameCount;
		if (mFrameCount == UINT32_MAX)
		{
			mFrameCount = 0u;
		}
	}


	bool WindowsRenderer::WindowShouldClose()
	{
		return false;
	}
}
#endif