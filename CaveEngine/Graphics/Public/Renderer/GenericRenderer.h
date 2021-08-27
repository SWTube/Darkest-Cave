/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once
#include <string>
#include "GraphicsApiPch.h"

#include "CoreTypes.h"
//#include "Device/DeviceResources.h"
//#include "Renderer/Camera.h"
#include "Containers/Vertex.h"
//#include "Texture/Texture.h"
//#include "Sprite/Sprite.h"
//include "Sprite/AnimatedSprite.h"


import DeviceResources;
import Camera;
import Shader;
import TextureManager;
import Texture;
import BufferManager;
import Sprite;
import AnimatedSprite;

namespace cave
{
	class GenericRenderer
	{
	public:
		GenericRenderer();
		virtual ~GenericRenderer();

		GenericRenderer(const GenericRenderer&) = delete;
		GenericRenderer& operator=(const GenericRenderer&) = delete;
		GenericRenderer& operator=(const GenericRenderer&&) = delete;

		virtual eResult Init(Window* window) = 0;
		virtual eResult CreateDeviceDependentResources() = 0;
		virtual eResult CreateWindowSizeDependentResources(Window* window = nullptr) = 0;
    	virtual void Update() = 0;
    	virtual void Render() = 0;
		virtual void Destroy();

		virtual eResult AddSprite(Sprite* sprite);
		virtual eResult AddSprite(const std::filesystem::path& filePath);
		virtual eResult AddAnimatedSprite(const std::filesystem::path& filePath, std::string animationName, uint32_t frame, float duration, bool isLoof);
		virtual eResult AddAnimatedSprite(const std::filesystem::path& filePath, std::string animationName, uint32_t row, uint32_t column, uint32_t frame, float duration, bool isLoof);

		virtual eResult RemoveSprite(uint32_t index);

		virtual void SetSpriteSize(uint32_t index, uint32_t width, uint32_t height);
		virtual void SetSpritePosition(uint32_t index, Float2 position);
		virtual void SetSpriteZIndex(uint32_t index, uint32_t z);
		virtual void GetSpriteSize(uint32_t index, uint32_t& outWidth, uint32_t& outHeight) const;
		virtual void GetSpritePosition(uint32_t index, float& outX, float& outY);
		virtual Float2 GetSpritePosition(uint32_t index) const;

		virtual bool WindowShouldClose() = 0;
		DeviceResources* GetDeviceResources() const;
	protected:

		static constexpr size_t RENDERER_MEMORY_SIZE = 1024ul * 1024ul * 10ul;
		MemoryPool* mPool = nullptr;

		Camera* mCamera = nullptr;

		DirectX::XMMATRIX mProjection;

		DeviceResources* mDeviceResources = nullptr;
		BufferManager* mBufferManager = nullptr;
		uint32_t mIndexCount = 0u;
		uint32_t mFrameCount = 0u;

		std::vector<Sprite*> mSprites;
		Shader* mShader;
	};
}