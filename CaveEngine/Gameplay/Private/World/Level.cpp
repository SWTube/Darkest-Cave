/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "CoreGlobals.h"
#include "World/Level.h"
#include "Assertion/Assert.h"
#include "Object/GameObject.h"
#include "Object/TagPool.h"

namespace cave
{
	Level::Level()
		: Object("Level")
		, mMap(nullptr)
	{

	}

	Level::Level(std::string& name) 
		: Object(name)
		, mMap(nullptr)
	{

	}

	Level::Level(const char* name)
		: Object(name)
		, mMap(nullptr)
	{

	}

	Level::~Level()
	{
		if (mMap != nullptr)
		{
			delete mMap;
		}
	}

	void Level::AddGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());
		mAllGameObjects.insert({ gameObject.GetName(), &gameObject });
		addTaggedGameObject(gameObject);
		if (gameObject.IsActive())
		{
			addActiveGameObject(gameObject);
		}
	}

	void Level::AddGameObjects(std::vector<GameObject*>& gameObjects)
	{
		for (auto gameObject : gameObjects)
		{
			AddGameObject(*gameObject);
		}
	}

	void Level::RemoveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());

		if (gameObject.IsActive())
		{
			removeActiveGameObject(gameObject);
		}
		
		removeTaggedGameObject(gameObject);

		auto range = mAllGameObjects.equal_range(gameObject.GetName());
		for (; range.first != range.second; ++range.first)
		{
			if (range.first->second == &gameObject)
			{
				mAllGameObjects.erase(range.first);
				gCoreMemoryPool.Deallocate(range.first->second, sizeof(GameObject));
			}
		}
	}

	void Level::RemoveGameObjects(std::vector<GameObject*>& gameObjects)
	{
		for (auto gameObject : gameObjects)
		{
			RemoveGameObject(*gameObject);
		}
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

	std::vector<GameObject*>&& Level::FindGameObjectsByName(const char* name)
	{
		assert(IsValid() && (name != nullptr));
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
		assert(IsValid());
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);

		auto iter = mTagGameObjects.find(tag);

		return iter != mTagGameObjects.end() ? iter->second : nullptr;
	}

	GameObject* Level::FindGameObjectByTag(const char* name)
	{
		assert(IsValid() && (name != nullptr));
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);

		auto iter = mTagGameObjects.find(tag);

		return iter != mTagGameObjects.end() ? iter->second : nullptr;
	}

	std::vector<GameObject*>&& Level::FindGameObjectsByTag(std::string& name)
	{
		assert(IsValid());
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);

		auto range = mTagGameObjects.equal_range(tag);
		std::vector<GameObject*> result;
		for (; range.first != range.second; ++range.first)
		{
			result.push_back(range.first->second);
		}
		
		return std::move(result);
	}

	std::vector<GameObject*>&& Level::FindGameObjectsByTag(const char* name)
	{
		assert(IsValid() && (name != nullptr));
		
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);

		auto range = mTagGameObjects.equal_range(tag);
		std::vector<GameObject*> result;
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
			assert((iter->second)->IsValid());
			(iter->second)->UpdateScripts();
		}
	}

	void Level::UpdateAllGameObjectInLevel()
	{
		assert(IsValid());
		for (auto iter = mAllGameObjects.begin(); iter != mAllGameObjects.end(); ++iter)
		{
			assert((iter->second)->IsValid());
			(iter->second)->UpdateScripts();
		}
	}

	void Level::addActiveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());
		assert(findGameObject(gameObject));

		mActiveGameObjects.insert({ gameObject.GetName(), &gameObject });
	}

	void Level::removeActiveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());

		auto range = mActiveGameObjects.equal_range(gameObject.GetName());
		for (; range.first != range.second; ++range.first)
		{
			if (range.first->second == &gameObject)
			{
				mActiveGameObjects.erase(range.first);
			}
		}
	}

	void Level::addTaggedGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());
		assert(findGameObject(gameObject));

		mTagGameObjects.insert({ gameObject.GetTag(), &gameObject });
	}

	void Level::removeTaggedGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());

		auto range = mTagGameObjects.equal_range(gameObject.GetTag());
		for (; range.first != range.second; ++range.first)
		{
			if (range.first->second == &gameObject)
			{
				mTagGameObjects.erase(range.first);
			}
		}
	}

	bool Level::findGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());

		auto range = mAllGameObjects.equal_range(gameObject.GetName());
		for (; range.first != range.second; ++range.first)
		{
			if (range.first->second == &gameObject)
			{
				return true;
			}
		}

		return false;
	}
}