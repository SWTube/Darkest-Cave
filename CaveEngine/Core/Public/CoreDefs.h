/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <windows.h>

#if defined(__clang__)
	//#include "Clang/ClangPlatform.h"
#else
	//#include "MSVC/MSVCPlatform.h"
#endif

// Base defines, must define these for the platform, there are no defaults
#define DESKTOP							1
#if defined( _WIN64 )
	#define IS_64BITS					1
#else
	#define IS_64BITS					0
#endif

#define IS_32BITS				(!IS_64BITS)

#ifndef FORCEINLINE
	#define FORCEINLINE __forceinline
#endif