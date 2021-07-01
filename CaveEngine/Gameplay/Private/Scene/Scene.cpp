/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Scene/Grid.h"
#include "Scene/Scene.h"

namespace cave
{
	Scene::Scene(Length width, Length height, std::string& name) :
		mWidth(width),
		mHeight(height),
		mGridWidth(64),
		mGridHeight(64),
		mName(std::move(name))
	{
		Length y = mHeight / mGridHeight + 1;
		Length x = mWidth / mGridWidth + 1;

		mGrid = new Grid*[y];
		for (size_t index = 0; index < y; ++index)
		{
			mGrid[index] = new Grid[x];
		}
	}

	Scene::Scene(Length width, Length height, Length gridWidth, Length gridHeight, std::string& name) :
		mWidth(width),
		mHeight(height),
		mGridWidth(gridWidth),
		mGridHeight(gridHeight),
		mName(std::move(name))
	{
		Length y = mHeight / mGridHeight + 1;
		Length x = mWidth / mGridWidth + 1;

		mGrid = new Grid * [y];
		for (size_t index = 0; index < y; ++index)
		{
			mGrid[index] = new Grid[x];
		}
	}

	Scene::~Scene()
	{
		Length y = mHeight / mGridHeight + 1;
		Length x = mWidth / mGridWidth + 1;

		for (size_t index = 0; index < y; ++index)
		{
			delete[] mGrid[index];
		}
		delete[] mGrid;
	}
}