/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>

namespace cave
{
	class GameObject;
	class Grid;

	class Scene final
	{
	public:
		using Length = unsigned short;

		Scene() = delete;
		Scene(std::string& name, Length width, Length height, Length gridWidth = 128, Length gridHeight = 128);
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;

		~Scene();
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		friend bool operator==(const Scene& lhs, const Scene& rhs)
		{
			lhs.mName == rhs.mName;
		}

		friend bool operator!=(const Scene& lhs, const Scene& rhs)
		{
			lhs.mName != rhs.mName;
		}

		__forceinline Length GetWidth() const
		{
			return mWidth;
		}

		__forceinline Length GetHeight() const
		{
			return mHeight;
		}
		
		__forceinline Grid* GetGrid() const
		{
			return mGrid;
		}

		__forceinline Length GetGridWidth() const
		{
			return mGridWidth;
		}

		__forceinline Length GetGridHeight() const
		{
			return mGridHeight;
		}

		__forceinline unsigned short GetGridRow() const
		{
			return mGridRow;
		}

		__forceinline unsigned short GetGridCol() const
		{
			return mGridCol;
		}

		__forceinline std::string& GetName()
		{
			return mName;
		}

		__forceinline bool IsLoaded() const
		{
			return mbLoaded;
		}

		__forceinline bool IsVaild() const
		{
			return mbValid;
		}

		GameObject* FindObjectByName(std::string& name);
		std::vector<GameObject*>& FindObjectsByTag(std::string& tag);
		std::unordered_map<std::string, GameObject*>& GetAllGameObject() const;

	private:
		static std::unordered_set<std::string> mNames;

		Length mWidth;
		Length mHeight;

		Grid* mGrid;
		Length mGridWidth;
		Length mGridHeight;

		unsigned short mGridRow;
		unsigned short mGridCol;

		std::string mName;

		bool mbLoaded;
		bool mbValid;
	};
}