/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Sprite/GenericSprite.h"

namespace cave
{
	GenericSprite::GenericSprite(Texture* texture)
		: mTexture(texture)
	{
		mWidth = mTexture->GetWidth();
		mHeight = mTexture->GetHeight();
		mTextureIndex = mTexture->GetIndex();
	}

	//GenericSprite::GenericSprite(const Texture& texture)
	//	: mTexture(reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture))))
	//{
	//	new(mTexture) Texture(texture);
	//	mWidth = mTexture->GetWidth();
	//	mHeight = mTexture->GetHeight();
	//	mTextureIndex = mTexture->GetIndex();
	//}

	//GenericSprite::GenericSprite(Texture&& texture, MemoryPool& pool)
	//	: mPool(&pool)
	//	, mTexture(reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture))))
	//{
	//	new(mTexture) Texture(std::move(texture));
	//	mWidth = mTexture->GetWidth();
	//	mHeight = mTexture->GetHeight();
	//	mTextureIndex = mTexture->GetIndex();
	//}


	GenericSprite::GenericSprite(const GenericSprite& other)
		: mWorld(other.mWorld)
		, mTextureIndex(other.mTextureIndex)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
		, mPosition(other.mPosition)
	{
		mTexture = other.mTexture;
		/*if (other.mTexture != nullptr)
		{
			mTexture = reinterpret_cast<Texture*>(mPool->Allocate(sizeof(Texture)));
			new(mTexture) Texture(*other.mTexture);
		}*/
	}

	GenericSprite::GenericSprite(GenericSprite&& other)
		: mWorld(other.mWorld)
		, mTextureIndex(other.mTextureIndex)
		, mTexture(other.mTexture)
		, mPosition(other.mPosition)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
	{
		other.mTexture = nullptr;
	}

	GenericSprite& GenericSprite::operator=(const GenericSprite& other)
	{
		if (this != &other)
		{
			mWorld = other.mWorld;
			mTextureIndex = other.mTextureIndex;

			//mTexture->~Texture();
			//if (other.mTexture != nullptr)
			//{
			//	new(mTexture) Texture(*other.mTexture);
			//}
			//else
			//{
			//	mPool->Deallocate(mTexture, sizeof(Texture));
			//	mTexture = nullptr;
			//}
			mTexture = other.mTexture;

			mPosition = other.mPosition;
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
			mTextureIndex = other.mTextureIndex;

			mTexture = other.mTexture;

			mPosition = other.mPosition;

			mWidth = other.mWidth;
			mHeight = other.mHeight;
			other.mTexture = nullptr;
		}

		return *this;
	}

	GenericSprite::~GenericSprite()
	{
		Destroy();
	}

	eResult GenericSprite::Init(ID3D11Device* device, ID3D11DeviceContext* context, uint32_t screenWidth, uint32_t screenHeight)
	{
		mScreenWidth = screenWidth;
		mScreenHeight = screenHeight;

		mPreviousPosition = Float3(-1.0f, -1.0f, 1.0f);
		//mPosition = Float3(0.0f, 0.0f, 1.0f);

		eResult result = initializeBuffers(device, context);

		return result;
	}

	void GenericSprite::Destroy()
	{
		if (mTexture != nullptr)
		{
			mTexture->~Texture(); //
			mTexture = nullptr;
		}
	}

	void GenericSprite::SetTexture(const Texture& texture)
	{
		if (mTexture != nullptr)
		{
			mTexture->~Texture();
			mTexture = nullptr;
		}
		*mTexture = texture;
	}
	void GenericSprite::SetTextureIndex(Texture* texture, uint32_t index)
	{
		mWidth = texture->GetWidth();
		mHeight = texture->GetHeight();
		mTexture = texture;
		mTextureIndex = index;
	}
} // namespace cave
