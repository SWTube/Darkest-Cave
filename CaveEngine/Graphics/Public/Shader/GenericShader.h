/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"

namespace cave
{
	class GenericShader
	{
	public:
		GenericShader() = delete;
		constexpr GenericShader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
		GenericShader(const GenericShader&) = delete;
		GenericShader(const GenericShader&&) = delete;
		GenericShader& operator=(const GenericShader&) = delete;
		virtual ~GenericShader() = default;

		virtual eResult Compile() = 0;
	protected:
		const char* mVertexShaderFilePath = nullptr;
		const char* mFragmentShaderFilePath = nullptr;
	};

	constexpr GenericShader::GenericShader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
		: mVertexShaderFilePath(vertexShaderFilePath)
		, mFragmentShaderFilePath(fragmentShaderFilePath)
	{
	}
} // namespace cave
