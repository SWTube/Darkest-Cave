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

namespace cave
{
	Level::Level()
		: Object("Level")
		, mOwner(nullptr)
	{

	}

	Level::Level(std::string& name) 
		: Object(name)
		, mOwner(nullptr)
	{

	}

	Level::Level(const char* name)
		: Object(name)
		, mOwner(nullptr)
	{

	}

	Level::~Level()
	{
		assert(IsValid());

		mActiveGameObjects.clear();
		mTaggedGameObjects.clear();
		for (auto iter = mAllGameObjects.begin(); iter != mAllGameObjects.end(); ++iter)
		{
			GameObject* gameObject = iter->second;
			assert(gameObject != nullptr);
			iter->second = nullptr;
			delete gameObject;
		}

		mAllGameObjects.clear();
	}

	void Level::AddGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());
		mAllGameObjects.insert({ gameObject.GetName(), &gameObject });
		addTagGameObject(gameObject);
		if (gameObject.IsActive())
		{
			addActiveGameObject(gameObject);
		}
		gameObject.setLevel(*this);
	}

	void Level::AddGameObjects(std::vector<GameObject*>& gameObjects)
	{
		for (auto& gameObject : gameObjects)
		{
			AddGameObject(*gameObject);
		}
	}

	void Level::RemoveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());
		mGameObjectsToRemove.push_back(&gameObject);
	}

	void Level::RemoveGameObjects(std::vector<GameObject*>& gameObjects)
	{
		for (auto& gameObject : gameObjects)
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
		assert(IsValid());
		assert(name != nullptr);

		auto iter = mAllGameObjects.find(name);

		return iter != mAllGameObjects.end() ? iter->second : nullptr;
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

		auto iter = mTaggedGameObjects.find(tag);

		return iter != mTaggedGameObjects.end() ? iter->second : nullptr;
	}

	GameObject* Level::FindGameObjectByTag(const char* name)
	{
		assert(IsValid() && (name != nullptr));
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);

		auto iter = mTaggedGameObjects.find(tag);

		return iter != mTaggedGameObjects.end() ? iter->second : nullptr;
	}

	std::vector<GameObject*>&& Level::FindGameObjectsByTag(std::string& name)
	{
		assert(IsValid());
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);

		auto range = mTaggedGameObjects.equal_range(tag);
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

		auto range = mTaggedGameObjects.equal_range(tag);
		std::vector<GameObject*> result;
		for (; range.first != range.second; ++range.first)
		{
			result.push_back(range.first->second);
		}

		return std::move(result);
	}

	void Level::InitializeGameObjectsInLevel()
	{
		assert(IsValid());
		for (auto iter = mAllGameObjects.begin(); iter != mAllGameObjects.end(); ++iter)
		{
			(iter->second)->InitializeScripts();
		}
	}
	
	void Level::UpdateGameObjectsInLevel()
	{
		assert(IsValid());

		for (auto iter = mActiveGameObjects.begin(); iter != mActiveGameObjects.end(); ++iter)
		{
			(iter->second)->UpdateScripts();
		}
		destroyGameObjects();
	}

	void Level::FixedUpdateGameObjectsInLevel()
	{
		assert(IsValid());

		for (auto iter = mActiveGameObjects.begin(); iter != mActiveGameObjects.end(); ++iter)
		{
			assert((iter->second)->IsValid());
			(iter->second)->FixedUpdateScripts();
		}
		destroyGameObjects();
	}

	void Level::addActiveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid() & isGameObjectInLevel(gameObject));

		mActiveGameObjects.insert({ gameObject.GetGUID(), &gameObject });
	}

	void Level::removeActiveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid() & isGameObjectInLevel(gameObject));

		auto iter = mActiveGameObjects.find(gameObject.GetGUID());
		
		if (iter != mActiveGameObjects.end())
		{
			mActiveGameObjects.erase(iter);
		}
	}

	void Level::addTagGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid() & isGameObjectInLevel(gameObject));

		mTaggedGameObjects.insert({ gameObject.GetTag(), &gameObject });
	}

	void Level::removeTaggedGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid() & isGameObjectInLevel(gameObject));

		auto range = mTaggedGameObjects.equal_range(gameObject.GetTag());
		for (; range.first != range.second; ++range.first)
		{
			if (*(range.first->second) == gameObject)
			{
				mTaggedGameObjects.erase(range.first);
				break;
			}
		}
	}

	void Level::destroyGameObjects()
	{
		assert(IsValid());

		if (mGameObjectsToRemove.empty())
		{
			return;
		}

		for (size_t index = 0, end = mGameObjectsToRemove.size(); index != end; ++index)
		{
			GameObject* gameObject = mGameObjectsToRemove[index];
			assert(gameObject != nullptr);

			removeActiveGameObject(*gameObject);
			removeTaggedGameObject(*gameObject);

			auto range = mAllGameObjects.equal_range(gameObject->GetName());
			for (; range.first != range.second; ++range.first)
			{
				if (range.first->second == gameObject)
				{
					mAllGameObjects.erase(range.first);
					delete gameObject;
					break;
				}
			}
		}

		mGameObjectsToRemove.clear();
	}

	bool Level::isGameObjectInLevel(GameObject& gameObject)
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

#ifdef CAVE_BUILD_DEBUG
	namespace LevelTest
	{
	}
#endif //CAVE_BUILD_DEBUG
}