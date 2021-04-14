#pragma once

#include "GraphicsCommon.h"

#define FAILED(error) ((static_cast<int32_t>(error)) != GLFW_NO_ERROR)

namespace cave
{
	namespace Renderer
	{
		
		constexpr uint8_t TRIANGLES = 0u;
		constexpr uint8_t VERTEX_ARRAY_OBJECTS_COUNT = 1u;
		constexpr uint8_t ARRAY_BUFFER = 0u;
		constexpr uint8_t BUFFER_COUNT = 1u;
		constexpr uint8_t TEXTURE = 0u;
		constexpr uint8_t TEXTURE_COUNT = 1u;
		constexpr uint8_t V_POSITION = 0u;
		constexpr uint8_t V_TEX_COORD = 1u;

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

		typedef struct
		{
			GLenum       type;
			const char*  filename;
			GLuint       shader;
		} ShaderInfo;

		void Destroy();
		bool GlfwWindowShouldClose();

		int32_t Init(const char* title);

		// Render steps:
			// 1. Clear the window by calling glClearBufferfv()
			// 2. Issue the OpenGL calls required to render your object
			// 3. Request that the image is presented to the screen
		void Render();
	}
}