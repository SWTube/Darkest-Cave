/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "CoreTypes.h"
#include "Object/Object.h"

namespace cave
{
	class World;
	class GameObject;
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
		void RemoveGameObject(const std::string& name);
		void RemoveGameObject(const char* name);
		void RemoveGameObject(GameObject& gameObject);
		void RemoveGameObjects(std::vector<GameObject*>& gameObjects);

		GameObject* FindGameObjectByName(std::string& name);
		GameObject* FindGameObjectByName(const char* name);

		GameObject* FindGameObjectByTag(std::string& tag);
		GameObject* FindGameObjectByTag(const char* tag);
		std::vector<GameObject*>&& FindGameObjectsByTag(std::string& tag);
		std::vector<GameObject*>&& FindGameObjectsByTag(const char* tag);

		void InitializeGameObjectsInLevel();
		void UpdateGameObjectsInLevel();
		void FixedUpdateGameObjectsInLevel();

		bool IsGameObjectInLevel(GameObject& gameObject);

		World* GetWorld() const;

	private:
		void addActiveGameObject(GameObject& gameObject);
		void removeActiveGameObject(GameObject& gameObject);

		void addTagGameObject(GameObject& gameObject);
		void removeTaggedGameObject(GameObject& gameObject);

		void destroyGameObjects();

	private:
		static std::unordered_set<std::string> mGlobalUniqueNames;

		std::unordered_map<std::string, GameObject*> mAllGameObjects;
		std::unordered_map<std::string, GameObject*> mActiveGameObjects;
		std::unordered_multimap<Tag*, GameObject*> mTaggedGameObjects;

		std::vector<GameObject*> mGameObjectsToRemove;

		World* mOwner;
	};

#ifdef CAVE_BUILD_DEBUG
	namespace LevelTest
	{

	}
#endif //CAVE_BUILD_DEBUG
}
