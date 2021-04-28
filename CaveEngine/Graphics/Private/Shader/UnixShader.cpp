/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "GraphicsApiPch.h"

#include "Shader/UnixShader.h"

namespace cave
{
	UnixShader::~UnixShader()
	{
		delete[] mVertexShaderFilePath;
		delete[] mFragmentShaderFilePath;
	}

	eResult UnixShader::Compile()
	{
		// 11. Compile Shaders ---------------------------------------------------------------------------------------------
		size_t projectDirLength = strlen(PROJECT_DIR);
		size_t shaderFilePathLength = strlen("/CaveEngine/Graphics/Shader/");
		size_t vertexShaderFileNameLength = strlen(mVertexShaderFilePath);
		size_t fragmentShaderFileNameLength = strlen(mFragmentShaderFilePath);
		char vertexShaderFile[projectDirLength + shaderFilePathLength + vertexShaderFileNameLength + 1] = { '\0', };
		char fragmentShaderFile[projectDirLength + shaderFilePathLength + fragmentShaderFileNameLength + 1] = { '\0', };
		strncpy(vertexShaderFile, PROJECT_DIR, projectDirLength);
		strncat(vertexShaderFile, "/CaveEngine/Graphics/Shader/", shaderFilePathLength);
		strncat(vertexShaderFile, mVertexShaderFilePath, vertexShaderFileNameLength);
		strncpy(fragmentShaderFile, PROJECT_DIR, projectDirLength);
		strncat(fragmentShaderFile, "/CaveEngine/Graphics/Shader/", shaderFilePathLength);
		strncat(fragmentShaderFile, mFragmentShaderFilePath, fragmentShaderFileNameLength);
		
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, vertexShaderFile },
			{ GL_FRAGMENT_SHADER, fragmentShaderFile },
			{ GL_NONE, nullptr }
		};

		eResult error = compileShaderFromFile(shaders);
		if (error != eResult::CAVE_OK)
		{
			LOGE(eLogChannel::GRAPHICS, std::cout, "The shader files cannot be compiled.");
			return error;
		}

		return eResult::CAVE_OK;
	}

	uint32_t UnixShader::GetProgram()
	{
		return mProgram;
	}

	//--------------------------------------------------------------------------------------
	// Helper for compiling shaders with D3DCompile
	//
	// With VS 11, we could load up prebuilt .cso files instead...
	//--------------------------------------------------------------------------------------
	eResult UnixShader::compileShaderFromFile(ShaderInfo* shaders)
	{
		mProgram = loadShaders(shaders);
		glUseProgram(mProgram);

		return eResult::CAVE_OK;
	}


	uint32_t UnixShader::loadShaders(ShaderInfo* shaders)
	{
		if (shaders == nullptr)
		{
			return 0;
		}

		GLuint program = glCreateProgram();

		ShaderInfo* entry = shaders;
		while (entry->type != GL_NONE)
		{
			GLuint shader = glCreateShader(entry->type);

			entry->shader = shader;

			const GLchar* source = readShader(entry->filename);
			if (source == nullptr)
			{
				for (entry = shaders; entry->type != GL_NONE; ++entry)
				{
					glDeleteShader( entry->shader );
					entry->shader = 0;
				}

				return 0;
			}

			glShaderSource(shader, 1, &source, nullptr);
			delete [] source;

			glCompileShader(shader);

			GLint compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled)
			{
#ifdef __Debug__
			GLsizei len;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

			GLchar* log = new GLchar[len+1];
			glGetShaderInfoLog( shader, len, &len, log );
			std::cerr << "Shader compilation failed: " << log << std::endl;
			LOGAF(eLogChannel::GRAPHICS, std::cout, "%s Compilation Failed: %s", entry->filename, log);
			delete [] log;
#endif /* DEBUG */

				return 0;
			}

			glAttachShader(program, shader);
			
			++entry;
		}

		glLinkProgram(program);

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked)
		{
#ifdef __Debug__
			GLsizei len;
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

			GLchar* log = new GLchar[len+1];
			glGetProgramInfoLog( program, len, &len, log );
			LOGAF(eLogChannel::GRAPHICS, std::cout, "Shader Linking Failed: %s", log);
			delete [] log;
#endif /* DEBUG */

			for (entry = shaders; entry->type != GL_NONE; ++entry)
			{
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}
			
			return 0;
		}

		return program;
	}

	const char* UnixShader::readShader(const char* filename)
	{
#ifdef __WIN32__
		FILE* infile;
		fopen_s( &infile, filename, "rb" );
#else
		FILE* infile = fopen(filename, "rb");
#endif // __WIN32__

		if (!infile)
		{
#ifdef _DEBUG
			LOGAF(eLogChannel::GRAPHICS, std::cout, "Unable to open file '%s' ", filename);
#endif /* DEBUG */
			return NULL;
		}

		fseek(infile, 0, SEEK_END);
		int len = ftell(infile);
		fseek(infile, 0, SEEK_SET);

		GLchar* source = new GLchar[len + 1];

		fread(source, 1, len, infile);
		fclose(infile);

		source[len] = 0;

		return const_cast<const GLchar*>(source);
	}
} // namespace cave
