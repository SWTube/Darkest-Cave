/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"

#include "Object/Vertex.h"

namespace cave
{
	class GenericDrawableObject
	{
	public:
		GenericDrawableObject() = delete;
		constexpr GenericDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices);
		constexpr GenericDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices, const char* textureFilePath);
		constexpr GenericDrawableObject(const GenericDrawableObject& other);
		constexpr GenericDrawableObject(const GenericDrawableObject&& other);
		constexpr GenericDrawableObject& operator=(const GenericDrawableObject& other);
		constexpr GenericDrawableObject& operator=(const GenericDrawableObject&& other);
		virtual ~GenericDrawableObject();

#ifdef __WIN32__
		virtual eResult Init() = 0;
#else
		virtual eResult Init(uint32_t program) = 0;
#endif
		virtual void Destroy() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual void SetTextureFilePath(const char* filePath);

	protected:
		uint32_t mVerticesCount = 0u;
		Vertex* mVertices = nullptr;
		uint32_t mIndicesCount = 0u;
		uint8_t* mIndices = nullptr;

#ifdef __WIN32__
		DirectX::XMMATRIX mWorld;
#else
		glm::mat4 mWorld = glm::mat4(1.0f);
#endif

		uint32_t mTexture = 0u;
		uint8_t* mTextureData = nullptr;
		uint32_t mTextureWidth = 0u;
		uint32_t mTextureHeight = 0u;
		uint32_t mTextureSampler = 0u;
		const char* mTextureFilePath = nullptr;
	};

	constexpr GenericDrawableObject::GenericDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices)
		: GenericDrawableObject(verticesCount, std::move(vertices), indicesCount, std::move(indices), nullptr)
	{
	}

	constexpr GenericDrawableObject::GenericDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices, const char* textureFilePath)
		: mVerticesCount(verticesCount)
		, mVertices(vertices)
		, mIndicesCount(indicesCount)
		, mIndices(indices)
		, mTextureFilePath(textureFilePath)
	{
		vertices = nullptr;
		indices = nullptr;
	}

	constexpr GenericDrawableObject::GenericDrawableObject(const GenericDrawableObject& other)
	{
		if (this != &other)
		{
			mVerticesCount = other.mVerticesCount;
			if (sizeof(other.mVertices))
			{

			}
			mVertices = new Vertex[mVerticesCount];
			for (uint32_t i = 0; i < mVerticesCount; ++i)
			{
				mVertices[i] = other.mVertices[i];
			}
			mIndicesCount = other.mIndicesCount;
			mIndices = new uint8_t[mIndicesCount];
			for (uint32_t i = 0; i < mIndicesCount; ++i)
			{
				mIndices[i] = other.mIndices[i];
			}
		}
	}
} // namespace cave
