/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "Device/DeviceResources.h"
#include "Object/DrawableObject.h"

namespace cave
{
	class GenericRenderer
	{
	public:
		GenericRenderer(DeviceResources* deviceResources);
		virtual ~GenericRenderer() = default;

		GenericRenderer(const GenericRenderer&) = delete;
		GenericRenderer& operator=(const GenericRenderer&) = delete;
		GenericRenderer& operator=(const GenericRenderer&&) = delete;

		virtual void CreateDeviceDependentResources() = 0;
		virtual void CreateWindowSizeDependentResources() = 0;
    	virtual void Update() = 0;
    	virtual void Render() = 0;
		virtual void Destroy() = 0;

		virtual void AddDrawableObject(DrawableObject*&& object);

		virtual bool WindowShouldClose() = 0;
		DeviceResources* const GetDeviceResources() const;
	protected:
		virtual int32_t createShaders() = 0;
		virtual int32_t createObjects() = 0;
		virtual void createView() = 0;
		virtual void createPerspective() = 0;

		DeviceResources* mDeviceResources = nullptr;
		uint32_t mIndexCount = 0u;
		uint32_t mFrameCount = 0u;

		std::vector<DrawableObject*> mDrawableObjects;
	};
}