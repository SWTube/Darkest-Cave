/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Assertion/Assert.h"
#include "Object/GameObject.h"
#include "World/Level.h"
#include "World/World.h"

namespace cave
{
	std::unordered_set<std::string> World::mGlobalUniqueName;

	World::World(const char* name) 
		: Object(name, mGlobalUniqueName)
		, mPhysicsWorld(new b2World(b2Vec2{ 0, -10 }))
	{
		assert(IsValid());
	}

	World::World(std::string& name)
		: Object(name, mGlobalUniqueName)
		, mPhysicsWorld(new b2World(b2Vec2{ 0, -10 }))
	{
		assert(IsValid());
	}

	World::World(const std::string& name)
		: Object(name, mGlobalUniqueName)
		, mPhysicsWorld(new b2World(b2Vec2{ 0, -10 }))
	{
		assert(IsValid());
	}

	World::~World()
	{
		assert(IsValid());

		if (mPhysicsWorld != nullptr)
		{
			delete mPhysicsWorld;
		}

		for (auto iter = mLevels.begin(); iter != mLevels.end(); ++iter)
		{
			Level* level = iter->second;
			assert(level != nullptr);
			iter->second = nullptr;
			delete level;
		}
		mLevels.clear();
	}

	void World::AddLevel(const char* name)
	{
		assert(IsValid() && IsInitialized() && name != nullptr);
		Level* level = new Level(name);
		assert(level != nullptr);
		mLevels.insert({ level->GetName(), level });
	}

	void World::AddLevel(std::string& name)
	{
		assert(IsValid() && IsInitialized());
		Level* level = new Level(name);
		assert(level != nullptr);
		mLevels.insert({ level->GetName(), level });
	}

	void World::AddLevel(const std::string& name)
	{
		assert(IsValid() && IsInitialized());
		Level* level = new Level(name);
		assert(level != nullptr);
		mLevels.insert({ level->GetName(), level });
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

	Level* World::FindLevel(const char* name)
	{
		assert(IsValid() && IsInitialized());

		auto iter = mLevels.find(name);
		return iter == mLevels.end() ? nullptr : iter->second;
	}

	Level* World::FindLevel(std::string& name)
	{
		assert(IsValid() && IsInitialized());

		auto iter = mLevels.find(name);
		return iter == mLevels.end() ? nullptr : iter->second;
	}

	Level* World::FindLevel(const std::string& name)
	{
		assert(IsValid() && IsInitialized());

		auto iter = mLevels.find(name);
		return iter == mLevels.end() ? nullptr : iter->second;
	}

	std::unordered_map<std::string, Level*>& World::GetStreamingLevels()
	{
		assert(IsValid() && IsInitialized());
		return mStreamingLevels;
	}

	void World::AddGameObject(const char* name)
	{
		assert(IsValid() && IsInitialized() && name != nullptr);
		GameObject* gameObject = new GameObject(name);
		assert(gameObject != nullptr);
		mAllGameObjects.insert({ gameObject->GetName(), gameObject });

		if (gameObject->IsActive() && !gameObject->IsStatic())
		{
			mActiveGameObjects.insert({ gameObject->GetName(), gameObject });
		}
	}

	void World::AddGameObject(std::string& name)
	{
		assert(IsValid() && IsInitialized());
		GameObject* gameObject = new GameObject(name);
		assert(gameObject != nullptr);
		mAllGameObjects.insert({ gameObject->GetName(), gameObject });

		if (gameObject->IsActive() && !gameObject->IsStatic())
		{
			mActiveGameObjects.insert({ gameObject->GetName(), gameObject });
		}
	}

	void World::AddGameObject(const std::string& name)
	{
		assert(IsValid() && IsInitialized());
		GameObject* gameObject = new GameObject(name);
		assert(gameObject != nullptr);
		mAllGameObjects.insert({ gameObject->GetName(), gameObject });

		if (gameObject->IsActive() && !gameObject->IsStatic())
		{
			mActiveGameObjects.insert({ gameObject->GetName(), gameObject });
		}
	}

	void World::RemoveGameObject(const char* name)
	{
		assert(IsValid() && IsInitialized() && name != nullptr);
		auto iter = mActiveGameObjects.find(name);
		if (iter != mActiveGameObjects.end())
		{
			mActiveGameObjects.erase(iter);
		}

		iter = mAllGameObjects.find(name);
		if (iter != mAllGameObjects.end())
		{
			GameObject* gameObject = iter->second;
			mAllGameObjects.erase(name);
			delete gameObject;
		}
	}

	void World::RemoveGameObject(std::string& name)
	{
		assert(IsValid() && IsInitialized());
		auto iter = mActiveGameObjects.find(name);
		if (iter != mActiveGameObjects.end())
		{
			mActiveGameObjects.erase(iter);
		}

		iter = mAllGameObjects.find(name);
		if (iter != mAllGameObjects.end())
		{
			GameObject* gameObject = iter->second;
			mAllGameObjects.erase(name);
			delete gameObject;
		}
	}

	void World::RemoveGameObject(const std::string& name)
	{
		assert(IsValid() && IsInitialized());
		auto iter = mActiveGameObjects.find(name);
		if (iter != mActiveGameObjects.end())
		{
			mActiveGameObjects.erase(iter);
		}

		iter = mAllGameObjects.find(name);
		if (iter != mAllGameObjects.end())
		{
			GameObject* gameObject = iter->second;
			mAllGameObjects.erase(name);
			delete gameObject;
		}
	}

	GameObject* World::FindGameObject(const char* name)
	{
		assert(IsValid() && IsInitialized() && name != nullptr);

		auto iter = mAllGameObjects.find(name);
		return iter == mAllGameObjects.end() ? nullptr : iter->second;
	}

	GameObject* World::FindGameObject(std::string& name)
	{
		assert(IsValid() && IsInitialized());

		auto iter = mAllGameObjects.find(name);
		return iter == mAllGameObjects.end() ? nullptr : iter->second;
	}

	GameObject* World::FindGameObject(const std::string& name)
	{
		assert(IsValid() && IsInitialized());

		auto iter = mAllGameObjects.find(name);
		return iter == mAllGameObjects.end() ? nullptr : iter->second;
	}

	void World::SetGravity(b2Vec2 gravity)
	{
		assert(IsValid());
		mPhysicsWorld->SetGravity(gravity);
	}

	b2Vec2 World::GetGravity() const
	{
		assert(IsValid());
		return mPhysicsWorld->GetGravity();
	}

	b2World* World::GetPhysicsWorld() const
	{
		assert(IsValid());
		return mPhysicsWorld;
	}

	void World::Init()
	{
		assert(IsValid());
		for (auto iter = mActiveGameObjects.begin(); iter != mActiveGameObjects.end(); ++iter)
		{
			iter->second->Init();
		}
		mbInitialized = true;
	}

	void World::FixedUpdate(float elapsedTimestep)
	{
		assert(IsValid());
		mPhysicsWorld->Step(elapsedTimestep, 10, 8);
		for (auto iter = mActiveGameObjects.begin(); iter != mActiveGameObjects.end(); ++iter)
		{
			iter->second->FixedUpdate(elapsedTimestep);
		}
	}

	void World::Update(float elapsedTimestep)
	{
		assert(IsValid());
		for (auto iter = mActiveGameObjects.begin(); iter != mActiveGameObjects.end(); ++iter)
		{
			iter->second->Update(elapsedTimestep);
		}
	}

	bool World::IsInitialized() const
	{
		return mbInitialized;
	}
}