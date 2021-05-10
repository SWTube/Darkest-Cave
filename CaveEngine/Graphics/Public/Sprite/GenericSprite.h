/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "Sprite/Vertex.h"
#include "Texture/Texture.h"

namespace cave
{
	class GenericSprite
	{
	public:
		GenericSprite() = delete;
		GenericSprite(Texture* texture, MemoryPool& pool = gCoreMemoryPool);
		GenericSprite(const Texture& texture, MemoryPool& pool = gCoreMemoryPool);
		GenericSprite(Texture&& texture, MemoryPool& pool = gCoreMemoryPool);
		GenericSprite(const GenericSprite& other);
		GenericSprite(GenericSprite&& other);
		virtual ~GenericSprite();
		GenericSprite& operator=(const GenericSprite& other);
		GenericSprite& operator=(GenericSprite&& other);
		MemoryPool* const GetMemoryPool() const;

#ifdef __WIN32__
		virtual eResult Init(ID3D11Device* device, ID3D11DeviceContext* context, uint32_t screenWidth, uint32_t screenHeight);
#else
		virtual eResult Init(uint32_t program, uint32_t screenWidth, uint32_t screenHeight);
#endif
		virtual void Destroy();
		virtual void Update() = 0;
		virtual void Render() = 0;

	protected:
#ifdef __WIN32__
		virtual eResult initializeBuffers(ID3D11Device* device, ID3D11DeviceContext* context) = 0;
#else
		virtual eResult initializeBuffers(uint32_t program) = 0;
#endif
		static constexpr uint32_t VERTICES_COUNT = 4u;
		static constexpr uint32_t INDICES_COUNT = 6u;

		static constexpr VertexT VERTICES[VERTICES_COUNT] = {
			VertexT(-1.0f,  1.0f, 0.0f,	0.0f, 0.0f),	// top left
			VertexT( 1.0f,  1.0f, 0.0f,	1.0f, 0.0f),	// top right
			VertexT( 1.0f, -1.0f, 0.0f,	1.0f, 1.0f),	// bottom right
			VertexT(-1.0f, -1.0f, 0.0f,	0.0f, 1.0f),	// bottom left
		};

		static constexpr uint8_t INDICES[INDICES_COUNT] = {
			0u, 1u, 2u,
			2u, 3u, 0u,
		};

		MemoryPool* mPool = nullptr;
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
		Texture* mTextureData = nullptr;
		uint32_t mTextureSampler = 0u;

		uint32_t mWidth = 0u;
		uint32_t mHeight = 0u;
		uint32_t mScreenWidth = 0u;
		uint32_t mScreenHeight = 0u;

		Vertex mPosition;
		Vertex mPreviousPosition;

		bool mbNeedsUpdate = false;
	};
} // namespace cave
