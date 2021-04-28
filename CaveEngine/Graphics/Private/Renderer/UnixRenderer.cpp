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

	eResult UnixRenderer::createShader(Shader& shader)
	{
		shader.Compile();
		mDeviceResources->SetProgram(shader.GetProgram());

		return eResult::CAVE_OK;
	}

	eResult UnixRenderer::createShaders()
	{
		for (Shader* const shader : mShaders)
		{
			shader->Compile();
			mDeviceResources->SetProgram(shader->GetProgram());
		}

		return eResult::CAVE_OK;
	}

	eResult UnixRenderer::createObjects()
	{
		LOGDF(eLogChannel::GRAPHICS, std::cout, "number of objects: %u", mDrawableObjects.size());

		for (DrawableObject* const object : mDrawableObjects)
		{
			if (eResult result = object->Init(mDeviceResources->GetProgram()); result != eResult::CAVE_OK)
			{
				return result;
			}
		}

		return eResult::CAVE_OK;
	}

	eResult UnixRenderer::createObject(DrawableObject& object)
	{
		return object.Init(mDeviceResources->GetProgram());
	}

	void UnixRenderer::createView()
	{
		if (mShaders.size() != 0)
		{
			glm::vec3 eye = glm::vec3(0.0f, 0.0f, -2.0f);
			glm::vec3 at = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

			mView = glm::lookAtLH(eye, at, up);
			int32_t viewLocation = glGetUniformLocation(mDeviceResources->GetProgram(), "View");
			if (viewLocation < 0)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "Failed to get uniform location: %s, error code: 0x%x", "View", glGetError());
				assert(false);
			}
			glUniformMatrix4fv(viewLocation, 1, false, glm::value_ptr(mView));
		}
	}

	void UnixRenderer::createPerspective()
	{
		if (mShaders.size() != 0)
		{
			// mProjection = glm::ortho(0.0f, static_cast<float>(mDeviceResources->GetWidth()), static_cast<float>(mDeviceResources->GetHeight()), 0.0f,-1.0f, 1.0f);
			mProjection = glm::perspectiveFovLH(glm::quarter_pi<float>(), static_cast<float>(mDeviceResources->GetWidth()), static_cast<float>(mDeviceResources->GetHeight()), 0.01f, 100.0f);
			int32_t projectionLocation = glGetUniformLocation(mDeviceResources->GetProgram(), "Projection");
			if (projectionLocation < 0)
			{
				LOGEF(eLogChannel::GRAPHICS, std::cerr, "Failed to get uniform location: %s, error code: 0x%x", "Projection", glGetError());
				assert(false);
			}
			glUniformMatrix4fv(projectionLocation, 1, false, glm::value_ptr(mProjection));
		}
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
		for (DrawableObject* const object : mDrawableObjects)
		{
			object->Update();
		}

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
			object->Render();
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