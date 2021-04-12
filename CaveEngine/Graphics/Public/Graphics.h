/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "GraphicsCommon.h"
#ifndef __linux__
	#include <windows.h>
	#include <d3d11_1.h>
	#include <d3dcompiler.h>
	#include <directxmath.h>
	#include <directxcolors.h>
	#include "Test/Resource.h"
	#include "Renderer/CaveApplication.h" 
	#include "Renderer/CaveNode.h" 
	#include "Renderer/CaveRenderer.h"
#else
	#include "OpenGlTest.h"
#endif
