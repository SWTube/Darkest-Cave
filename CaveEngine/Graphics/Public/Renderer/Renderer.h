/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once


#include <string>
#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "Containers/Vertex.h"
#include "Texture/Texture.h"


import DeviceResources;
import Camera;
import Shader;
import TextureManager;
import BufferManager;
import Sprite;
import AnimatedSprite;
import RenderQueue;


namespace cave
{
	class Renderer
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


		bool WindowShouldClose();
		DeviceResources* GetDeviceResources() const;

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



		Shader* mShader;
	};
}
