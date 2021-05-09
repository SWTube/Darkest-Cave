/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <filesystem>

#include "CoreGlobals.h"
#include "CoreTypes.h"

namespace cave
{
	enum class eTextureFormat
	{
		RGB,
		RGBA,
	};

	struct Texture final
	{
	public:
		Texture(const std::filesystem::path& filePath, eTextureFormat textureFormat = eTextureFormat::RGBA, MemoryPool& pool = gCoreMemoryPool);
		Texture(const Texture& other);
		Texture(Texture&& other);
		Texture& operator=(const Texture& other);
		Texture& operator=(Texture&& other);
		~Texture();
		MemoryPool* const GetMemoryPool();

		const uint8_t* const GetTexture() const;
		const char* const GetCStringFilePath() const;
		const std::filesystem::path& GetFilePath() const;
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		eTextureFormat GetFormat() const;
	private:
		typedef struct TexturePointer
		{
			uint32_t ReferenceCount = 0u;
			uint8_t* Texture = nullptr;

			constexpr TexturePointer()
				: ReferenceCount(0u)
				, Texture(nullptr)
			{
			}

			constexpr TexturePointer(TexturePointer&& other)
				: ReferenceCount(other.ReferenceCount)
				, Texture(other.Texture)
			{
				other.Texture = nullptr;
			}

			~TexturePointer()
			{
				if (Texture != nullptr)
				{
					free(Texture);
				}
			}
		} TexturePointer;
		
		MemoryPool* mPool = nullptr;
		std::filesystem::path mFilePath = PROJECT_DIR;
		uint32_t mWidth = 0u;
		uint32_t mHeight = 0u;
		eTextureFormat mFormat = eTextureFormat::RGBA;
		TexturePointer* mTexture = nullptr;
	};
} // namespace cave
