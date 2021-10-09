/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#if !defined(WIN32)
	#include "CaveEngineConfig.h"
#else
	 /*--------------------------------------------------------------------------------
		 Build configuration coming from CAVE, do not modify
	 --------------------------------------------------------------------------------*/

	 // Ensure that we have one, and only one build config coming from UBT
	#if CAVE_BUILD_DEBUG + CAVE_BUILD_DEVELOPMENT + CAVE_BUILD_TEST + CAVE_BUILD_RELEASE != 1
	#error Exactly one of [CAVE_BUILD_DEBUG CAVE_BUILD_DEVELOPMENT CAVE_BUILD_TEST CAVE_BUILD_RELEASE] should be defined to be 1
	#endif

	#ifndef __WIN32__
	#define __WIN32__
	#endif

	#define PLATFORM_NAME Windows

	#define FORCEINLINE __forceinline
#endif

	#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr;} }
	#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr;} }

	#include <windows.h>
	#include <d3d11_1.h>
	#include <d3dcompiler.h>
	#include <directxmath.h>
	#include <directxcolors.h>
	#include <d2d1.h>
	#include <d2d1helper.h>
	#include <dwrite.h>
	#include <dwrite_3.h>
