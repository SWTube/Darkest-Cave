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

		// 16. Load Textures ---------------------------------------------------------------------------------------------

		// LOGDF(eLogChannel::GRAPHICS, std::cout, "vector size: %lu", TextureData.size());
		glCreateTextures(GL_TEXTURE_2D, 1u, &mIndex);
		if (uint32_t glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateTextures error code: 0x%x", glError);
		}

		glTextureParameteri(mIndex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(mIndex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(mIndex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(mIndex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		const char* extension = mFilePath.extension().c_str();
		if (strncmp(extension, ".png", 4) == 0)
		{
			uint32_t error = 0u;
			switch (mFormat)
			{
			case eTextureFormat::RGB:
				{
					error = lodepng_decode24_file(&mTexture->Texture, &mWidth, &mHeight, mFilePath.c_str());

					glTextureStorage2D(mIndex, 1, GL_RGB8, mWidth, mHeight);
					if (uint32_t glError = glGetError(); glError != GL_NO_ERROR)
					{
						LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureStorage2D error code: 0x%x", glError);
					}
					glTextureSubImage2D(mIndex, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mTexture->Texture);
					if (uint32_t glError = glGetError(); glError != GL_NO_ERROR)
					{
						LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureSubImage2D error code: 0x%x", glError);
					}
					break;
				}
			case eTextureFormat::RGBA:
				{
					error = lodepng_decode32_file(&mTexture->Texture, &mWidth, &mHeight, mFilePath.c_str());

					std::vector<uint8_t> image;
					image.resize(mWidth * mHeight * 4);
					for (uint32_t y = 0; y < mHeight; ++y)
					{
						for (uint32_t x = 0; x < mWidth; ++x)
						{
							image[4 * mWidth * y + 4 * x + 0] = 255 * !(x & y);
							image[4 * mWidth * y + 4 * x + 1] = x ^ y;
							image[4 * mWidth * y + 4 * x + 2] = x | y;
							image[4 * mWidth * y + 4 * x + 3] = 255;
						}
					}

					lodepng::encode("what.png", image, mWidth, mHeight);

					glTextureStorage2D(mIndex, 1, GL_RGBA8, mWidth, mHeight);
					if (uint32_t glError = glGetError(); glError != GL_NO_ERROR)
					{
						LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureStorage2D error code: 0x%x", glError);
					}
					glTextureSubImage2D(mIndex, 0, 0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, mTexture->Texture);
					if (uint32_t glError = glGetError(); glError != GL_NO_ERROR)
					{
						LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureSubImage2D error code: 0x%x", glError);
					}
					break;
				}
			default:
				assert(false);
				break;
			}
			
			if (error != 0)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "The png file %s cannot be loaded. Error Code: %u", mFilePath.c_str(), error);
			}

			// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, TextureWidth, TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureData);
			glGenerateTextureMipmap(mIndex);
			if (uint32_t glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glGenerateTextureMipmap error code: 0x%x", glError);
			}
			// glCreateSamplers(1, &msBackgroundSampler);
			// LOGDF(eLogChannel::GRAPHICS, std::cout, "sampler: %u", msBackgroundSampler);
			// glBindSampler(msBackgroundIndex, msBackgroundSampler);
			
			if (mTexture != nullptr)
			{
				mTexture->Destroy();
				mTexture = nullptr;
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
		, mIndex(other.mIndex)
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
		, mIndex(other.mIndex)
	{
		other.mPool = nullptr;
		other.mFilePath.clear();
		other.mTexture = nullptr;
		other.mIndex = 0u;
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
		glDeleteTextures(mIndex - 1u, &mIndex);

		if (mTexture != nullptr)
		{
			mTexture->Destroy();
			mTexture = nullptr;
		}
	}

	MemoryPool* const Texture::GetMemoryPool()
	{
		return mPool;
	}

	const char* const Texture::GetCStringFilePath() const
	{
#ifdef __WIN32__
		return mFilePath.string().c_str();
#else
		return mFilePath.c_str();
#endif
	}
} // namespace cave
