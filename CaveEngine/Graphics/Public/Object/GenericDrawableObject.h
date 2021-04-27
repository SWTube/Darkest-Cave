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
		constexpr GenericDrawableObject(const GenericDrawableObject& object);
		constexpr GenericDrawableObject(const GenericDrawableObject&& object);
		constexpr GenericDrawableObject& operator=(const GenericDrawableObject& object);
		constexpr GenericDrawableObject& operator=(const GenericDrawableObject&& object);
		virtual ~GenericDrawableObject();

		virtual uint32_t GetVerticesDataSize() const;

		virtual void Destroy() = 0;

		uint32_t VerticesCount = 0u;
		uint32_t VerticesFrameSize = 0u;
		float* Vertices = nullptr;
		uint32_t IndicesCount = 0u;
		uint8_t* Indices = nullptr;

		uint32_t Texture = 0u;
		uint8_t* TextureData = nullptr;
		uint32_t TextureWidth = 0u;
		uint32_t TextureHeight = 0u;
		uint32_t TextureSampler = 0u;
	};

	constexpr GenericDrawableObject::GenericDrawableObject(uint32_t verticesCount, uint32_t verticesFrameSize, float*&& vertices, uint32_t indicesCount, uint8_t*&& indices)
		: VerticesCount(verticesCount)
		, VerticesFrameSize(verticesFrameSize)
		, Vertices(vertices)
		, IndicesCount(indicesCount)
		, Indices(indices)
	{
		vertices = nullptr;
		indices = nullptr;
	}

	constexpr GenericDrawableObject::GenericDrawableObject(const GenericDrawableObject& other)
	{
		if (this != &other)
		{
			VerticesCount = other.VerticesCount;
			VerticesFrameSize = other.VerticesFrameSize;
			Vertices = new float[VerticesCount * VerticesFrameSize];
			for (uint32_t i = 0; i < VerticesCount * VerticesFrameSize; ++i)
			{
				Vertices[i] = other.Vertices[i];
			}
			IndicesCount = other.IndicesCount;
			Indices = new uint8_t[IndicesCount];
			for (uint32_t i = 0; i < IndicesCount; ++i)
			{
				Indices[i] = other.Indices[i];
			}
		}
	}
} // namespace cave
