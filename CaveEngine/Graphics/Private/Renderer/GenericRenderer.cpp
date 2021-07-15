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
		while (!mTextures.empty())
		{
			Texture* texture = mTextures.back();
			texture->~Texture();
			mPool->Deallocate(texture, sizeof(Sprite));
			texture = nullptr;
			mTextures.pop_back();
		}
		mTextures.clear();
		// std::vector<Texture*>().swap(mTextures);

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

	eResult GenericRenderer::AddSprite(Sprite&& object)
	{
		Sprite* newSprite = reinterpret_cast<Sprite*>(mPool->Allocate(sizeof(Sprite)));
		new(newSprite) Sprite(std::move(object));
		newSprite->SetTextureIndex(mTextures[0u],0u);
		eResult result = newSprite->Init(mDeviceResources->GetDevice(),mDeviceResources->GetDeviceContext(), mDeviceResources->GetWidth(), mDeviceResources->GetHeight());

		if (result != eResult::CAVE_OK)
		{
			return result;
		}
		newSprite->SetZIndex(mSprites.size());
		mSprites.push_back(newSprite);

		return result;
	}

	eResult GenericRenderer::AddSprite(const std::filesystem::path& filePath)
	{
		//새 텍스쳐 생성
		Texture* newTexture = reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture)));
		new(newTexture) cave::Texture(mDeviceResources->GetDevice(),filePath);
		//newTexture->Init(mDeviceResources->GetDevice(), mDeviceResources->GetDeviceContext());
		mTextures.push_back(newTexture);

		//새 스프라이트 생성
		cave::Sprite* newSprite = reinterpret_cast<Sprite*>(mPool->Allocate(sizeof(Sprite)));
		new(newSprite) cave::Sprite(newTexture);

		eResult result = newSprite->Init(mDeviceResources->GetDevice(), mDeviceResources->GetDeviceContext(), mDeviceResources->GetWidth(), mDeviceResources->GetHeight());
		newSprite->SetTextureIndex(mTextures.back(),mTextures.size() - 1);
		newSprite->SetSize(newTexture->GetWidth(), newTexture->GetHeight());
		newSprite->SetPosition(200, 200); // temp
		newSprite->SetZIndex(mSprites.size());
		mSprites.push_back(newSprite);

		return result;
	}

	eResult GenericRenderer::AddAnimatedSprite(const std::filesystem::path& filePath, std::string animationName, uint32_t frame, float duration, bool isLoof)
	{
		MultiTexture* newTexture = reinterpret_cast<MultiTexture*>(mPool->Allocate(sizeof(MultiTexture)));
		new(newTexture) cave::MultiTexture(mDeviceResources->GetDevice(), filePath, frame);
		mTextures.push_back(newTexture);
		cave::AnimatedSprite* newSprite = reinterpret_cast<AnimatedSprite*>(mPool->Allocate(sizeof(AnimatedSprite)));
		new(newSprite) cave::AnimatedSprite(animationName,newTexture,frame,duration,isLoof,mPool);

		eResult result = newSprite->Init(mDeviceResources->GetDevice(), mDeviceResources->GetDeviceContext(), mDeviceResources->GetWidth(), mDeviceResources->GetHeight());
		newSprite->SetTextureIndex(mTextures.back(), mTextures.size() - 1);
		newSprite->SetSize(newTexture->GetWidth(), newTexture->GetHeight());
		newSprite->SetPosition(300, 200); // temp
		newSprite->SetZIndex(mSprites.size());
		mSprites.push_back(newSprite);
		return result;
	}

	eResult GenericRenderer::AddTexture(Texture&& texture)
	{
		Texture* newTexture = reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture)));
		new(newTexture) Texture(std::move(texture));

		mTextures.push_back(newTexture);

		return eResult::CAVE_OK;
	}

	eResult GenericRenderer::AddTexture(const std::filesystem::path& filePath)
	{
		Texture* newTexture = reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture)));
		new(newTexture) cave::Texture(mDeviceResources->GetDevice(), filePath);
		mTextures.push_back(newTexture);
		return eResult::CAVE_OK;
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

	eResult GenericRenderer::RemoveTexture(uint32_t index)
	{
		assert(index < mTextures.size());

		Texture* texture = mTextures[index];
		texture->Destroy();
		mPool->Deallocate(texture, sizeof(Texture));
		mTextures.erase(mTextures.begin() + index);

		return eResult::CAVE_OK;
	}

	void GenericRenderer::SetSpriteTexture(uint32_t index, uint32_t textureIndex)
	{
		assert(index < mSprites.size());

		mSprites[index]->SetTextureIndex(mTextures[textureIndex],textureIndex);
	}

	uint32_t GenericRenderer::GetSpriteTextureIndex(uint32_t index) const
	{
		assert(index < mSprites.size());

		return mSprites[index]->GetTextureIndex();
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