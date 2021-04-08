/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Core.h"
#include "Graphics.h"

using namespace cave;

enum eVaoIds
{
	TRIANGLES,
	NUM_VAOS
};

enum eBufferIds
{
	ARRAY_BUFFER,
	NUM_BUFFERS
};

enum eAttribIds
{
	V_POSITION = 0
};

GLuint gVaos[eVaoIds::NUM_VAOS];
GLuint gBuffers[eBufferIds::NUM_BUFFERS];
const GLuint gNumVertices = 6;

void Draw();
void GlfwErrorCallback(int glfwError, const char* message);
void InitGame();
void RunGame();

int main(int argc, char* argv[])
{
	int errorCode = glfwInit();
	glfwSetErrorCallback(GlfwErrorCallback);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Triangles", nullptr, nullptr);
	// errorCode = glfwGetError(nullptr);
	// LOGDF(eLogChannel::GRAPHICS, std::cout, "GLFW Window Creation Result: %x", errorCode);
	// if (errorCode == GLFW_NOT_INITIALIZED)
	// {
	// 	LOGDF(eLogChannel::GRAPHICS, std::cout, "GLFW NOT INITIALIZED", errorCode);
	// 	return -1;
	// }

	// if (window == nullptr)
	// {
	// 	LOGD(eLogChannel::GRAPHICS, std::cout, "NO");
	// }

	// glfwMakeContextCurrent(window);
	// gl3wInit();

	// InitGame();

	// while (!glfwWindowShouldClose(window))
	// {
	// 	Draw();
	// 	glfwSwapBuffers(window);
	// 	glfwPollEvents();
	// }

	glfwDestroyWindow(window);
	
	glfwTerminate();

	return 0;
}

void Draw()
{
	static const float black[] = {
		0.0f, 0.0f, 0.0f, 0.0f
	};
	glClearBufferfv(GL_COLOR, 0, black);
	
	glBindVertexArray(gVaos[eVaoIds::TRIANGLES]);
	glDrawArrays(GL_TRIANGLES, 0, gNumVertices);
}

void GlfwErrorCallback(int glfwError, const char* message)
{
	LOGDF(eLogChannel::GRAPHICS, std::cout, "GLFW Error: %s", message);
}

void InitGame()
{
	// Initialize Memory
	// Initialize File System Manager
	// Initialize Video Manager
	// Initialialize Render Manager
	// Initialize Animation Manager
	// Initialize Physics Manager
	// Initialize Game Manager

	static const GLfloat sVertices[gNumVertices][2] = {
		{ -0.90, -0.90 }, // Triangle 1
		{  0.85, -0.90 },
		{ -0.90,  0.85 },
		{  0.90, -0.85 }, // Triangle 2
		{  0.90,  0.90 },
		{ -0.85,  0.90 }
	};

	glCreateBuffers(eBufferIds::NUM_BUFFERS, gBuffers);
	glNamedBufferStorage(gBuffers[eBufferIds::ARRAY_BUFFER], sizeof(sVertices), sVertices, 0);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, nullptr }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glGenVertexArrays(eVaoIds::NUM_VAOS, gVaos);
	glBindVertexArray(gVaos[eVaoIds::TRIANGLES]);
	glBindBuffer(GL_ARRAY_BUFFER, gBuffers[eBufferIds::ARRAY_BUFFER]);
	glVertexAttribPointer(eAttribIds::V_POSITION, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(eAttribIds::V_POSITION);

}

void RunGame()
{

}
