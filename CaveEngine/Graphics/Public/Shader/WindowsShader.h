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
			WindowsShader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath);
			WindowsShader(const WindowsShader&) = delete;
			WindowsShader(WindowsShader&& other);
			WindowsShader& operator=(const WindowsShader&) = delete;
			WindowsShader& operator=(WindowsShader&& other);
			virtual ~WindowsShader();

			virtual eResult Compile(ID3D11Device* device) override;
			void Render(ID3D11DeviceContext* context);

			ID3DBlob* const GetVertexShaderBlob();
		private:
			eResult compileShaderFromFile(const wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);

			ID3D11VertexShader* mVertexShader = nullptr;
			ID3D11PixelShader* mPixelShader = nullptr;
			ID3DBlob* mVsBlob = nullptr;
			ID3DBlob* mPsBlob = nullptr;
		};

		typedef WindowsShader Shader;
	} // namespace cave
#endif