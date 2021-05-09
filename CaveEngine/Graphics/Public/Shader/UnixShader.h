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
			UnixShader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath);
			UnixShader(const UnixShader&) = delete;
			UnixShader(UnixShader&& other);
			UnixShader& operator=(const UnixShader&) = delete;
			UnixShader& operator=(UnixShader&& other);
			virtual ~UnixShader() = default;

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

		typedef UnixShader Shader;
	} // namespace cave
#endif