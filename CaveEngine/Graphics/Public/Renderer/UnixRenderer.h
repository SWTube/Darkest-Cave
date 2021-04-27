/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreMinimal.h"
#include "Device/DeviceResources.h"
#include "Renderer/GenericRenderer.h"

#define BUFFER_OFFSET(a) (reinterpret_cast<void*>(a))
#define FAILED(error) ((static_cast<int32_t>(error)) != GLFW_NO_ERROR)

#ifdef __UNIX__
namespace cave
{
	//--------------------------------------------------------------------------------------
	// Structures
	//--------------------------------------------------------------------------------------
	struct GLFLOAT3
	{
		float x;
		float y;
		float z;
		GLFLOAT3() = default;
		GLFLOAT3(const GLFLOAT3& other) = default;
		GLFLOAT3& operator=(const GLFLOAT3& other) = default;
		GLFLOAT3(const GLFLOAT3&& other);
		GLFLOAT3& operator=(const GLFLOAT3&& other);
		constexpr GLFLOAT3(float inX, float inY, float inZ);
		GLFLOAT3(float* array);
	};

	struct GLFLOAT2
	{
		float x;
		float y;
		GLFLOAT2() = default;
		GLFLOAT2(const GLFLOAT2& other) = default;
		GLFLOAT2& operator=(const GLFLOAT2& other) = default;
		GLFLOAT2(const GLFLOAT2&& other);
		GLFLOAT2& operator=(const GLFLOAT2&& other);
		constexpr GLFLOAT2(float inX, float inY);
		GLFLOAT2(float* array);
	};

	typedef struct
	{
		GLenum       type;
		const char*  filename;
		GLuint       shader;
	} ShaderInfo;

	class UnixRenderer final : public GenericRenderer
	{
	public:
		UnixRenderer() = delete;
		UnixRenderer(DeviceResources* deviceResources);
		virtual ~UnixRenderer();

		UnixRenderer(const UnixRenderer&) = delete;
		UnixRenderer& operator=(const UnixRenderer&) = delete;
		UnixRenderer& operator=(const UnixRenderer&&) = delete;

		bool WindowShouldClose() override;

		void CreateDeviceDependentResources() override;
		void CreateWindowSizeDependentResources() override;
		void Update() override;
		// Render steps:
			// 1. Clear the window by calling glClearBufferfv()
			// 2. Issue the OpenGL calls required to render your object
			// 3. Request that the image is presented to the screen
		void Render() override;

		void Destroy() override;

	private:
		int32_t createShaders() override;
		int32_t createCube() override;
		void createView() override;
		void createPerspective() override;

		void cleanupDevice();
		int32_t compileShaderFromFile(ShaderInfo* shaders);
		GLuint loadShaders(ShaderInfo* shaders);
		const GLchar* readShader(const char* filename);

		static constexpr uint8_t TRIANGLES = 0u;
		static constexpr uint8_t VERTEX_ARRAY_OBJECTS_COUNT = 1u;
		static constexpr uint8_t ARRAY_BUFFER = 0u;
		static constexpr uint8_t ELEMENT_ARRAY_BUFFER = 1u;
		static constexpr uint8_t BUFFER_COUNT = 2u;
		static constexpr uint8_t TEXTURE = 0u;
		static constexpr uint8_t TEXTURE_COUNT = 1u;
		static constexpr uint8_t V_POSITION = 0u;
		static constexpr uint8_t V_TEX_COORD = 1u;

		//--------------------------------------------------------------------------------------
		// Member Variables
		//--------------------------------------------------------------------------------------
		uint8_t* msBackground = nullptr;
		uint32_t msBackgroundWidth = 0u;
		uint32_t msBackgroundHeight = 0u;
		uint32_t msBackgroundSampler = 0u;

		GLuint msVertexArrayObjects[VERTEX_ARRAY_OBJECTS_COUNT];
		GLuint msBuffers[BUFFER_COUNT] = { 0u, };
		GLuint msTextures[TEXTURE_COUNT];

		static constexpr GLuint msNumVertices = 4u;
	};

	typedef UnixRenderer Renderer;
}
#endif