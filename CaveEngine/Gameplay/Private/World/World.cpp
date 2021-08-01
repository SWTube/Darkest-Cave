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
		assert(IsValid() & (!mGlobalUniqueName.contains(name)));
	}

	World::World(const char* name) 
		: Object(name)
	{
		assert(IsValid() & (!mGlobalUniqueName.contains(name)));
	}

	World::~World()
	{
		assert(IsValid());
		for (auto iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		{
			Level* level = iter->second;
			assert(level != nullptr);
			iter->second = nullptr;
			delete level;
		}
		mLevels.clear();
	}

	void World::AddLevel(Level& level)
	{
		assert(IsValid() & level.IsValid());

		mLevels.insert({ level.GetGUID(), &level });
	}

	 void World::AddLevels(std::vector<Level*>& levels)
	{
		for (auto& level : levels)
		{
			AddLevel(*level);
		}
	}

	 void World::InitializeGameObjectsInWorld()
	 {
		 assert(IsValid());

		 for (auto iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		 {
			 assert(iter->second->IsValid());
			 iter->second->InitializeGameObjectsInLevel();
		 }
	}

	void World::UpdateGameObjectsInWorld()
	{
		assert(IsValid());

		for (auto iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		{
			assert(iter->second->IsValid());
			iter->second->UpdateGameObjectsInLevel();
		}
	}

	void World::FixedUpdateGameObjectsInWorld()
	{
		assert(IsValid());

		for (auto iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		{
			assert(iter->second->IsValid());
			iter->second->FixedUpdateGameObjectsInLevel();
		}
	}

	bool World::isLevelInWorld(Level& level)
	{
		assert(IsValid() & level.IsValid());

		auto iter = mLevels.find(level.GetGUID());

		return iter != mLevels.end() ? true : false;
	}
}