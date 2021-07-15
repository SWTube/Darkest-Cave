/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include <unordered_map>

namespace cave
{
	class GameObject;
	class Map;
	class Tag;

	class Level final
	{
	public:
		Level() = delete;
		Level(std::string& name);
		Level(const char* name);
		Level(const Level&) = delete;
		Level(Level&&) = delete;

		~Level();
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;

		void SetName(std::string& name);
		void SetName(const char* name);

		void AddGameObject(GameObject& gameObject);
		void AddGameObjects(std::vector<GameObject*> gameObjects);

		void RemoveGameObject(std::string& name);
		void RemoveGameObject(const char* name);
		void RemoveGameObjects(std::string& name);
		void RemoveGameObjects(std::string& name);

		GameObject* FindGameObjectByName(std::string& name);
		GameObject* FindGameObjectByName(const char* name);
		std::vector<GameObject*>& FindGameObjectsByName(std::string& name);
		std::vector<GameObject*>& FindGameObjectsByName(const char* name);

		GameObject* FindGameObjectByTag(std::string& tag);
		GameObject* FindGameObjectByTag(const char* tag);
		std::vector<GameObject*>& FindGameObjectsByTag(std::string& tag);
		std::vector<GameObject*>& FindGameObjectsByTag(const char* tag);

		void UpdateGameObjectInLevel();
		void UpdateAllGameObjectInLevel();

	private:
		std::unordered_multimap<std::string, GameObject*> mActiveGameObjects;
		std::unordered_multimap<std::string, GameObject*> mDeactiveGameObjects;
		/*Read only.*/
		std::unordered_multimap<Tag*, GameObject*> mGameObjectsSortedByTag;

		std::string mName;
		Map* mMap;
	};
}
