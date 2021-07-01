/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>

namespace cave
{
	class GameObject;
	class Grid;

	class Scene final
	{
	public:
		using Length = unsigned short;

		Scene() = delete;
		Scene(Length width, Length height, std::string& name);
		Scene(Length width, Length height, Length gridWidth, Length gridHeight, std::string& name);
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;

		~Scene();
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		__forceinline Length GetWidth() const
		{
			return mWidth;
		}

		__forceinline Length GetHeight() const
		{
			return mHeight;
		}

		__forceinline Length GetGridWidth() const
		{
			return mGridWidth;
		}
			
		__forceinline Length GetGridHeight() const
		{
			return mGridHeight;
		}
		
		__forceinline Grid** GetGrid() const
		{
			return mGrid;
		}

		__forceinline std::string GetName() const
		{
			return mName;
		}

		GameObject* FindObjectByName(std::string& name);
		std::vector<GameObject*> FindObjectsByTag(std::string& tag);

	private:
		__forceinline void SetWidth(Length width)
		{
			mWidth = width;
		}
		__forceinline void SetHeight(Length height)
		{
			mHeight = height;
		}

		__forceinline void SetGridWidth(Length width)
		{
			mGridWidth = width;
		}

		__forceinline void SetGridHeight(Length height)
		{
			mGridHeight = height;
		}

		__forceinline void SetName(std::string& name)
		{
			mName = std::move(name);
		}

	private:
		Length mWidth;
		Length mHeight;
		
		Length mGridWidth;
		Length mGridHeight;

		Grid** mGrid;

		std::string mName;
	};
}