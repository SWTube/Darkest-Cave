/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include <unordered_map>

#include "Object/Obejct.h"

namespace cave
{
	class World;
	class GameObject;
	class Map;
	class Tag;

	class Level final : public Object
	{
	public:
		friend class GameObject;

		Level() = delete;
		Level(std::string& name);
		Level(const char* name);
		Level(const Level&) = delete;
		Level(Level&&) = delete;

		~Level();
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;

		void AddGameObject(GameObject& gameObject);
		void AddGameObjects(std::vector<GameObject*>& gameObjects);

		void RemoveGameObject(std::string& name);
		void RemoveGameObject(const char* name);
		void RemoveGameObject(GameObject& gameObject);
		void RemoveGameObjects(std::string& name);
		void RemoveGameObjects(const char* name);
		void RemoveGameObjects(std::vector<GameObject*>& gameObjects);

		GameObject* FindGameObjectByName(std::string& name);
		GameObject* FindGameObjectByName(const char* name);
		std::vector<GameObject*>&& FindGameObjectsByName(std::string& name);
		std::vector<GameObject*>&& FindGameObjectsByName(const char* name);

		GameObject* FindGameObjectByTag(std::string& tag);
		GameObject* FindGameObjectByTag(const char* tag);
		std::vector<GameObject*>&& FindGameObjectsByTag(std::string& tag);
		std::vector<GameObject*>&& FindGameObjectsByTag(const char* tag);

		void UpdateGameObjectInLevel();
		void UpdateAllGameObjectInLevel();

	private:
		void addActiveGameObject(GameObject& gameObject);
		void addActiveGameObjects(std::vector<GameObject*>& gameObjects);

		void removeActiveGameObject(GameObject& gameObject);
		void removeActiveGameObjects(std::vector<GameObject*>& gameObjects);

	private:
		std::unordered_multimap<std::string, GameObject*> mAllGameObjects;
		std::unordered_multimap<std::string, GameObject*> mActiveGameObjects;
		
		/*Read only.*/
		std::unordered_multimap<Tag*, GameObject*> mAllTaggedGameObjects;
		std::unordered_multimap<Tag*, GameObject*> mActiveTaggedGameObjects;

		Map* mMap;

		World* mWorld;
	};
}
