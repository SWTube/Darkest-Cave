/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Renderer/GenericRenderer.h"

namespace cave
{

	GenericRenderer::GenericRenderer()
		: mPool(reinterpret_cast<MemoryPool*>(gCoreMemoryPool.Allocate(sizeof(MemoryPool))))
		, mFrameCount(0u)
	{
		new(mPool) MemoryPool(RENDERER_MEMORY_SIZE);
	}

	GenericRenderer::~GenericRenderer()
	{
		Destroy();
	}

	void GenericRenderer::Destroy()
	{

		while (!mSprites.empty())
		{
			Sprite* sprite = mSprites.back();
			sprite->~Sprite();
			mPool->Deallocate(sprite, sizeof(Sprite));
			sprite = nullptr;
			mSprites.pop_back();
		}
		mSprites.clear();

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

	DeviceResources* GenericRenderer::GetDeviceResources() const
	{
		return mDeviceResources;
	}
	eResult GenericRenderer::AddSprite(Sprite* sprite) 
	{
		if (sprite == nullptr) return eResult::CAVE_FAIL;

		mSprites.push_back(sprite);
		
		return eResult::CAVE_OK;
	}

	eResult GenericRenderer::AddSprite(const std::filesystem::path& filePath)
	{

		Texture* newTexture = TextureManager::GetInstance().AddTexture(filePath);
		//새 스프라이트 생성
		cave::Sprite* newSprite = reinterpret_cast<Sprite*>(mPool->Allocate(sizeof(Sprite)));
		new(newSprite) cave::Sprite(newTexture);

		eResult result = newSprite->Init(mDeviceResources->GetDevice(), mDeviceResources->GetDeviceContext(), mDeviceResources->GetWidth(), mDeviceResources->GetHeight());
		
		newSprite->SetSize(newTexture->GetWidth(), newTexture->GetHeight());
		newSprite->SetPosition(200, 200); // temp
		newSprite->SetZIndex(mSprites.size());
		mSprites.push_back(newSprite);

		return result;
	}

	eResult GenericRenderer::AddAnimatedSprite(const std::filesystem::path& filePath, std::string animationName, uint32_t frame, float duration, bool isLoof)
	{

		MultiTexture* newTexture = TextureManager::GetInstance().AddMultiTexture(filePath,frame,1,frame);
		cave::AnimatedSprite* newSprite = reinterpret_cast<AnimatedSprite*>(mPool->Allocate(sizeof(AnimatedSprite)));
		new(newSprite) cave::AnimatedSprite(animationName,newTexture,frame,duration,isLoof,mPool);

		eResult result = newSprite->Init(mDeviceResources->GetDevice(), mDeviceResources->GetDeviceContext(), mDeviceResources->GetWidth(), mDeviceResources->GetHeight());
		
		//temp setting
		newSprite->SetSize(newTexture->GetWidth(), newTexture->GetHeight());
		newSprite->SetPosition(300, 200); // temp
		newSprite->SetZIndex(mSprites.size());
		mSprites.push_back(newSprite);
		return result;
	}

	eResult GenericRenderer::AddAnimatedSprite(const std::filesystem::path& filePath, std::string animationName, uint32_t row, uint32_t column, uint32_t frame, float duration, bool isLoof)
	{
		MultiTexture* newTexture = TextureManager::GetInstance().AddMultiTexture(filePath, frame, row, column);
		cave::AnimatedSprite* newSprite = reinterpret_cast<AnimatedSprite*>(mPool->Allocate(sizeof(AnimatedSprite)));
		new(newSprite) cave::AnimatedSprite(animationName, newTexture, frame, duration, isLoof, mPool);

		eResult result = newSprite->Init(mDeviceResources->GetDevice(), mDeviceResources->GetDeviceContext(), mDeviceResources->GetWidth(), mDeviceResources->GetHeight());

		//temp setting
		newSprite->SetSize(newTexture->GetWidth(), newTexture->GetHeight());
		newSprite->SetPosition(300, 200); // temp
		newSprite->SetZIndex(mSprites.size());
		mSprites.push_back(newSprite);

		return result;
	}

	
	eResult GenericRenderer::RemoveSprite(uint32_t index)
	{
		assert(index < mSprites.size());

		Sprite* sprite = mSprites[index];
		sprite->Destroy();
		mPool->Deallocate(sprite, sizeof(Sprite));
		mSprites.erase(mSprites.begin() + index);

		return eResult::CAVE_OK;
	}

	void GenericRenderer::SetSpriteSize(uint32_t index, uint32_t width, uint32_t height)
	{
		assert(index < mSprites.size());

		mSprites[index]->SetSize(width, height);
	}

	void GenericRenderer::SetSpritePosition(uint32_t index, Float2 position)
	{
		assert(index < mSprites.size());
		mSprites[index]->SetPosition(position);
	}

	void GenericRenderer::SetSpriteZIndex(uint32_t index, uint32_t z)
	{
		assert(index < mSprites.size());
		mSprites[index]->SetZIndex(z);
	}

	void GenericRenderer::GetSpriteSize(uint32_t index, uint32_t& outWidth, uint32_t& outHeight) const
	{
		assert(index < mSprites.size());

		mSprites[index]->GetSize(outWidth, outHeight);
	}

	void GenericRenderer::GetSpritePosition(uint32_t index, float& outX, float& outY)
	{
		assert(index < mSprites.size());

		outX = mSprites[index]->GetPositionX();
		outY = mSprites[index]->GetPositionY();
	}

	Float2 GenericRenderer::GetSpritePosition(uint32_t index) const
	{
		assert(index < mSprites.size());

		Float2 position = mSprites[index]->GetPosition();
		return position;
	}
}