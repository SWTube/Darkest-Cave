#pragma once

#include <cstdio>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "Core.h"

#define BUFFER_OFFSET(a) (static_cast<void*>(a))

namespace cave
{
	typedef struct
	{
		GLenum       type;
		const char*  filename;
		GLuint       shader;
	} ShaderInfo;

	GLuint LoadShaders(ShaderInfo* shaders);
} // namespace cave
