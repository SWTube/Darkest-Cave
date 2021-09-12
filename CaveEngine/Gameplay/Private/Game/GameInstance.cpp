/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Game/GameInstance.h"
#include "Assertion/Assert.h"
#include "World/World.h"
#include "Object/TagPool.h"

namespace cave
{
	GameInstance::GameInstance()
	{
		TagPool::Init();
	}

	GameInstance::~GameInstance()
	{
		Shutdown();
	}

	void GameInstance::Init()
	{
		for (auto iter = mWorlds.begin(); iter != mWorlds.end(); ++iter)
		{
			iter->second->InitializeGameObjectsInWorld();
		}
	}

	void GameInstance::FixedUpdate()
	{
		for (auto iter = mWorlds.begin(); iter != mWorlds.end(); ++iter)
		{
			iter->second->FixedUpdateGameObjectsInWorld();
		}
	}

	void GameInstance::Update()
	{
		for (auto iter = mWorlds.begin(); iter != mWorlds.end(); ++iter)
		{
			iter->second->UpdateGameObjectsInWorld();
		}
	}

	void GameInstance::Shutdown()
	{
		for (auto iter = mWorlds.begin(); iter != mWorlds.end(); ++iter)
		{
			World* world = iter->second;
			assert(world != nullptr);
			iter->second = nullptr;
			delete world;
		}

		mWorlds.clear();

		TagPool::ShutDown();
	}

	void GameInstance::AddWorld(World& world)
	{
		assert(world.IsValid());
		mWorlds.insert({ world.GetName(), &world });
	}

	void GameInstance::RemoveWorld(World& world)
	{
		assert(world.IsValid());
		auto iter = mWorlds.find(world.GetName());
		if (iter != mWorlds.end())
		{
			World* tmp = iter->second;
			mWorlds.erase(iter);
			delete tmp;
		}
	}

	bool GameInstance::IsWorldInGameInstance(World& world)
	{
		assert(world.IsValid());

		return mWorlds.find(world.GetName()) != mWorlds.end();
	}
}