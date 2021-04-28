/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Shader/GenericShader.h"

#ifdef __UNIX__
	namespace cave
	{
		class UnixShader final : public GenericShader
		{
		public:
			UnixShader() = delete;
			constexpr UnixShader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
			UnixShader(const UnixShader&) = delete;
			UnixShader(const UnixShader&&) = delete;
			UnixShader& operator=(const UnixShader&) = delete;
			virtual ~UnixShader();

			virtual eResult Compile() override;
			virtual uint32_t GetProgram();
		private:
			typedef struct
			{
				GLenum       type;
				const char*  filename;
				GLuint       shader;
			} ShaderInfo;

			eResult compileShaderFromFile(ShaderInfo* shaders);
			uint32_t loadShaders(ShaderInfo* shaders);
			const char* readShader(const char* filename);

			uint32_t mProgram = 0u;
		};

		constexpr UnixShader::UnixShader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
			: GenericShader(vertexShaderFilePath, fragmentShaderFilePath)
		{
		}

		typedef UnixShader Shader;
	} // namespace cave
#endif