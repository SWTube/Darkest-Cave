/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Renderer/GenericRenderer.h"

namespace cave
{
	GenericRenderer::GenericRenderer(DeviceResources* deviceResources)
		: mDeviceResources(deviceResources)
		, mFrameCount(0u)
	{
	}

	DeviceResources* const GenericRenderer::GetDeviceResources() const
	{
		return mDeviceResources;
	}
}