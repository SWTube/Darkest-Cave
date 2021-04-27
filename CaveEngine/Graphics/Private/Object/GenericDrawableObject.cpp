/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Object/GenericDrawableObject.h"

namespace cave
{
	constexpr GenericDrawableObject::GenericDrawableObject(const GenericDrawableObject&& other)
	{
		if (this != &other)
		{
			VerticesCount = other.VerticesCount;
			VerticesFrameSize = other.VerticesFrameSize;
			Vertices = other.Vertices;
			IndicesCount = other.IndicesCount;
			Indices = other.Indices;
		}
	}

	constexpr GenericDrawableObject& GenericDrawableObject::operator=(const GenericDrawableObject& other)
	{
		if (this != &other)
		{
			if (VerticesCount * VerticesFrameSize != other.VerticesCount * other.VerticesFrameSize)
			{
				delete Vertices;
				Vertices = new float[other.VerticesCount * other.VerticesFrameSize];
			}
			VerticesCount = other.VerticesCount;
			VerticesFrameSize = other.VerticesFrameSize;
			
			for (uint32_t i = 0; i < VerticesCount * VerticesFrameSize; ++i)
			{
				Vertices[i] = other.Vertices[i];
			}

			if (IndicesCount != other.IndicesCount)
			{
				delete Indices;
				Indices = new uint8_t[other.IndicesCount];
			}
			IndicesCount = other.IndicesCount;
			for (uint32_t i = 0; i < IndicesCount; ++i)
			{
				Indices[i] = other.Indices[i];
			}
		}

		return *this;
	}

	constexpr GenericDrawableObject& GenericDrawableObject::operator=(const GenericDrawableObject&& other)
	{
		if (this != &other)
		{
			if (VerticesCount * VerticesFrameSize != other.VerticesCount * other.VerticesFrameSize)
			{
				delete Vertices;
				Vertices = new float[other.VerticesCount * other.VerticesFrameSize];
			}
			VerticesCount = other.VerticesCount;
			VerticesFrameSize = other.VerticesFrameSize;
			
			for (uint32_t i = 0; i < VerticesCount * VerticesFrameSize; ++i)
			{
				Vertices[i] = other.Vertices[i];
			}

			if (IndicesCount != other.IndicesCount)
			{
				delete Indices;
				Indices = new uint8_t[other.IndicesCount];
			}
			IndicesCount = other.IndicesCount;
			for (uint32_t i = 0; i < IndicesCount; ++i)
			{
				Indices[i] = other.Indices[i];
			}
		}

		return *this;
	}

	GenericDrawableObject::~GenericDrawableObject()
	{
		delete Indices;
		delete Vertices;
	}

	uint32_t GenericDrawableObject::GetVerticesDataSize() const
	{
		return VerticesCount * VerticesFrameSize;
	}
} // namespace cave
