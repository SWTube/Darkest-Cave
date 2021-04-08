/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr;} }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr;} }

#include <Windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>


 //////////////////////////////////////
#include <vector>