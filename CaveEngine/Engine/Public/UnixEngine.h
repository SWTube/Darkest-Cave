/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"
#include "GenericEngine.h"

#if 1
namespace cave
{
	class UnixEngine final : public GenericEngine
	{
	public:
		UnixEngine();
		virtual ~UnixEngine() = default;

		const GLFWwindow* GetWindowHandle() override;
		int32_t CreateDesktopWindow() override;
		int32_t Run(DeviceResources* deviceResources, Renderer* renderer) override;
	private:
		GLFWwindow* mWindow = nullptr;
	};

	typedef UnixEngine Engine;
}
#endif