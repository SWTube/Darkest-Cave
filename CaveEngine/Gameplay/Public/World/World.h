/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "CoreTypes.h"
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

		void InitializeGameObjectsInWorld();
		void UpdateGameObjectsInWorld();
		void FixedUpdateGameObjectsInWorld();

	private:
		bool isLevelInWorld(Level& level);

	private:
		static std::unordered_set<std::string> mGlobalUniqueName;
		std::unordered_map<uint32_t, Level*> mLevels;

		Map* mMap;
	};
}