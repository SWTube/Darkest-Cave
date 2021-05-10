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
		for (Shader& shader : mShaders)
		{
			shader.Compile();
			mDeviceResources->SetProgram(shader.GetProgram());
		}

		return eResult::CAVE_OK;
	}

	eResult UnixRenderer::createObjects()
	{
		LOGDF(eLogChannel::GRAPHICS, std::cout, "number of objects: %u", mSprites.size());

		for (Sprite& object : mSprites)
		{
			if (eResult result = object.Init(mDeviceResources->GetProgram(), mDeviceResources->GetWidth(), mDeviceResources->GetHeight()); result != eResult::CAVE_OK)
			{
				return result;
			}
		}

		return eResult::CAVE_OK;
	}

	eResult UnixRenderer::createObject(Sprite& object)
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
		for (Sprite& object : mSprites)
		{
			object.Update();
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
		for (Sprite& object : mSprites)
		{
			object.Destroy();
		}
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
		for (Sprite& object : mSprites)
		{
			object.Render();
		}
	}

	void UnixRenderer::Destroy()
	{
		cleanupDevice();
		GenericRenderer::Destroy();
		mDeviceResources = nullptr;
	}
}
#endif