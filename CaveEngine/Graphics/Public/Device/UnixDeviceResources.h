/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "GraphicsApiPch.h"
#include "Device/GenericDeviceResources.h"

namespace cave
{
	class UnixDeviceResources final : public GenericDeviceResources
	{
	public:
		constexpr UnixDeviceResources() = default;
		constexpr UnixDeviceResources(const UnixDeviceResources&) = default;
		UnixDeviceResources& operator=(const UnixDeviceResources&) = default;
		virtual ~UnixDeviceResources() = default;


		int32_t CreateDeviceResources(GLFWwindow* window) override;
		int32_t CreateWindowResources(GLFWwindow* window) override;
		int32_t CreateDeviceResources() override;

		int32_t ConfigureBackBuffer() override;
		int32_t ReleaseBackBuffer() override;
		int32_t GoFullScreen() override;
		int32_t GoWindowed() override;

		float GetAspectRatio() override;

		void Present() override;
	};

	typedef UnixDeviceResources DeviceResources;
}