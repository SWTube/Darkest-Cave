/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "lodepng.h"

#include "Debug/Log.h"
#include "Texture/Texture.h"

#ifdef __WIN32__
	import DdsTextureLoader;
#endif

namespace cave
{
	Texture::Texture(const std::filesystem::path& filePath, eTextureFormat textureFormat, MemoryPool& pool)
		: mPool(&pool)
		, mFormat(textureFormat)
	{
#ifdef __WIN32__
		mFilePath /= L"CaveEngine/Graphics/Resource";
		std::filesystem::create_directories(mFilePath / L"Textures");
		mFilePath /= L"Textures";
		mFilePath /= filePath;

		mTexture = reinterpret_cast<TexturePointer*>(mPool->Allocate(sizeof(TexturePointer)));
		mTexture->ReferenceCount = 1u;
		mTexture->Texture = nullptr;

		const wchar_t* extension = mFilePath.extension().c_str();
		if (wcsncmp(extension, L".png", 4) == 0)
		{
			uint32_t error = 0u;
			switch (mFormat)
			{
			case eTextureFormat::RGB:
				error = lodepng_decode24_file(&mTexture->Texture, &mWidth, &mHeight, mFilePath.string().c_str());
				break;
			case eTextureFormat::RGBA:
				error = lodepng_decode32_file(&mTexture->Texture, &mWidth, &mHeight, mFilePath.string().c_str());
				break;
			default:
				assert(false);
				break;
			}
			
			if (error != 0)
			{
				LOGEF(eLogChannel::GRAPHICS, "The png file %s cannot be loaded. Error Code: %u", mFilePath.string().c_str(), error);
			}
		}
		else if (wcsncmp(extension, L".dds", 4) == 0)
		{

		}
#else
		mFilePath /= "CaveEngine/Graphics/Resource";
		std::filesystem::create_directories(mFilePath / "Textures");
		mFilePath /= "Textures";
		mFilePath /= filePath;

		mTexture = reinterpret_cast<TexturePointer*>(mPool->Allocate(sizeof(TexturePointer)));
		mTexture->ReferenceCount = 1u;
		mTexture->Texture = nullptr;

		const char* extension = mFilePath.extension().c_str();
		if (strncmp(extension, ".png", 4) == 0)
		{
			uint32_t error = 0u;
			switch (mFormat)
			{
			case eTextureFormat::RGB:
				error = lodepng_decode24_file(&mTexture->Texture, &mWidth, &mHeight, mFilePath.c_str());
				break;
			case eTextureFormat::RGBA:
				error = lodepng_decode32_file(&mTexture->Texture, &mWidth, &mHeight, mFilePath.c_str());
				break;
			default:
				assert(false);
				break;
			}
			
			if (error != 0)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "The png file %s cannot be loaded. Error Code: %u", mFilePath.c_str(), error);
			}
		}
		else if (strncmp(extension, ".dds", 4) == 0)
		{

		}
#endif
	}

	Texture::Texture(const Texture& other)
		: mPool(other.mPool)
		, mFilePath(other.mFilePath)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
		, mFormat(other.mFormat)
		, mTexture(other.mTexture)
	{
		if (mTexture != nullptr)
		{
			++mTexture->ReferenceCount;
		}
	}

	Texture::Texture(Texture&& other)
		: mPool(other.mPool)
		, mFilePath(other.mFilePath)
		, mWidth(other.mWidth)
		, mHeight(other.mHeight)
		, mFormat(other.mFormat)
		, mTexture(other.mTexture)
	{
		other.mPool = nullptr;
		other.mFilePath.clear();
		other.mTexture = nullptr;
	}

	Texture& Texture::operator=(const Texture& other)
	{
		if (this != &other)
		{
			mPool = other.mPool;
			mFilePath = other.mFilePath;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
			mFormat = other.mFormat;
			if (mTexture != nullptr)
			{
				--mTexture->ReferenceCount;
			}
			mTexture = other.mTexture;
			if (mTexture != nullptr)
			{
				++mTexture->ReferenceCount;
			}
		}

		return *this;
	}

	Texture& Texture::operator=(Texture&& other)
	{
		if (this != &other)
		{
			mPool = other.mPool;
			mFilePath = other.mFilePath;
			mWidth = other.mWidth;
			mHeight = other.mHeight;
			mFormat = other.mFormat;
			if (mTexture != nullptr)
			{
				--mTexture->ReferenceCount;
			}
			mTexture = other.mTexture;

			other.mPool = nullptr;
			other.mFilePath.clear();
			other.mTexture = nullptr;
		}

		return *this;
	}

	Texture::~Texture()
	{
		Destroy();
	}

	void Texture::Destroy()
	{
		if (mTexture != nullptr)
		{
			--mTexture->ReferenceCount;
			if (mTexture->ReferenceCount == 0u)
			{
				mTexture->~TexturePointer();
				mPool->Deallocate(mTexture, sizeof(TexturePointer));
			}
		}
	}

	MemoryPool* const Texture::GetMemoryPool()
	{
		return mPool;
	}

	const uint8_t* const Texture::GetTexture() const
	{
		if (mTexture != nullptr)
		{
			return mTexture->Texture;
		}

		return nullptr;
	}

	const char* const Texture::GetCStringFilePath() const
	{
#ifdef __WIN32__
		return mFilePath.string().c_str();
#else
		return mFilePath.c_str();
#endif
	}

	const std::filesystem::path& Texture::GetFilePath() const
	{
		return mFilePath;
	}

	uint32_t Texture::GetWidth() const
	{
		return mWidth;
	}

	uint32_t Texture::GetHeight() const
	{
		return mHeight;
	}

	eTextureFormat Texture::GetFormat() const
	{
		return mFormat;
	}
} // namespace cave
