/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "CoreGlobals.h"
#include "Game/GameInstance.h"
#include "Assertion/Assert.h"
#include "World/World.h"
#include "Object/TagPool.h"

namespace cave
{
	GameInstance::GameInstance()
	{

	}

	GameInstance::~GameInstance()
	{
		Shutdown();
	}

	void GameInstance::Init()
	{
		TagPool::Init();

		for (auto iter = mWorlds.begin(); iter != mWorlds.end(); ++iter)
		{
			iter->second->Init();
		}
		mbInitialized = true;
	}

	void GameInstance::FixedUpdate(float elapsedTimestep)
	{
		assert(IsInitialized());
		mCurrentWorld->FixedUpdate(elapsedTimestep);
	}

	void GameInstance::Update(float elapsedTimestep)
	{
		assert(IsInitialized());
		mCurrentWorld->Update(elapsedTimestep);
	}

	void GameInstance::Shutdown()
	{
		assert(IsInitialized());
		for (auto iter = mWorlds.begin(); iter != mWorlds.end(); ++iter)
		{
			World* world = iter->second;
			assert(world != nullptr);
			iter->second = nullptr;
			world->~World();
			gCoreMemoryPool.Deallocate(world, sizeof(*world));
		}

		mWorlds.clear();

		TagPool::ShutDown();
	}

	void GameInstance::AddWorld(const char* name)
	{
		assert(name != nullptr && IsInitialized());
		World* world = reinterpret_cast<World*>(gCoreMemoryPool.Allocate(sizeof(World)));
		new(world) World(name);
		assert(world != nullptr);
		mWorlds.insert({ world->GetName(), world });
	}

	void GameInstance::AddWorld(std::string& name)
	{
		AddWorld(name.c_str());
	}

	void GameInstance::AddWorld(const std::string& name)
	{
		AddWorld(name.c_str());
	}

	void GameInstance::RemoveWorld(const char* name)
	{
		assert(IsInitialized() && name != nullptr);
		auto iter = mWorlds.find(name);
		if (iter != mWorlds.end())
		{
			World* tmp = iter->second;
			mWorlds.erase(iter);
			tmp->~World();
			gCoreMemoryPool.Deallocate(tmp, sizeof(*tmp));
		}
	}

	void GameInstance::RemoveWorld(std::string& name)
	{
		RemoveWorld(name.c_str());
	}

	void GameInstance::RemoveWorld(const std::string& name)
	{
		RemoveWorld(name.c_str());
	}

	World* GameInstance::FindWorld(const char* name)
	{
		assert(IsInitialized() && name != nullptr);
		auto iter = mWorlds.find(name);
		return iter == mWorlds.end() ? nullptr : iter->second;
	}

	World* GameInstance::FindWorld(std::string& name)
	{
		return FindWorld(name.c_str());
	}

	World* GameInstance::FindWorld(const std::string& name)
	{
		return FindWorld(name.c_str());
	}

	void GameInstance::SetCurrentWorld(const char* name)
	{
		assert(IsInitialized() && name != nullptr);
		auto iter = mWorlds.find(name);
		assert(iter != mWorlds.end());
		mCurrentWorld = iter->second;
	}

	void GameInstance::SetCurrentWorld(std::string& name)
	{
		SetCurrentWorld(name.c_str());
	}

	void GameInstance::SetCurrentWorld(const std::string& name)
	{
		SetCurrentWorld(name.c_str());
	}

	World* GameInstance::GetCurrentWorld() const
	{
		return mCurrentWorld;
	}

	bool GameInstance::IsInitialized() const
	{
		return mbInitialized;
	}
}