/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#ifdef CAVE_BUILD_DEBUG
#include <iostream>
#include <random>
#include <limits>
#include "Object/Tag.h"
#endif //CAVE_BUILD_DEBUG

#include "Engine.h"
#include "Object/GameObject.h"
#include "Object/TagPool.h"
#include "Object/Script.h"
#include "Object/Transform.h"
#include "World/Level.h"

namespace cave
{
	GameObject::GameObject(bool isControlled)
		: Object()
		, mbActive(true)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(TagPool::FindTagByName("None"))
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(std::string& name, bool isControlled)
		: Object(name)
		, mbActive(true)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(TagPool::FindTagByName("None"))
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(const char* name, bool isControlled)
		: Object(name)
		, mbActive(true)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(TagPool::FindTagByName("None"))
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(std::string& name, std::string& tag, bool isControlled)
		: Object(name)
		, mbActive(true)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(TagPool::FindTagByName(tag))
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(std::string& name, const char* tag, bool isControlled)
		: Object(name)
		, mbActive(true)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(TagPool::FindTagByName(tag))
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(std::string& name, Tag& tag, bool isControlled)
		: Object(name)
		, mbActive(true)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(&tag)
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(const char* name, std::string& tag, bool isControlled)
		: Object(name)
		, mbActive(true)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(TagPool::FindTagByName(tag))
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(const char* name, const char* tag, bool isControlled)
		: Object(name)
		, mbActive(true)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(TagPool::FindTagByName(tag))
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(const char* name, Tag& tag, bool isControlled)
		: Object(name)
		, mbActive(true)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(&tag)
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(const GameObject& other)
		: Object(other)
		, mbActive(other.IsActive())
		, mbControlled(other.IsControlled())
		, mLayer(other.GetLayer())
		, mScripts(other.mScripts)
		, mTag(other.GetTag())
		, mTransform(new Transform())
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(other.GetController())
		, mLevel(other.GetLevel())
	{
		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::GameObject(GameObject&& other) noexcept
		: Object(std::move(other))
		, mbActive(other.IsActive())
		, mbControlled(other.IsControlled())
		, mLayer(other.GetLayer())
		, mScripts(std::move(other.mScripts))
		, mTag(other.GetTag())
		, mTransform(other.GetTransform())
		, mRenderer(other.GetRenderer())
		, mPhysics(other.GetPhysics())
		, mController(other.GetController())
		, mLevel(other.GetLevel())
	{
		other.mTransform = nullptr;
		other.mRenderer = nullptr;
		other.mPhysics = nullptr;
		other.mController = nullptr;
		other.RemoveGameObjectInLevel();

		assert((mTag != nullptr) & (mTransform != nullptr));
	}

	GameObject::~GameObject()
	{
		assert(IsValid());
		if (mTransform != nullptr)
		{
			delete mTransform;
		}

		if (mController != nullptr)
		{
			delete mController;
		}
	}

	void GameObject::UpdateScripts()
	{
		assert(IsValid());
		for (auto& script : mScripts)
		{
			script.second->Update(*this);
		}
	}

	void GameObject::FixedUpdateScripts()
	{
		assert(IsValid());
		for (auto& script : mScripts)
		{
			script.second->FixedUpdate(*this);
		}
	}

	void GameObject::AddScript(Script& script)
	{
		assert(IsValid() & script.IsValid());
		mScripts.insert({ script.GetName(), &script });
	}

	void GameObject::AddScripts(std::vector<Script*>& scripts)
	{
		for (auto& script : scripts)
		{
			AddScript(*script);
		}
	}

	void GameObject::RemoveScript(std::string& name)
	{
		assert(IsValid());

		auto iter = mScripts.find(name);
		if (iter != mScripts.end())
		{
			mScripts.erase(iter);
		}
	}

	void GameObject::RemoveScript(const char* name)
	{
		assert(IsValid());
		assert(name != nullptr);

		auto iter = mScripts.find(name);
		if (iter != mScripts.end())
		{
			mScripts.erase(iter);
		}
	}

	void GameObject::RemoveScripts(std::vector<std::string>& names)
	{
		for (auto& name : names)
		{
			RemoveScript(name);
		}
	}

	void GameObject::RemoveScripts(std::vector<const char*>& names)
	{
		for (auto& name : names)
		{
			RemoveScript(name);
		}
	}

	Script* GameObject::FindScriptByName(std::string& name)
	{
		assert(IsValid());

		auto iter = mScripts.find(name);

		return iter != mScripts.end() ? iter->second : nullptr;
	}

	Script* GameObject::FindScriptByName(const char* name)
	{
		assert(IsValid());
		assert(name != nullptr);

		auto iter = mScripts.find(name);

		return iter != mScripts.end() ? iter->second : nullptr;
	}

	void GameObject::SetActive(bool state)
	{
		assert(IsValid());
		mbActive = state;
		if (mLevel != nullptr)
		{
			if (!mbActive)
			{
				mLevel->removeActiveGameObject(*this);
				return;
			}
			mLevel->addActiveGameObject(*this);
		}
	}

	void GameObject::SetTransform(Transform& transform)
	{
		assert(IsValid());
		if (mTransform != nullptr)
		{
			delete mTransform;
		}
		mTransform = &transform;
	}

	void GameObject::SetRenderer(Renderer& renderer)
	{
		assert(IsValid());
		if (mRenderer != nullptr)
		{
			delete mRenderer;
		}
		mRenderer = &renderer;
	}

	void GameObject::SetPhysics(Physics& physics)
	{
		assert(IsValid());
		if (mPhysics != nullptr)
		{
			delete mPhysics;
		}
		mPhysics = &physics;
	}

	void GameObject::SetController(Controller& controller)
	{
		assert(IsValid() & IsControlled());
		if (mController != nullptr)
		{
			delete mController;
		}
		mController = &controller;
	}

	void GameObject::SetLevel(Level& level)
	{
		assert(IsValid() & level.IsValid());
		mLevel = &level;
	}

	void GameObject::RemoveGameObjectInLevel()
	{
		assert(IsValid());
		assert(mLevel != nullptr);
		mLevel->RemoveGameObject(*this);
	}

#ifdef CAVE_BUILD_DEBUG
	namespace GameObjectTest
	{
		void Test()
		{
			TagPool::Init();

			const char* testString = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

			std::vector<std::string> vecString;
			std::vector<char*> vecConstChar;
			std::vector<GameObject*> gameObjects;

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> disIndex(1, 40);
			std::uniform_int_distribution<int> disStr(0, 61);

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

				vecConstChar.push_back(str);
			}

			TagPool::AddTag("Monster");
			Tag* tag = TagPool::FindTagByName("Monster");

			for (auto& element : vecConstChar)
			{
				GameObject* gameObject = new GameObject(element, *tag);
				gameObjects.push_back(gameObject);
			}

			Script* script = new Script("Move");

			for (auto& element : gameObjects)
			{
				std::cout << element->GetName() << std::endl;
				assert((*(element->GetTag())) == "Monster");
				assert(element->IsActive());
				element->SetActive(false);
				assert(!element->IsActive());
				assert(element->GetLayer() == 0);
				element->SetLayer(12);
				assert(element->GetLayer() == 12);
				assert(element->GetTransform() != nullptr);
				assert(element->GetLevel() == nullptr);
				assert(element->GetPhysics() == nullptr);
				assert(element->GetRenderer() == nullptr);
				assert(!element->IsControlled());
				assert(element->GetController() == nullptr);
				assert(element->FindScriptByName("Move") == nullptr);
				element->AddScript(*script);
				assert(element->FindScriptByName("Move") != nullptr);
				element->RemoveScript("Move");
				assert(element->FindScriptByName("Move") == nullptr);
			}

			for (auto& element : gameObjects)
			{
				delete element;
			}

			for (auto& element : vecConstChar)
			{
				delete element;
			}

			TagPool::ShutDown();
		}
	}
#endif //CAVE_BUILD_DEBUG
}