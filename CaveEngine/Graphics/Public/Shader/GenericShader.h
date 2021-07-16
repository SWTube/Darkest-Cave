/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <filesystem>

#include "GraphicsApiPch.h"

#include "CoreGlobals.h"
#include "CoreTypes.h"
#include "Memory/MemoryPool.h"
#include "Sprite/Sprite.h"

namespace cave
{
	class GenericShader
	{
	public:
		GenericShader() = delete;
		GenericShader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath, MemoryPool& pool);
		GenericShader(const std::filesystem::path& shaderFilePath, MemoryPool& pool);
		GenericShader(const GenericShader&) = delete;
		GenericShader(GenericShader&& other);
		GenericShader& operator=(const GenericShader&) = delete;
		GenericShader& operator=(GenericShader&& other);
		virtual ~GenericShader();
		constexpr MemoryPool* GetMemoryPool() const;
		
		virtual eResult Compile(ID3D11Device* device) = 0;
		virtual void Render(ID3D11DeviceContext* context, uint32_t indexCount, const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture) = 0;

		virtual void Destroy();
	protected:
		struct Buffer
		{
			DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();
			DirectX::XMMATRIX View = DirectX::XMMatrixIdentity();
			DirectX::XMMATRIX Projection = DirectX::XMMatrixIdentity();
		};
		MemoryPool* mPool = nullptr;
		std::filesystem::path mShaderFilePath = PROJECT_DIR;
		std::filesystem::path mVertexShaderFilePath = PROJECT_DIR;
		std::filesystem::path mFragmentShaderFilePath = PROJECT_DIR;
		ID3D11Buffer* mBuffer = nullptr;

	};
} // namespace cave
