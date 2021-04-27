/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "lodepng.h"

#include "CoreMinimal.h"
#include "Renderer/UnixRenderer.h"

#ifdef __UNIX__
namespace cave
{
	UnixRenderer::UnixRenderer(DeviceResources* deviceResources)
		: GenericRenderer(deviceResources)
	{
	}
	
	//--------------------------------------------------------------------------------------
	// Destroy Renderer
	//--------------------------------------------------------------------------------------
	UnixRenderer::~UnixRenderer()
	{
		Destroy();
	}

	int32_t UnixRenderer::createShaders()
	{
		// 11. Compile Shaders ---------------------------------------------------------------------------------------------
		size_t projectDirLength = strlen(PROJECT_DIR);
		size_t shaderFileNameLength = strlen("/CaveEngine/Graphics/Shader/triangles.vert");
		char vertexShaderFile[projectDirLength + shaderFileNameLength + 1] = { '\0', };
		char fragmentShaderFile[projectDirLength + shaderFileNameLength + 1] = { '\0', };
		strncpy(vertexShaderFile, PROJECT_DIR, projectDirLength);
		strncat(vertexShaderFile, "/CaveEngine/Graphics/Shader/triangles.vert", shaderFileNameLength);
		strncpy(fragmentShaderFile, PROJECT_DIR, projectDirLength);
		strncat(fragmentShaderFile, "/CaveEngine/Graphics/Shader/triangles.frag", shaderFileNameLength);
		
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, vertexShaderFile },
			{ GL_FRAGMENT_SHADER, fragmentShaderFile },
			{ GL_NONE, nullptr }
		};

		int32_t error = compileShaderFromFile(shaders);
		if (FAILED(error))
		{
			LOGE(eLogChannel::GRAPHICS, std::cout, "The shader files cannot be compiled.");
			return error;
		}

		return GLFW_NO_ERROR;
	}

	int32_t UnixRenderer::createObjects()
	{
		GLenum glError = GL_NO_ERROR;

		for (DrawableObject* const object : mDrawableObjects)
		{
			// 14. Create Buffer ---------------------------------------------------------------------------------------------
			glCreateBuffers(DrawableObject::BUFFER_COUNT, object->Buffers);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateBuffers error code: 0x%x", glError);
			}
			for (uint32_t i = 0; i < DrawableObject::BUFFER_COUNT; ++i)
			{
				LOGDF(eLogChannel::GRAPHICS, std::cerr, "buffer: %u", object->Buffers[i]);
			}

			// 15. Bind Buffer ---------------------------------------------------------------------------------------------
			glBindBuffer(GL_ARRAY_BUFFER, object->Buffers[DrawableObject::ARRAY_BUFFER]);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindBuffer error code: 0x%x", glError);
			}
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->Buffers[DrawableObject::ELEMENT_ARRAY_BUFFER]);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindBuffer error code: 0x%x", glError);
			}

			// 12. Define, create, set the input layout ---------------------------------------------------------------------------------------------
			glCreateVertexArrays(1u, &object->VertexArrayObject);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateVertexArrays error code: 0x%x", glError);
			}
			glBindVertexArray(object->VertexArrayObject);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindVertexArray error code: 0x%x", glError);
			}
			
			glVertexAttribPointer(V_POSITION, 3, GL_FLOAT, GL_FALSE, object->VerticesFrameSize * sizeof(float), BUFFER_OFFSET(0));
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGDF(eLogChannel::GRAPHICS, std::cerr, "glVertexAttribPointer error code: 0x%x", glError);
			}
			glEnableVertexAttribArray(V_POSITION);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glEnableVertexAttribArray error code: 0x%x", glError);
			}

			glVertexAttribPointer(V_TEX_COORD, 2, GL_FLOAT, GL_FALSE, object->VerticesFrameSize * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glVertexAttribPointer error code: 0x%x", glError);
			}
			glEnableVertexAttribArray(V_TEX_COORD);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGDF(eLogChannel::GRAPHICS, std::cerr, "glEnableVertexAttribArray error code: 0x%x", glError);
			}

			// Preparing to Send Data to OpenGL
			// All data must be stored in buffer objects (chunks of memory managed by OpenGL)
			// Common way is to specify the data at the same time as you specify the buffer's size
			glNamedBufferStorage(object->GetBuffers()[DrawableObject::ARRAY_BUFFER], object->GetVerticesDataSize(), object->Vertices, 0);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glNamedBufferStorage error code: 0x%x", glError);
			}

			glNamedBufferStorage(object->GetBuffers()[DrawableObject::ELEMENT_ARRAY_BUFFER], object->IndicesCount, object->Indices, 0);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glNamedBufferStorage error code: 0x%x", glError);
			}


			// 16. Load Textures ---------------------------------------------------------------------------------------------
			uint32_t error = lodepng_decode24_file(&object->TextureData, &object->TextureWidth, &object->TextureHeight, "Graphics/Resource/8471.png");
			if (error != 0)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cout, "The png file cannot be loaded. Error Code: %u", error);
				return error;
			}

			// LOGDF(eLogChannel::GRAPHICS, std::cout, "vector size: %lu", object->TextureData.size());
			LOGDF(eLogChannel::GRAPHICS, std::cout, "image width: %u", object->TextureWidth);
			LOGDF(eLogChannel::GRAPHICS, std::cout, "image height: %u", object->TextureHeight);
			glCreateTextures(GL_TEXTURE_2D, 1u, &object->Texture);
			LOGDF(eLogChannel::GRAPHICS, std::cout, "texture index: %u", object->Texture);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glCreateTextures error code: 0x%x", glError);
			}

			glBindTextureUnit(0, object->Texture);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindTextureUnit error code: 0x%x", glError);
			}

			uint32_t program = mDeviceResources->GetProgram();
			if (glGetUniformLocation(program, "tex") < 0)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "Failed to get uniform location: %s, error code: 0x%x", "tex", glGetError());
			}

			glTextureParameteri(object->Texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(object->Texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureParameteri(object->Texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(object->Texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			LOGDF(eLogChannel::GRAPHICS, std::cerr, "Width: %u Height: %u", object->TextureWidth, object->TextureHeight);
			glTextureStorage2D(object->Texture, 1, GL_RGB8, object->TextureWidth, object->TextureHeight);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureStorage2D error code: 0x%x", glError);
			}
			glTextureSubImage2D(object->Texture, 0, 0, 0, object->TextureWidth, object->TextureHeight, GL_RGB, GL_UNSIGNED_BYTE, object->TextureData);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glTextureSubImage2D error code: 0x%x", glError);
			}
			// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, object->TextureWidth, object->TextureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, object->TextureData);
			glGenerateTextureMipmap(object->Texture);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glGenerateTextureMipmap error code: 0x%x", glError);
			}

			GLint texLocation = glGetUniformLocation(program, "tex");
			LOGDF(eLogChannel::GRAPHICS, std::cout, "texture location: %u", texLocation);
			
			if (texLocation >= 0)
			{
				glUniform1i(texLocation, 0);
			}

			// glCreateSamplers(1, &msBackgroundSampler);
			// LOGDF(eLogChannel::GRAPHICS, std::cout, "sampler: %u", msBackgroundSampler);
			// glBindSampler(msBackgroundIndex, msBackgroundSampler);
			free(object->TextureData);
			object->TextureData = nullptr;
		}

		return GLFW_NO_ERROR;
	}

	void UnixRenderer::createView()
	{

	}

	void UnixRenderer::createPerspective()
	{

	}

	//-----------------------------------------------------------------------------
	// Create device-dependent resources for rendering.
	//---------------------------------------------------------------------------
	void UnixRenderer::CreateDeviceDependentResources()
	{
		// Compile shaders using the Effects library.
		createShaders();

		// Load the geometry for the spinning cube.
		createObjects();
	}

	void UnixRenderer::CreateWindowSizeDependentResources()
	{
		createView();
		createPerspective();
	}

	void UnixRenderer::Update()
	{
		++mFrameCount;
		if (mFrameCount == UINT32_MAX)
		{
			mFrameCount == 0u;
		}
	}

	//--------------------------------------------------------------------------------------
	// Clean up the objects we've created
	//--------------------------------------------------------------------------------------
	void UnixRenderer::cleanupDevice()
	{
		for (DrawableObject* const object : mDrawableObjects)
		{
			object->Destroy();
		}
	}

	//--------------------------------------------------------------------------------------
	// Helper for compiling shaders with D3DCompile
	//
	// With VS 11, we could load up prebuilt .cso files instead...
	//--------------------------------------------------------------------------------------
	int32_t UnixRenderer::compileShaderFromFile(ShaderInfo* shaders)
	{
		mDeviceResources->SetProgram(loadShaders(shaders));
		glUseProgram(mDeviceResources->GetProgram());

		return GLFW_NO_ERROR;
	}

	bool UnixRenderer::WindowShouldClose()
	{
		return static_cast<bool>(glfwWindowShouldClose(mDeviceResources->GetWindow()));
	}

	//--------------------------------------------------------------------------------------
	// Initialize Renderer
	//--------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------------
	// Create OpenGL device and swap chain
	//--------------------------------------------------------------------------------------
	// Used to set up data for use later in the program
		// vertext information
		// image data
	// Specify shaders
	// Shader Plumbing

	//--------------------------------------------------------------------------------------
	// Render a frame
	//--------------------------------------------------------------------------------------
	void UnixRenderer::Render()
	{
		GLenum glError = GL_NO_ERROR;

		// 2. Clear buffer ---------------------------------------------------------------------------------------------
		static const float midnightBlue[] = { 0.098039225f, 0.098039225f, 0.439215720f, 0.000000000f };

		glClearBufferfv(GL_COLOR, 0, midnightBlue);

		// 3. Set Render Data ---------------------------------------------------------------------------------------------
		for (DrawableObject* const object : mDrawableObjects)
		{
			glBindTextureUnit(1u, object->Texture);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindTextureUnit error code: 0x%x, %u", glError, object->Texture);
			}

			glBindVertexArray(object->VertexArrayObject);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindVertexArray error code: 0x%x", glError);
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->Buffers[DrawableObject::ELEMENT_ARRAY_BUFFER]);
			if (glError = glGetError(); glError != GL_NO_ERROR)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "glBindBuffer error code: 0x%x", glError);
			}
		}

		// 5. Render ---------------------------------------------------------------------------------------------
		// Sending Data to OpenGL
			// Drawing == transferring vertex data to the OpenGL server
			// vertex == bundle of data values that are processed together
				// almost always includes positional data
				// values needed to determine the pixel's final color
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);
		if (glError = glGetError(); glError != GL_NO_ERROR)
		{
			LOGEF(eLogChannel::GRAPHICS, std::cerr, "glDrawElements error code: 0x%x", glError);
		}
	}

	GLuint UnixRenderer::loadShaders(ShaderInfo* shaders)
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

	const GLchar* UnixRenderer::readShader(const char* filename)
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

	void UnixRenderer::Destroy()
	{
		cleanupDevice();
		mDeviceResources = nullptr;
	}
}
#endif