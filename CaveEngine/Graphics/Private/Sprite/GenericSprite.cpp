/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Sprite/GenericSprite.h"

namespace cave
{
	GenericSprite::GenericSprite(Texture* texture, MemoryPool& pool)
		: mPool(&pool)
		, mTextureData(texture)
		, mWidth(mTextureData->GetWidth())
		, mHeight(mTextureData->GetHeight())
	{
	}

	GenericSprite::GenericSprite(const Texture& texture, MemoryPool& pool)
		: mPool(&pool)
		, mTextureData(reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture))))
	{
		new(mTextureData) Texture(texture);
		mWidth = mTextureData->GetWidth();
		mHeight = mTextureData->GetHeight();
	}

	GenericSprite::GenericSprite(Texture&& texture, MemoryPool& pool)
		: mPool(&pool)
		, mTextureData(reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture))))
	{
		new(mTextureData) Texture(std::move(texture));
		mWidth = mTextureData->GetWidth();
		mHeight = mTextureData->GetHeight();
	}

	GenericSprite::GenericSprite(const GenericSprite& other)
		: mPool(other.mPool)
		, mWorld(other.mWorld)
		, mTexture(other.mTexture)
		, mTextureSampler(other.mTextureSampler)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
	{
		if (other.mTextureData != nullptr)
		{
			mTextureData = reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture)));
			new(mTextureData) Texture(*other.mTextureData);
		}
	}

	GenericSprite::GenericSprite(GenericSprite&& other)
		: mPool(other.mPool)
		, mWorld(other.mWorld)
		, mTexture(other.mTexture)
		, mTextureData(other.mTextureData)
		, mTextureSampler(other.mTextureSampler)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
	{
		other.mPool = nullptr;
		other.mTextureData = nullptr;
	}

	GenericSprite& GenericSprite::operator=(const GenericSprite& other)
	{
		if (this != &other)
		{
			mWorld = other.mWorld;
			mTexture = other.mTexture;

			mTextureData->~Texture();
			if (other.mTextureData != nullptr)
			{
				new(mTextureData) Texture(*other.mTextureData);
			}
			else
			{
				mPool->Deallocate(mTextureData, sizeof(Texture));
				mTextureData = nullptr;
			}

			mTextureSampler = other.mTextureSampler;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
		}

		return *this;
	}

	GenericSprite& GenericSprite::operator=(GenericSprite&& other)
	{
		if (this != &other)
		{
			mWorld = other.mWorld;
			mTexture = other.mTexture;

			mTextureData = other.mTextureData;
			mTextureSampler = other.mTextureSampler;

			mWidth = other.mWidth;
			mHeight = other.mHeight;

			other.mPool = nullptr;
			other.mTextureData = nullptr;
		}

		return *this;
	}

	GenericSprite::~GenericSprite()
	{
		Destroy();
	}

	MemoryPool* const GenericSprite::GetMemoryPool() const
	{
		return mPool;
	}

#ifdef __WIN32__
	eResult GenericSprite::Init(ID3D11Device* device, ID3D11DeviceContext* context, uint32_t screenWidth, uint32_t screenHeight)
#else
	eResult GenericSprite::Init(uint32_t program, uint32_t screenWidth, uint32_t screenHeight)
#endif
	{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;

		mPreviousPosition = Vertex(-1.0f, -1.0f, 1.0f);
		mPosition = Vertex(mScreenWidth / 2.0f, mScreenHeight / 2.0f, 1.0f);

#ifdef __WIN32__
		eResult result = initializeBuffers(device, context);
#else
		eResult result = initializeBuffers(program);
#endif

		return result;
	}

	void GenericSprite::Destroy()
	{
		if (mTextureData != nullptr)
		{
			mTextureData->~Texture();
			mPool->Deallocate(mTextureData, sizeof(Texture));
		}
	}
} // namespace cave
