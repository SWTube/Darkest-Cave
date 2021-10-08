/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>

#include "CoreTypes.h"
#include "Physics.h"
#include "Object/Object.h"

namespace cave
{
	class GameObject;
	class Level;

	class World final : public Object
	{
	public:
		friend class Level;

		World() = delete;
		World(const char* name);
		World(std::string& name);
		World(const std::string& name);
		World(const World&) = delete;
		World(World&&) = delete;

		~World();
		World& operator=(const World&) = delete;
		World& operator=(World&&) = delete;

		void AddLevel(const char* name);
		void AddLevel(std::string& name);
		void AddLevel(const std::string& name);

		void RemoveLevel(const char* name);
		void RemoveLevel(std::string& name);
		void RemoveLevel(const std::string& name);

		Level* FindLevel(const char* name);
		Level* FindLevel(std::string& name);
		Level* FindLevel(const std::string& name);

		void AddGameObject(const char* name);
		void AddGameObject(std::string& name);
		void AddGameObject(const std::string& name);

		void RemoveGameObject(const char* name);
		void RemoveGameObject(std::string& name);
		void RemoveGameObject(const std::string& name);

		GameObject* FindGameObject(const char* name);
		GameObject* FindGameObject(std::string& name);
		GameObject* FindGameObject(const std::string& name);

		void SetGravity(b2Vec2 gravity);
		b2Vec2 GetGravity() const;

		b2World* GetPhysicsWorld() const;

		void Init();
		void Update(float elapsedTimestep);
		void FixedUpdate(float elapsedTimestep);

		bool IsInitialized() const;

	private:
		static std::unordered_set<std::string> mGlobalUniqueName;

		std::unordered_map<std::string, GameObject*> mAllGameObjects;
		std::unordered_map<std::string, GameObject*> mActiveGameObjects;

		std::vector<GameObject*> mRemoveGameObjectList;

		std::unordered_map<std::string, Level*> mLevels;
		
		b2World* mPhysicsWorld = nullptr;
		bool mbInitialized = false;
	};
}
