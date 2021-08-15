/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Renderer/Renderer.h"

namespace cave
{

	Renderer::Renderer()
		: mPool(reinterpret_cast<MemoryPool*>(gCoreMemoryPool.Allocate(sizeof(MemoryPool))))
		, mFrameCount(0u)
	{
		new(mPool) MemoryPool(RENDERER_MEMORY_SIZE);
	}

	Renderer::~Renderer()
	{
		Destroy();
	}

	void Renderer::Destroy()
	{

		if (mShader != nullptr)
		{
			mShader->~Shader();
			mPool->Deallocate(mShader, sizeof(Shader));
			mShader = nullptr;
		}

		if (mCamera != nullptr)
		{
			mCamera->~Camera();
			mPool->Deallocate(mCamera, sizeof(Camera));
			mCamera = nullptr;
		}

		if (mDeviceResources != nullptr)
		{
			mDeviceResources->~DeviceResources();
			mPool->Deallocate(mDeviceResources, sizeof(DeviceResources));
			mDeviceResources = nullptr;
		}

		if (mBufferManager != nullptr)
		{
			mBufferManager->~BufferManager();
			mPool->Deallocate(mBufferManager, sizeof(BufferManager));
			mBufferManager = nullptr;
		}

		if (mPool != nullptr)
		{
			mPool->~MemoryPool();
			gCoreMemoryPool.Deallocate(mPool, sizeof(MemoryPool));
			mPool = nullptr;
		}

	}

	DeviceResources* Renderer::GetDeviceResources() const
	{
		return mDeviceResources;
	}



	eResult Renderer::Init(Window* window)
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

		//Sprite::mScreenWidth = mDeviceResources->GetWidth();
		//Sprite::mScreenHeight= mDeviceResources->GetHeight();

		Sprite::SetScreenSize(mDeviceResources->GetWidth(), mDeviceResources->GetHeight());

		return eResult::CAVE_OK;
	}


	//--------------------------------------------------------------------------------------
	// Render a frame
	//--------------------------------------------------------------------------------------
	void Renderer::Render()
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
		std::vector<Sprite*> sprites = RenderQueue::GetInstance().GetRenderQueue();
		// 3. Set Render Data ---------------------------------------------------------------------------------------------
		for (Sprite* const object : sprites)
		{
			object->Render(mDeviceResources->GetDeviceContext());
			VertexT* vertices = object->GetVertices();
			for (unsigned int i = 0; i < 4; i++) {

				vertexData.push_back(vertices[i]);
			}

		}

		mBufferManager->UpdateVertexBuffer(vertexData.data(), sprites.size());

		int count = 0;
		for (Sprite* const object : sprites)
		{
			Texture* tex = object->GetTexture();
			if(tex != nullptr) // 나중에 texture가 nullptr이여도 색을 입혀서 그려주게 구현하고 싶음.
				mShader->Render(context, object->GetIndicesCount(), count * object->GetIndicesCount(), worldMatrix, viewMatrix, ortho, tex->GetTexture());
			count++;
		}


		mDeviceResources->TurnOffAlphaBlending();
		//mDeviceResources->TurnZBufferOn();
		// Present the frame to the screen.
		mDeviceResources->RenderEnd();


	}

	eResult Renderer::CreateDeviceDependentResources()
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

	eResult Renderer::CreateWindowSizeDependentResources(Window* window)
	{
		// We have a window, so initialize window size-dependent resources.

		return 	mDeviceResources->CreateWindowResources(window);
	}

	void Renderer::Update()
	{
		for (Sprite* const object : RenderQueue::GetInstance().GetRenderQueue())
		{
			object->Update();
		}

		++mFrameCount;
		if (mFrameCount == UINT32_MAX)
		{
			mFrameCount = 0u;
		}
	}


	bool Renderer::WindowShouldClose()
	{
		return false;
	}

}