/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace cave
{
	class GameObject;

	class Grid final
	{
	public:
		friend class Scene;

		using Length = unsigned short;

		Grid();
		Grid(const Grid& other) = delete;
		Grid(Grid&& other) = delete;

		~Grid();
		Grid& operator=(const Grid& other) = delete;
		Grid& operator=(Grid&& other) = delete;

		void AddObject(GameObject& object);
		void RemoveObject(GameObject& object);
		void MoveObject(std::string& name);

		__forceinline unsigned short GetRow() const
		{
			return mRow;
		}

		__forceinline unsigned short GetCol() const
		{
			return mCol;
		}

		std::unordered_map<std::string, GameObject*>& GetObjects(bool isActivate = true);

		GameObject* FindObjectByName(std::string& name);
		std::vector<GameObject*>& FindObjectsByTag(std::string& tag);

	private:
		__forceinline void SetRow(unsigned short row)
		{
			mRow = row;
		}

		__forceinline void SetCol(unsigned short col)
		{
			mCol = col;
		}

		__forceinline void SetScene(Scene& scene)
		{
			mScene = &scene;
		}

	private:
		unsigned short mRow;
		unsigned short mCol;

		Scene* mScene;

		std::unordered_map<std::string, std::unordered_multimap<std::string, GameObject*>> mActivateObject;
		std::unordered_map<std::string, GameObject*> mDeactivateObject;
	};
}