/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <filesystem>
#include "GraphicsApiPch.h"
#include "Shader/GenericShader.h"

#ifdef __WIN32__
	namespace cave
	{
		class WindowsShader final : public GenericShader
		{
		public:
			WindowsShader() = delete;
			constexpr WindowsShader(const char* shaderFilePath);
			WindowsShader(const WindowsShader&) = delete;
			WindowsShader(const WindowsShader&&) = delete;
			WindowsShader& operator=(const WindowsShader&) = delete;
			virtual ~WindowsShader();

			virtual eResult Compile(ID3D11Device* device) override;
		private:
			eResult compileShaderFromFile(const wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);

			ID3D11VertexShader* mVertexShader = nullptr;
			ID3D11PixelShader* mPixelShader = nullptr;
		};

		constexpr WindowsShader::WindowsShader(const char* shaderFilePath)
			: GenericShader(shaderFilePath)
		{
		}

		typedef WindowsShader Shader;
	} // namespace cave
#endif