/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <unordered_map>

#include "CoreTypes.h"
#include "Object/Obejct.h"

namespace cave
{
	class Level;

	class World final : public Object
	{
	public:
		World() = delete;
		World(std::string& name);
		World(const char* name);
		World(const World&) = delete;
		World(World&&) = delete;

		~World();
		World& operator=(const World&) = delete;
		World& operator=(World&&) = delete;

		void AddLevel(Level& level);
		void RemoveLevel(std::string& name);
		void RemoveLevel(const char* name);

		Level* FindLevelByName(std::string& name);
		Level* FindLevelByName(const char* name);

		void UpdateGameObjectInCurrentLevel();

	private:
		std::unordered_map<std::string, Level*> mLevels;
		Level* mPreviousLevel;
		Level* mCurrentLevel;
		Level* mNextLevel;

		std::string mName;
	};
}