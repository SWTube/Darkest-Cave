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
	class Level;
	class Map;

	class World final : public Object
	{
	public:
		friend class Level;

		World() = delete;
		World(std::string& name);
		World(const char* name);
		World(const World&) = delete;
		World(World&&) = delete;

		~World();
		World& operator=(const World&) = delete;
		World& operator=(World&&) = delete;

		void AddLevel(Level& level);
		void AddLevels(std::vector<Level*>& levels);

		void RemoveLevel(Level& level);
		void RemoveLevel(const std::string& name);
		void RemoveLevel(std::string& name);
		void RemoveLevel(const char* name);
		void RemoveLevels(std::vector<Level*>& levels);

		void SetGravity(b2Vec2 gravity);
		b2Vec2 GetGravity() const;

		void InitializeGameObjectsInWorld();
		void UpdateGameObjectsInWorld();
		void FixedUpdateGameObjectsInWorld();

		bool IsLevelInWorld(Level& level);

	private:
		static std::unordered_set<std::string> mGlobalUniqueName;
		std::unordered_map<std::string, Level*> mLevels;
		b2World* mPhysicsWorld;
	};
}