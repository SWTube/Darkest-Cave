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
		mDrawableObjects.reserve(1);
	}

	GenericRenderer::~GenericRenderer()
	{
		for (Shader* const shader : mShaders)
		{
			delete shader;
		}

		for (DrawableObject* const drawableObject : mDrawableObjects)
		{
			delete drawableObject;
		}
	}

	DeviceResources* const GenericRenderer::GetDeviceResources() const
	{
		return mDeviceResources;
	}

	void GenericRenderer::AddDrawableObject(DrawableObject*&& object)
	{
		mDrawableObjects.push_back(std::move(object));
		createObject(*mDrawableObjects.back());
	}

	void GenericRenderer::AddShader(Shader*&& shader)
	{
		mShaders.push_back(std::move(shader));
		createShader(*mShaders.back());
		CreateWindowSizeDependentResources();
	}
}