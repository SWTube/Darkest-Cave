/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "GraphicsApiPch.h"

namespace cave
{
	class GenericShader
	{
	public:
		GenericShader() = delete;
		constexpr GenericShader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
		constexpr GenericShader(const char* shaderFilePath);
		GenericShader(const GenericShader&) = delete;
		GenericShader(const GenericShader&&) = delete;
		GenericShader& operator=(const GenericShader&) = delete;
		virtual ~GenericShader() = default;
		
#ifdef __WIN32__
		virtual eResult Compile(ID3D11Device* device) = 0;
#else
		virtual eResult Compile() = 0;
#endif
	protected:
		const char* mShaderFilePath = nullptr;
		const char* mVertexShaderFilePath = nullptr;
		const char* mFragmentShaderFilePath = nullptr;
	};

	constexpr GenericShader::GenericShader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
		: mVertexShaderFilePath(vertexShaderFilePath)
		, mFragmentShaderFilePath(fragmentShaderFilePath)
	{
	}

	constexpr GenericShader::GenericShader(const char* shaderFilePath)
		: mShaderFilePath(shaderFilePath)
	{
	}
} // namespace cave
