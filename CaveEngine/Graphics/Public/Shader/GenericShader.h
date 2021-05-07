/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <filesystem>

#include "CoreTypes.h"
#include "GraphicsApiPch.h"

namespace cave
{
	class GenericShader
	{
	public:
		GenericShader() = delete;
		GenericShader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath, MemoryPool& pool = gCoreMemoryPool);
		GenericShader(const std::filesystem::path& shaderFilePath, MemoryPool& pool = gCoreMemoryPool);
		GenericShader(const GenericShader&) = delete;
		GenericShader(GenericShader&& other);
		GenericShader& operator=(const GenericShader&) = delete;
		GenericShader& operator=(GenericShader&& other);
		virtual ~GenericShader();
		constexpr MemoryPool* const GetMemoryPool() const;
		
#ifdef __WIN32__
		virtual eResult Compile(ID3D11Device* device) = 0;
#else
		virtual eResult Compile() = 0;
#endif
	protected:
		MemoryPool* mPool = nullptr;
		std::filesystem::path mShaderFilePath = PROJECT_DIR;
		std::filesystem::path mVertexShaderFilePath = PROJECT_DIR;
		std::filesystem::path mFragmentShaderFilePath = PROJECT_DIR;
	};
} // namespace cave
