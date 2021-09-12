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
		: Object(name, mGlobalUniqueName)
	{
		assert(IsValid());
	}

	World::World(const char* name) 
		: Object(name, mGlobalUniqueName)
	{
		assert(IsValid());
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

		mLevels.insert({ level.GetName(), &level });
	}

	void World::AddLevels(std::vector<Level*>& levels)
	{
		for (auto& level : levels)
		{
			AddLevel(*level);
		}
	}

	void World::RemoveLevel(Level& level)
	{
		assert(level.IsValid());
		RemoveLevel(level.GetName());
	}

	void World::RemoveLevel(const std::string& name)
	{
		assert(IsValid());

		auto iter = mLevels.find(name);

		if (iter != mLevels.end())
		{
			Level* tmp = iter->second;
			mLevels.erase(iter);
			delete tmp;
		}
	}

	void World::RemoveLevel(std::string& name)
	{
		assert(IsValid());

		auto iter = mLevels.find(name);

		if (iter != mLevels.end())
		{
			Level* tmp = iter->second;
			mLevels.erase(iter);
			delete tmp;
		}
	}

	void World::RemoveLevel(const char* name)
	{
		assert(IsValid());

		auto iter = mLevels.find(name);

		if (iter != mLevels.end())
		{
			Level* tmp = iter->second;
			mLevels.erase(iter);
			delete tmp;
		}
	}

	void World::RemoveLevels(std::vector<Level*>& levels)
	{
		for (auto& level : levels)
		{
			RemoveLevel(*level);
		}
	}

	void World::InitializeGameObjectsInWorld()
	{
		assert(IsValid());

		for (auto iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		{
			iter->second->InitializeGameObjectsInLevel();
		}
	}

	void World::UpdateGameObjectsInWorld()
	{
		assert(IsValid());

		for (auto iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		{
			iter->second->UpdateGameObjectsInLevel();
		}
	}

	void World::FixedUpdateGameObjectsInWorld()
	{
		assert(IsValid());

		for (auto iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		{
			iter->second->FixedUpdateGameObjectsInLevel();
		}
	}

	bool World::IsLevelInWorld(Level& level)
	{
		assert(IsValid() & level.IsValid());

		auto iter = mLevels.find(level.GetName());

		return iter != mLevels.end() ? true : false;
	}
}