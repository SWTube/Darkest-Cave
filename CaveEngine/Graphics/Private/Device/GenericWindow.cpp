/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Device/GenericWindow.h"

namespace cave
{
	GenericWindow::GenericWindow(uint32_t width, uint32_t height, const char* title)
		: mWidth(width)
		, mHeight(height)
		, mTitle(title)
	{
	}
}