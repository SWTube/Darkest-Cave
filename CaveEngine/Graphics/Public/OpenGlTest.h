#pragma once

#include "Core.h"
#include "Graphics.h"

#define BUFFER_OFFSET(a) (static_cast<void*>(a))

namespace cave
{
	typedef struct
	{
		GLenum       type;
		const char*  filename;
		GLuint       shader;
	} ShaderInfo;

	void GlfwErrorCallback(int error, const char* message);
	void GlfwErrorInterpretor(int error);
	int GlfwTestMain(int argc, char* argv[]);
	GLuint LoadShaders(ShaderInfo* shaders);
} // namespace cave
