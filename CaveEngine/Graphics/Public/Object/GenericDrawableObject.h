/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "GraphicsApiPch.h"
#include "Object/Vertex.h"

namespace cave
{
	class GenericDrawableObject
	{
	public:
		GenericDrawableObject() = delete;
		GenericDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices);
		GenericDrawableObject(uint32_t verticesCount, Vertex*&& vertices, uint32_t indicesCount, uint8_t*&& indices, const char* textureFilePath);
		GenericDrawableObject(const GenericDrawableObject& other);
		GenericDrawableObject(const GenericDrawableObject&& other);
		constexpr GenericDrawableObject& operator=(const GenericDrawableObject& other);
		constexpr GenericDrawableObject& operator=(const GenericDrawableObject&& other);
		virtual ~GenericDrawableObject();

#ifdef __WIN32__
		virtual eResult Init(ID3D11Device* device, ID3D11DeviceContext* context) = 0;
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
		typedef struct ConstantBuffer
		{
			DirectX::XMMATRIX mWorld;
		} ConstantBuffer;

		// Assert that the constant buffer remains 16-byte aligned.
		static_assert((sizeof(ConstantBuffer) % 16) == 0, "Constant Buffer size must be 16-byte aligned");

		DirectX::XMMATRIX mWorld = DirectX::XMMatrixIdentity();
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
} // namespace cave
