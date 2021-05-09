/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "Device/DeviceResources.h"
#include "Sprite/Sprite.h"
#include "Shader/Shader.h"

namespace cave
{
	class GenericRenderer
	{
	public:
		GenericRenderer(DeviceResources* deviceResources, MemoryPool& pool = gCoreMemoryPool);
		virtual ~GenericRenderer();

		GenericRenderer(const GenericRenderer&) = delete;
		GenericRenderer& operator=(const GenericRenderer&) = delete;
		GenericRenderer& operator=(const GenericRenderer&&) = delete;

		virtual void CreateDeviceDependentResources() = 0;
		virtual void CreateWindowSizeDependentResources() = 0;
    	virtual void Update() = 0;
    	virtual void Render() = 0;
		virtual void Destroy();

		virtual void AddSprite(Sprite* object);
		virtual void AddShader(Shader* shader);

		virtual bool WindowShouldClose() = 0;
		DeviceResources* const GetDeviceResources() const;
	protected:
		virtual eResult createShader(Shader& shader) = 0;
		virtual eResult createShaders() = 0;
		virtual eResult createObject(Sprite& object) = 0;
		virtual eResult createObjects() = 0;
		virtual void createView() = 0;
		virtual void createPerspective() = 0;

		MemoryPool* mPool = nullptr;

#ifdef __WIN32__
		DirectX::XMMATRIX mView;
		DirectX::XMMATRIX mProjection;
#else
		glm::mat4 mView  = glm::mat4(1.0f);
		glm::mat4 mProjection = glm::mat4(1.0f);
#endif
		DeviceResources* mDeviceResources = nullptr;
		uint32_t mIndexCount = 0u;
		uint32_t mFrameCount = 0u;

		std::vector<Sprite*> mSprites;
		std::vector<Shader*> mShaders;
	};
}