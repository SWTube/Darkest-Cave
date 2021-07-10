/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <cassert>

#include "Scene/Grid.h"
#include "Scene/Scene.h"

namespace cave
{
	std::unordered_set<std::string> Scene::mNames;

	Scene::Scene(std::string& name, Length width, Length height, Length gridWidth, Length gridHeight) :
		mWidth(width),
		mHeight(height),
		mGridWidth(gridWidth),
		mGridHeight(gridHeight),
		mbValid(true),
		mbLoaded(false)
	{
		assert(mGridHeight != 0);
		assert(mGridWidth != 0);
		assert(mNames.find(name) == mNames.end());

		mGridHeight = mHeight / mGridHeight + 1;
		mGridCol = mWidth / gridWidth + 1;

		mName = std::move(name);

		mGrid = new Grid[mGridRow * mGridCol];
		for (size_t row = 0; row < mGridRow; ++row)
		{
			for (size_t col = 0; col < mGridCol; ++col)
			{
				unsigned int index = mGridRow * row + col;
				mGrid[index].SetScene(*this);
				mGrid[index].SetRow(row);
				mGrid[index].SetCol(col);
			}
		}
	}

	Scene::~Scene()
	{
		delete[] mGrid;
	}
}