/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Assertion/Assert.h"
#include "World/Level.h"
#include "World/World.h"

namespace cave
{
	std::unordered_set<std::string> World::mGlobalUniqueName;

	World::World(std::string& name) 
		: Object(name)
	{
		assert(IsValid() & mGlobalUniqueName.contains(name));
	}

	World::World(const char* name) 
		: Object(name)
	{
		assert(IsValid() & mGlobalUniqueName.contains(name));
	}

	World::~World()
	{
		assert(IsValid());
	}

	World::AddLevel(Level& level)
	{
		assert(IsValid() & level.IsValid());

		mLevels.insert({ level.GetGUID(), &level });
	}

	World::AddLevels(std::vector<Level*>& levels)
	{
		for (auto& level : levels)
		{
			AddLevel(*level);
		}
	}

	World::UpdateGameObjectsInWorld()
	{
		assert(IsValid());

		for (auto& iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		{
			iter->second->UpdateGameObjectsInLevel();
		}
	}

	World::FixedUpdateGameObjectsInWorld()
	{
		assert(IsValid());

		for (auto& iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		{
			assert(iter->second->IsValid());
			iter->second->UpdateGameObjectsInLevel();
		}
	}

	World::isLevelInWorld(Level& level)
	{
		assert(level.IsValid());

		auto iter = mLevels.find(level.GetGUID());

		return iter->second != mLevels.end() ? true : false;
	}
}