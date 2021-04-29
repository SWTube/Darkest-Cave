/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Object/GenericDrawableObject.h"

namespace cave
{
	GenericDrawableObject::GenericDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices)
		: GenericDrawableObject(verticesCount, std::move(vertices), indicesCount, std::move(indices), nullptr)
	{
	}

	GenericDrawableObject::GenericDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices, const char* textureFilePath)
		: mVerticesCount(verticesCount)
		, mVertices(vertices)
		, mIndicesCount(indicesCount)
		, mIndices(indices)
		, mTextureFilePath(textureFilePath)
	{
		vertices = nullptr;
		indices = nullptr;
	}

	GenericDrawableObject::GenericDrawableObject(const GenericDrawableObject& other)
	{
		if (this != &other)
		{
			mVerticesCount = other.mVerticesCount;
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

	GenericDrawableObject::GenericDrawableObject(const GenericDrawableObject&& other)
	{
		if (this != &other)
		{
			mVerticesCount = other.mVerticesCount;
			mVertices = other.mVertices;
			mIndicesCount = other.mIndicesCount;
			mIndices = other.mIndices;
		}
	}

	GenericDrawableObject& GenericDrawableObject::operator=(const GenericDrawableObject& other)
	{
		if (this != &other)
		{
			if (mVerticesCount != other.mVerticesCount)
			{
				delete[] mVertices;
				mVertices = new Vertex[other.mVerticesCount];
			}
			mVerticesCount = other.mVerticesCount;
			
			for (uint32_t i = 0; i < mVerticesCount; ++i)
			{
				mVertices[i] = other.mVertices[i];
			}

			if (mIndicesCount != other.mIndicesCount)
			{
				delete[] mIndices;
				mIndices = new uint8_t[other.mIndicesCount];
			}
			mIndicesCount = other.mIndicesCount;
			for (uint32_t i = 0; i < mIndicesCount; ++i)
			{
				mIndices[i] = other.mIndices[i];
			}
		}

		return *this;
	}

	GenericDrawableObject& GenericDrawableObject::operator=(const GenericDrawableObject&& other)
	{
		if (this != &other)
		{
			if (mVerticesCount != other.mVerticesCount)
			{
				delete[] mVertices;
				mVertices = new Vertex[other.mVerticesCount];
			}
			mVerticesCount = other.mVerticesCount;
			
			for (uint32_t i = 0; i < mVerticesCount; ++i)
			{
				mVertices[i] = other.mVertices[i];
			}

			if (mIndicesCount != other.mIndicesCount)
			{
				delete[] mIndices;
				mIndices = new uint8_t[other.mIndicesCount];
			}
			mIndicesCount = other.mIndicesCount;
			for (uint32_t i = 0; i < mIndicesCount; ++i)
			{
				mIndices[i] = other.mIndices[i];
			}
		}

		return *this;
	}

	GenericDrawableObject::~GenericDrawableObject()
	{
		delete[] mIndices;
		delete[] mVertices;
		delete[] mTextureFilePath;
	}

	void GenericDrawableObject::SetTextureFilePath(const char* filePath)
	{
		mTextureFilePath = filePath;
	}
} // namespace cave
