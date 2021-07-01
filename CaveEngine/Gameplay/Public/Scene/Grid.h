/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <vector>
#include <map>

namespace cave
{
	class GameObject;

	class Grid final
	{
	public:
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

		GameObject* FindObjectByName(std::string& name);
		std::vector<GameObject*>& FindObjectsByTag(std::string& tag);

	private:
		std::map<std::string, GameObject*> mActivateObject;
		std::map<std::string, GameObject*> mDeactivateObject;
	};
}