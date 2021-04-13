/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include "Core.h"

#include "GraphicsCommon.h"
#if defined(__WIN32__)
	#include "Test/Resource.h"
	#include "Renderer/CaveApplication.h" 
	#include "Renderer/CaveNode.h" 
	#include "Renderer/CaveRenderer.h"
#elif defined(__UNIX__)
	#include "Renderer/GlRenderer.h"
#endif
