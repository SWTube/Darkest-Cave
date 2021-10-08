/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#ifdef CAVE_BUILD_DEBUG
#include <random>
#include <limits>
#include <iostream>
#include "Object/Script.h"
#endif //CAVE_BUILD_DEBUG

#include "CoreGlobals.h"
#include "Assertion/Assert.h"
#include "Object/GameObject.h"
#include "Object/TagPool.h"
#include "World/Level.h"
#include "World/World.h"

namespace cave
{
	std::unordered_set<std::string> Level::mGlobalUniqueNames;

	Level::Level(const char* name)
		: Object(name, mGlobalUniqueNames)
	{

	}

	Level::Level(std::string& name)
		: Object(name, mGlobalUniqueNames)
	{

	}

	Level::Level(const std::string& name)
		: Object(name, mGlobalUniqueNames)
	{

	}

	Level::~Level()
	{
		assert(IsValid());

		mGameObjects.clear();
	}

	void Level::AddGameObject(const char* name)
	{
		assert(IsValid() && name != nullptr && mOwner != nullptr);
		GameObject* gameObject = mOwner->FindGameObject(name);
		assert(gameObject != nullptr);
		mGameObjects.insert({ gameObject->GetName(), gameObject });
	}

	void Level::AddGameObject(std::string& name)
	{
		assert(IsValid() && mOwner != nullptr);
		GameObject* gameObject = mOwner->FindGameObject(name);
		assert(gameObject != nullptr);
		mGameObjects.insert({ gameObject->GetName(), gameObject });
	}

	void Level::AddGameObject(const std::string& name)
	{
		assert(IsValid() && mOwner != nullptr);
		GameObject* gameObject = mOwner->FindGameObject(name);
		assert(gameObject != nullptr);
		mGameObjects.insert({ gameObject->GetName(), gameObject });
	}

	void Level::AddRemoveGameObjectList(const char* name)
	{
		assert(IsValid() && name != nullptr);
		auto iter = mGameObjects.find(name);
		if (iter != mGameObjects.end())
		{
			mRemoveGameObjectList.push_back(iter->second);
		}
	}

	void Level::AddRemoveGameObjectList(std::string& name)
	{
		assert(IsValid());
		auto iter = mGameObjects.find(name);
		if (iter != mGameObjects.end())
		{
			mRemoveGameObjectList.push_back(iter->second);
		}
	}

	void Level::AddRemoveGameObjectList(const std::string& name)
	{
		assert(IsValid());
		auto iter = mGameObjects.find(name);
		if (iter != mGameObjects.end())
		{
			mRemoveGameObjectList.push_back(iter->second);
		}
	}

	void Level::RemoveGameObjects()
	{
		assert(IsValid());
		for (auto& gameObject : mRemoveGameObjectList)
		{
			mGameObjects.erase(gameObject->GetName());
		}
	}

	GameObject* Level::FindGameObjectByName(const char* name)
	{
		assert(IsValid() && name != nullptr);
		auto iter = mGameObjects.find(name);

		return iter != mGameObjects.end() ? iter->second : nullptr;
	}


	GameObject* Level::FindGameObjectByName(std::string& name)
	{
		assert(IsValid());
		auto iter = mGameObjects.find(name);

		return iter != mGameObjects.end() ? iter->second : nullptr;
	}

	GameObject* Level::FindGameObjectByName(const std::string& name)
	{
		assert(IsValid());
		auto iter = mGameObjects.find(name);

		return iter != mGameObjects.end() ? iter->second : nullptr;
	}

	std::vector<GameObject*>&& Level::FindGameObjectsByTag(const char* name)
	{
		assert(IsValid() && name != nullptr);
		
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);

		std::vector<GameObject*> result;
		for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); ++iter)
		{
			if (tag == iter->second->GetTag())
			{
				result.push_back(iter->second);
			}
		}

		return std::move(result);
	}

	std::vector<GameObject*>&& Level::FindGameObjectsByTag(std::string& name)
	{
		assert(IsValid());

		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);

		std::vector<GameObject*> result;
		for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); ++iter)
		{
			if (tag == iter->second->GetTag())
			{
				result.push_back(iter->second);
			}
		}

		return std::move(result);
	}

	std::vector<GameObject*>&& Level::FindGameObjectsByTag(const std::string& name)
	{
		assert(IsValid());

		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);

		std::vector<GameObject*> result;
		for (auto iter = mGameObjects.begin(); iter != mGameObjects.end(); ++iter)
		{
			if (tag == iter->second->GetTag())
			{
				result.push_back(iter->second);
			}
		}

		return std::move(result);
	}

	void Level::SetWorldOwner(World* owner)
	{
		assert(IsValid() && owner != nullptr);
		mOwner = owner;
	}

	World* Level::GetWorldOwner() const
	{
		assert(IsValid() && mOwner != nullptr);
		return mOwner;
	}
}