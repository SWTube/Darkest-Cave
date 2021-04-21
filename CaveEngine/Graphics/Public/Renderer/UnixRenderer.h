/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreMinimal.h"

#define BUFFER_OFFSET(a) (reinterpret_cast<void*>(a))
#define FAILED(error) ((static_cast<int32_t>(error)) != GLFW_NO_ERROR)

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

	class UnixRenderer final
	{
	public:
		static void Destroy();
		static bool GlfwWindowShouldClose();

		static int32_t Init(uint32_t width, uint32_t height, const char* title);

		// Render steps:
			// 1. Clear the window by calling glClearBufferfv()
			// 2. Issue the OpenGL calls required to render your object
			// 3. Request that the image is presented to the screen
		static void Render();

		static void OnChar(uint32_t codepoint);
		static void OnKey(int32_t key, int32_t scancode, int32_t action, int32_t mods);
		static void Resize(uint32_t width, uint32_t height);
	private:
		static void cleanupDevice();
		static int32_t compileShaderFromFile(ShaderInfo* shaders);
		static void errorCallback(int errorCode, const char* description);
		static int32_t initWindow(uint32_t width, uint32_t height, const char* title);
		static int32_t initDevice();
		static GLuint loadShaders(ShaderInfo* shaders);
		static const GLchar* readShader(const char* filename);

		static void windowSizeCallback(GLFWwindow* window, int32_t width, int32_t height);
		static void keyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);
		static void charCallback(GLFWwindow* window, uint32_t codepoint);

		static char glfwKeyToChar(int32_t key);

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
		// Global Variables
		//--------------------------------------------------------------------------------------
		static GLFWwindow* msWindow;
		static uint32_t msWidth;
		static uint32_t msHeight;
		static GLuint msProgram;

		static uint8_t* msBackground;
		static uint32_t msBackgroundWidth;
		static uint32_t msBackgroundHeight;
		static uint32_t msBackgroundSampler;

		static GLuint msVertexArrayObjects[VERTEX_ARRAY_OBJECTS_COUNT];
		static GLuint msBuffers[BUFFER_COUNT];
		static GLuint msTextures[TEXTURE_COUNT];

		static constexpr GLuint msNumVertices = 4u;
	};

	typedef UnixRenderer Renderer;
}