/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CaveEngineConfig.h"

#if defined(__UNIX__)
	#include <cstdio>
	#define GLFW_INCLUDE_NONE
	#include "GL/gl3w.h"
	#include "Glfw.h"

	#define BUFFER_OFFSET(a) (reinterpret_cast<void*>(a))
#elif defined(__WIN32__)
	#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr;} }
	#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr;} }

	#include <vector>

	#include <windows.h>
	#include <d3d11_1.h>
	#include <d3dcompiler.h>
	#include <directxmath.h>
	#include <directxcolors.h>
	#include <d2d1.h>
	#include <d2d1helper.h>
	#include <dwrite.h>
	#include <wincodec.h>
#endif