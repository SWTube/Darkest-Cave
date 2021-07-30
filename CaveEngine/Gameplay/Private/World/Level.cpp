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
#include "World/Level.h"
#include "Assertion/Assert.h"
#include "Object/GameObject.h"
#include "Object/TagPool.h"

namespace cave
{
	Level::Level()
		: Object("Level")
		, mMap(nullptr)
		, mRenderer(nullptr)
	{

	}

	Level::Level(std::string& name) 
		: Object(name)
		, mMap(nullptr)
		, mRenderer(nullptr)
	{

	}

	Level::Level(const char* name)
		: Object(name)
		, mMap(nullptr)
		, mRenderer(nullptr)
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

	void Level::DefferedRemoveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());
		mDeferredRemoveGameObjects.push_back(&gameObject);
	}

	void Level::DefferedRemoveGameObjects(std::vector<GameObject*>& gameObjects)
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

	void Level::InitializeGameObjectsInLevel()
	{
		assert(IsValid());
		for (auto iter = mAllGameObjects.begin(); iter != mAllGameObjects.end(); ++iter)
		{
			(iter->second)->SetRenderer(*mRenderer);
			(iter->second)->Init();
		}
	}
	
	void Level::UpdateGameObjectsInLevel()
	{
		assert(IsValid());
		for (auto iter = mActiveGameObjects.begin(); iter != mActiveGameObjects.end(); ++iter)
		{
			(iter->second)->UpdateScripts();
		}
		removeGameObjects();
	}

	void Level::FixedUpdateGameObjectsInLevel()
	{
		assert(IsValid());
		for (auto iter = mActiveGameObjects.begin(); iter != mActiveGameObjects.end(); ++iter)
		{
			assert((iter->second)->IsValid());
			(iter->second)->FixedUpdateScripts();
		}
		removeGameObjects();
	}

	void Level::addActiveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid() & findGameObject(gameObject));

		mActiveGameObjects.insert({ gameObject.GetName(), &gameObject });
	}

	void Level::removeActiveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid() & findActiveGameObject(gameObject));

		auto iter = mActiveGameObjects.find(gameObject.GetGUID());
		if()
		
	}

	void Level::addTagGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid() & findGameObject(gameObject));

		mTagGameObjects.insert({ gameObject.GetTag(), &gameObject });
	}

	void Level::removeTagGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid() & findGameObject(gameObject));

		auto range = mTagGameObjects.equal_range(gameObject.GetTag());
		for (; range.first != range.second; ++range.first)
		{
			if (range.first->second == &gameObject)
			{
				mTagGameObjects.erase(range.first);
				break;
			}
		}
	}

	void Level::removeGameObjects()
	{
		assert(IsValid());

		if (mDeferredRemoveGameObjects.empty())
		{
			return;
		}

		for (size_t index = 0, end = mDeferredRemoveGameObjects.size(); index != end; ++index)
		{
			GameObject* gameObject = mDeferredRemoveGameObjects[index];

			if (findActiveGameObject(*gameObject))
			{
				removeActiveGameObject(*gameObject);
			}

			removeTagGameObject(*gameObject);

			auto range = mAllGameObjects.equal_range(gameObject->GetName());
			for (; range.first != range.second; ++range.first)
			{
				if (range.first->second == gameObject)
				{
					mAllGameObjects.erase(range.first);
					//gCoreMemoryPool.Deallocate(range.first->second, sizeof(GameObject));
					break;
				}
			}
		}

		mDeferredRemoveGameObjects.clear();
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

	bool Level::findActiveGameObject(GameObject& gameObject)
	{
		assert(IsValid() & gameObject.IsValid());

		auto iter = mActiveGameObjects.find(gameObject.GetGUID());
		if(iter != mActiveGameObjects.end())
		{
			return true;
		}

		return false;
	}

#ifdef CAVE_BUILD_DEBUG
	void Level::PrintGameObjects()
	{
		for (auto iter = mAllGameObjects.begin(); iter != mAllGameObjects.end(); ++iter)
		{
			std::cout << (iter->second)->GetName() << std::endl;
		}

		for (auto iter = mActiveGameObjects.begin(); iter != mActiveGameObjects.end(); ++iter)
		{
			std::cout << (iter->second)->GetName() << std::endl;
		}

		for (auto iter = mTagGameObjects.begin(); iter != mTagGameObjects.end(); ++iter)
		{
			std::cout << (iter->second)->GetName() << std::endl;
		}
	}

	namespace LevelTest
	{
		void Test()
		{
			TagPool::Init();

			const char* testString = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

			std::vector<char*> names;
			std::vector<char*> tags;
			std::vector<GameObject*> gameObjects;

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> disIndex(1, 30);
			std::uniform_int_distribution<int> disStr(0, 61);
			std::uniform_int_distribution<int> disTag(0, 19);

			for (size_t i = 0; i < 100; ++i)
			{
				int index = disIndex(gen);
				char* str = new char[index + 1];
				for (int j = 0; j < index; ++j)
				{
					str[j] = testString[disStr(gen)];
				}
				str[index] = '\0';
				std::cout << "word: " << str << std::endl;

				names.push_back(str);
			}

			Level* level = new Level(names[0]);

			for (size_t i = 0; i < 20; ++i)
			{
				int index = disIndex(gen);
				char* str = new char[index + 1];
				for (int j = 0; j < index; ++j)
				{
					str[j] = testString[disStr(gen)];
				}
				str[index] = '\0';

				tags.push_back(str);
			}

			for (auto& element : tags)
			{
				TagPool::AddTag(element);
			}

			for (auto& element : names)
			{
				GameObject* gameObject = new(gCoreMemoryPool.Allocate(sizeof(GameObject))) GameObject(element, *TagPool::FindTagByName(tags[disTag(gen)]));
				gameObjects.push_back(gameObject);
				level->AddGameObject(*gameObject);
			}

			for (auto& element : gameObjects)
			{
				assert(level->FindGameObjectByName(element->GetName().c_str()) != nullptr);
			}

			level->UpdateGameObjectsInLevel();
			level->UpdateAllGameObjectsInLevel();
			level->FixedUpdateGameObjectsInLevel();
			level->FixedUpdateAllGameObjectsInLevel();

			for (auto& element : gameObjects)
			{
				level->RemoveGameObject(*element);
			}

			for (auto& element : gameObjects)
			{
				assert(level->FindGameObjectByName(element->GetName().c_str()) == nullptr);
			}

			for (auto& element : gameObjects)
			{
				delete element;
			}

			for (auto& element : names)
			{
				delete element;
			}

			for (auto& element : tags)
			{
				delete element;
			}
			TagPool::ShutDown();
		}

		Level* CreateTmpLevel()
		{
			TagPool::Init();

			Level* level = new Level("Level_1");

			GameObject* lapland = new GameObject("lapland");
			GameObject* amiya = new GameObject("amiya");
			GameObject* texas = new GameObject("texas");

			TestScript* lapland_script = new TestScript("lapland_script", 0, 0, 0.05f);
			TestScript* amiya_script = new TestScript("amiya_script", 1, 2, 0.03f);
			TestScript* texas_script = new TestScript("texas_script", 2, 4, 0.01f);

			lapland->AddScript(*lapland_script);
			amiya->AddScript(*amiya_script);
			texas->AddScript(*texas_script);

			level->AddGameObject(*lapland);
			level->AddGameObject(*amiya);
			level->AddGameObject(*texas);

			level->PrintGameObjects();

			return level;
		}
	}
#endif //CAVE_BUILD_DEBUG
}