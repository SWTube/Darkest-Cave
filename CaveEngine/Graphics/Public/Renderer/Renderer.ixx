/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
module;
#include <string>
#include "GraphicsApiPch.h"
#include "CoreGlobals.h"
#include "CoreTypes.h"
//#include "Texture/Texture.h"

export module Renderer;

import cave.Core.Types.Vertex;
import cave.Core.String;
import DeviceResources;
import Camera;
import Shader;
import TextureManager;
import BufferManager;
import Sprite;
import AnimatedSprite;
import RenderQueue;
import cave.Graphics.Resource.FontManager;

namespace cave
{
	export class Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(const Renderer&&) = delete;

		eResult Init(Window* window);
		eResult CreateDeviceDependentResources();
		eResult CreateWindowSizeDependentResources(Window* window = nullptr);
		void Update();
		void Render();
		void Destroy();

		bool CaptureScreenShot();
		bool WindowShouldClose();
		DeviceResources* GetDeviceResources() const;

	private:
		void drawText(TextCommand* command);
	private:
		static constexpr size_t RENDERER_MEMORY_SIZE = 1024ul * 1024ul * 10ul;
		MemoryPool* mPool = nullptr;

		Camera* mCamera = nullptr;

		DirectX::XMMATRIX	mView = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX	mProjection = DirectX::XMMatrixIdentity();

		DeviceResources* mDeviceResources = nullptr;
		BufferManager* mBufferManager = nullptr;

		uint32_t mIndexCount = 0u;
		uint32_t mFrameCount = 0u;

		IDWriteFontCollection1* mFontCollection = nullptr;
		ID2D1SolidColorBrush* mBrush = nullptr;
		IDWriteTextFormat* mTextFormat = nullptr;
		
		Shader* mShader = nullptr;
	};

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
		if (mBrush != nullptr)
		{
			mBrush->Release();
			mBrush = nullptr;
		}

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
		FontManager::GetInstance().Init(mDeviceResources->GetDWFactory());

		mBufferManager = reinterpret_cast<BufferManager*>(mPool->Allocate(sizeof(BufferManager)));
		new(mBufferManager) BufferManager();
		mBufferManager->Init(mDeviceResources, 1200);

		//// set color shader
		//// set texture shader
		mShader = reinterpret_cast<Shader*>(mPool->Allocate(sizeof(Shader)));
		new(mShader) cave::Shader(L"DirectXTest.fxh", *mPool);
		mShader->Compile(mDeviceResources->GetDevice());

		Sprite::SetScreenSize(mDeviceResources->GetWidth(), mDeviceResources->GetHeight());

		//mDeviceResources->GetDWFactory()->CreateTextFormat(
		//	L"궁서체", 0, DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL,
		//	DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL,
		//	DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL,
		//	45, L"ko", &mTextFormat);

		mDeviceResources->GetD2DRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(0,0,0,1), &mBrush);
		
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
		mDeviceResources->TurnZBufferOff(); 
		mDeviceResources->TurnOnAlphaBlending();

		//std::vector<VertexT> vertexData;
		//std::vector<Sprite*> sprites = RenderQueue::GetInstance().GetRenderQueue();
		//// 3. Set Render Data ---------------------------------------------------------------------------------------------
		//for (Sprite* const object : sprites)
		//{
		//	object->Render(mDeviceResources->GetDeviceContext());
		//	VertexT* vertices = object->GetVertices();
		//	for (unsigned int i = 0; i < 4; i++) {

		//		vertexData.push_back(vertices[i]);
		//	}

		//}
		mDeviceResources->GetD2DRenderTarget()->BeginDraw();
		std::vector<VertexT> vertexData;
		std::vector<RenderCommand*> commands = RenderQueue::GetInstance().GetRenderQueue();
		uint32_t spriteCount = 0;
		for (RenderCommand* command : commands) 
		{
			if (command->type == RenderCommand::eType::SPRITE_COMMAND)
			{
				SpriteCommand* sc = reinterpret_cast<SpriteCommand*>(command);
				for (unsigned int i = 0; i < 4; i++)
				{
					vertexData.push_back(sc->vertexData[i]);
				}
				spriteCount++;
			}

		}

		if(!vertexData.empty()) mBufferManager->UpdateVertexBuffer(vertexData.data(), spriteCount);

		spriteCount = 0;
		for (RenderCommand* command : commands)
		{
			if (command->type == RenderCommand::eType::SPRITE_COMMAND)
			{
				SpriteCommand* sc = reinterpret_cast<SpriteCommand*>(command);
				Texture* tex = sc->texture;
				if (tex != nullptr) // 나중에 texture가 nullptr이여도 색을 입혀서 그려주게 구현하고 싶음.
					mShader->Render(context, 6, spriteCount * 6, worldMatrix, viewMatrix, ortho, tex->GetTexture());
				spriteCount++;
			}
			else if(command->type == RenderCommand::eType::TEXT_COMMAND)
			{
				drawText(reinterpret_cast<TextCommand*>(command));
			}

		}
		
		mDeviceResources->TurnOffAlphaBlending();
		//mDeviceResources->TurnZBufferOn();
		// Present the frame to the screen.
		mDeviceResources->GetD2DRenderTarget()->EndDraw();
		mDeviceResources->RenderEnd();

		RenderQueue::GetInstance().ClearRenderQueue();

	}

	
	void Renderer::drawText(TextCommand* command)
	{
		ID2D1RenderTarget* renderTarget = mDeviceResources->GetD2DRenderTarget();

		mBrush->SetColor(command->color);
		renderTarget->DrawTextLayout(D2D1::Point2F(command->position.X, command->position.Y), command->textLayout, mBrush);

		command->textLayout->Release();
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
		//for (Sprite* const object : RenderQueue::GetInstance().GetRenderQueue())
		//{
		//	object->Update();
		//}

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

	bool Renderer::CaptureScreenShot()
	{
		return mDeviceResources->SaveBufferToImage(L"./ScreenShots/test.jpg");
	}
}