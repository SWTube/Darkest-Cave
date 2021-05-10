/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Renderer/GenericRenderer.h"

namespace cave
{
	GenericRenderer::GenericRenderer(DeviceResources* deviceResources, MemoryPool& pool)
		: mPool(&pool)
		, mDeviceResources(deviceResources)
		, mFrameCount(0u)
	{
		mSprites.reserve(1);
	}

	GenericRenderer::~GenericRenderer()
	{
		Destroy();
	}

	void GenericRenderer::Destroy()
	{
		while (!mShaders.empty())
		{
			Shader& shader = mShaders.back();
			// shader.~Shader();
			mPool->Deallocate(&shader, sizeof(Shader));
			mShaders.pop_back();
		}

		while (!mSprites.empty())
		{
			Sprite& sprite = mSprites.back();
			// sprite.Destroy();
			mPool->Deallocate(&sprite, sizeof(Sprite));
			mSprites.pop_back();
		}

		mShaders.clear();
		mSprites.clear();
	}

	DeviceResources* const GenericRenderer::GetDeviceResources() const
	{
		return mDeviceResources;
	}

	void GenericRenderer::AddSprite(Sprite&& object)
	{
		assert(mPool == object.GetMemoryPool());
		mSprites.push_back(std::move(object));
		createObject(mSprites.back());
	}

	void GenericRenderer::AddShader(Shader&& shader)
	{
		mShaders.push_back(std::move(shader));
		
		createShader(mShaders.back());
		CreateWindowSizeDependentResources();
	}
}