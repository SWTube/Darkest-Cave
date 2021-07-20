/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "World/Level.h"
#include "Assertion/Assert.h"
#include "Object/GameObject.h"

namespace cave
{
	Level::Level(std::string& name) 
		: Object(name)
		, mMap(nullptr)
		, mWorld(nullptr)
	{

	}

	Level::Level(const char* name)
		: Object(name)
		, mMap(nullptr)
		, mWorld(nullptr)
	{

	}

	Level::~Level()
	{

	}

	void Level::AddGameObject(GameObject& gameObject)
	{
		assert(IsValid());
		mAllGameObjects.insert({ gameObject.GetName(), &gameObject });
		if (!gameObject.IsActive())
		{
			return;
		}
		mActiveGameObjects.insert({ gameObject.GetName(), &gameObject });
	}

	void Level::AddGameObjects(std::vector<GameObject*>& gameObjects)
	{
		assert(IsValid());
		for (auto iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
		{
			mAllGameObjects.insert({ (*iter)->GetName(), *iter });
			if (!(*iter)->IsActive())
			{
				return;
			}
			mActiveGameObjects.insert({ (*iter)->GetName(), *iter });
		}
	}

	void Level::RemoveGameObject(std::string& name)
	{

	}

	GameObject* Level::FindGameObjectByName(std::string& name)
	{
		assert(IsValid());
		auto iter = mAllGameObjects.find(name);

		return iter != mAllGameObjects.end() ? iter->second : nullptr;
	}

	GameObject* Level::FindGameObjectByName(const char* name)
	{
		assert(IsValid() && name != nullptr);
		auto iter = mAllGameObjects.find(name);

		return iter != mActiveGameObjects.end() ? iter->second : nullptr;
	}

	std::vector<GameObject*>&& Level::FindGameObjectsByName(std::string& name)
	{
		assert(IsValid());
		std::vector<GameObject*> result;
		auto range = mAllGameObjects.equal_range(name);
		for (; range.first != range.second; ++range.first)
		{
			result.push_back(range.first->second);
		}

		return std::move(result);
	}

	GameObject* Level::FindGameObjectByTag(std::string& name)
	{

	}

	GameObject* Level::FindGameObjectByTag(const char* name)
	{

	}

	std::vector<GameObject*>&& Level::FindGameObjectsByTag(std::string& name)
	{

	}

	std::vector<GameObject*>&& Level::FindGameObjectsByTag(const char* name)
	{

	}

	std::vector<GameObject*>&& Level::FindGameObjectsByName(const char* name)
	{
		assert(IsValid());
		assert(name != nullptr);
		std::vector<GameObject*> result;
		auto range = mAllGameObjects.equal_range(name);
		for (; range.first != range.second; ++range.first)
		{
			result.push_back(range.first->second);
		}

		return std::move(result);
	}
	
	void Level::UpdateGameObjectInLevel()
	{
		assert(IsValid());
		for (auto iter = mActiveGameObjects.begin(); iter != mActiveGameObjects.end(); ++iter)
		{
			(iter->second)->UpdateScripts();
		}
	}

	void Level::UpdateAllGameObjectInLevel()
	{
		assert(IsValid());
		for (auto iter = mAllGameObjects.begin(); iter != mAllGameObjects.end(); ++iter)
		{
			(iter->second)->UpdateScripts();
		}
	}
}