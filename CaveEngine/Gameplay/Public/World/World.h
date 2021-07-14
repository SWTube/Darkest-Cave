/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include <unordered_map>

namespace cave
{
	class Tag;
	class GameObject;
	class Level;

	class World final
	{
	public:
		World();
		World(const World&) = delete;
		World(World&&) = delete;

		~World();
		World& operator=(const World&) = delete;
		World& operator=(World&&) = delete;

		void AddLevel(Level& level);
		void RemoveLevel(std::string& name);
		void RemoveLevel(const char* name);

		void AddGameObject(GameObject& gameObject);
		void RemoveGameObject(std::string& name);
		void RemoveGameObject(const char* name);

		Level* FindLevelByName(std::string& name);
		Level* FindLevelByName(const char* name);

		GameObject* FindGameObjectByName(std::string& name);
		GameObject* FindGameObjectByName(const char* name);
		std::vector<GameObject*>& FindGameObjectsByName(std::string& name);
		std::vector<GameObject*>& FindGameObjectsByName(const char* name);

		GameObject* FindGameObjectByTag(std::string& tag);
		GameObject* FindGameObjectByTag(const char* tag);
		std::vector<GameObject*>& FindGameObjectsByTag(std::string& tag);
		std::vector<GameObject*>& FindGameObjectsByTag(const char* tag);

	private:
		std::unordered_map<std::string, Level*> mLevels;
		/*Read only.*/
		std::unordered_multimap<std::string, GameObject*> mGameObjects;
		/*Read only.*/
		std::unordered_multimap<Tag*, GameObject*> mGameObjectsSortByTag;

		Level* mCurrentLevel;
	};
}