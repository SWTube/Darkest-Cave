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
		Level() = delete;
		Level(const char* name);
		Level(std::string& name);
		Level(const std::string& name);
		Level(const Level&) = delete;
		Level(Level&&) = delete;

		~Level();
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;

		void AddGameObject(const char* name);
		void AddGameObject(std::string& name);
		void AddGameObject(const std::string& name);

		void AddRemoveGameObjectList(const char* name);
		void AddRemoveGameObjectList(std::string& name);
		void AddRemoveGameObjectList(const std::string& name);

		void RemoveGameObjects();

		GameObject* FindGameObjectByName(const char* name);
		GameObject* FindGameObjectByName(std::string& name);
		GameObject* FindGameObjectByName(const std::string& name);

		std::vector<GameObject*>&& FindGameObjectsByTag(const char* tag);
		std::vector<GameObject*>&& FindGameObjectsByTag(std::string& tag);
		std::vector<GameObject*>&& FindGameObjectsByTag(const std::string& tag);

		std::unordered_map<std::string, GameObject*>& GetGameObjects();

		void SetWorldOwner(World* owner);
		World* GetWorldOwner() const;

	private:
		static std::unordered_set<std::string> mGlobalUniqueNames;

		std::unordered_map<std::string, GameObject*> mGameObjects;
		std::vector<GameObject*> mRemoveGameObjectList;

		bool mbInitialize = false;

		World* mOwner = nullptr;
	};
}
