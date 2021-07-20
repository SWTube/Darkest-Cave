/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <cassert>

#include "Object/GameObject.h"
#include "Object/TagPool.h"
#include "Object/Script.h"
#include "Object/Transform.h"
#include "World/Level.h"

namespace cave
{
	GameObject::GameObject(std::string& name, bool isControlled)
		: mbActive(true)
		, mbStatic(false)
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
		assert(mTag != nullptr);
	}

	GameObject::GameObject(const char* name, bool isControlled)
		: mbActive(true)
		, mbStatic(false)
		, mbControlled(isControlled)
		, mLayer(0)
		, mScripts()
		, mTag(TagPool::FindTagByName("None"))
		, mTransform(nullptr)
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(nullptr)
		, mLevel(nullptr)
	{
		assert(mTag != nullptr);
	}

	GameObject::GameObject(const GameObject& other)
		: Object(other)
		, mbActive(other.IsActive())
		, mbStatic(other.IsStatic())
		, mbControlled(other.IsControlled())
		, mLayer(other.GetLayer())
		, mScripts(other.mScripts)
		, mTag(other.GetTag())
		, mTransform(nullptr)
		, mRenderer(nullptr)
		, mPhysics(nullptr)
		, mController(other.GetController())
		, mLevel(other.GetLevel())
	{

	}

	GameObject::GameObject(GameObject&& other) noexcept
		: Object(std::move(other))
		, mbActive(other.IsActive())
		, mbStatic(other.IsStatic())
		, mbControlled(other.IsControlled())
		, mLayer(other.GetLayer())
		, mScripts(other.mScripts)
		, mTag(other.GetTag())
		, mTransform(other.GetTransform())
		, mRenderer(other.GetRenderer())
		, mPhysics(other.Get)
		, mController(other.GetController())
		, mLevel(other.GetLevel())
	{
		other.mController = nullptr;
	}

	GameObject::~GameObject()
	{

	}

	GameObject& GameObject::operator=(const GameObject& other)
	{
		Object::operator=(other);

		return *this;
	}

	GameObject& GameObject::operator=(GameObject&& other) noexcept
	{
		Object::operator=(std::move(other));

		return *this;
	}

	void GameObject::UpdateScripts()
	{
		assert(IsValid());
		for (auto& iter : mScripts)
		{
			iter.second->Update(*this);
		}
	}

	void GameObject::FixedUpdateScripts()
	{
		assert(IsValid());
		for (auto& iter : mScripts)
		{
			iter.second->FixedUpdate(*this);
		}
	}

	void GameObject::AddScript(Script& script)
	{
		assert(IsValid() & script.IsValid());
		mScripts.insert({ script.GetName(), &script });
	}

	void GameObject::AddScripts(std::vector<Script*>& scripts)
	{
		for (auto element : scripts)
		{
			AddScript(*element);
		}
	}

	void GameObject::RemoveScript(std::string& name)
	{
		RemoveScript(name.c_str());
	}

	void GameObject::RemoveScript(const char* name)
	{
		assert(IsValid());
		assert(name != nullptr);

		auto iter = mScripts.find(name);
		if (iter != mScripts.end())
		{
			mScripts.erase(name);
		}
	}

	void GameObject::RemoveScripts(std::vector<std::string>& names)
	{
		for (auto& name : names)
		{
			RemoveScript(name.c_str());
		}
	}

	void GameObject::RemoveScripts(std::vector<const char*>& names)
	{
		for (auto name : names)
		{
			RemoveScript(name);
		}
	}

	Script* GameObject::FindScriptByName(std::string& name)
	{
		Script* script = FindScriptByName(name.c_str());
		return script;
	}

	Script* GameObject::FindScriptByName(const char* name)
	{
		assert(IsValid());
		assert(name != name);

		auto iter = mScripts.find(name);

		return iter != mScripts.end() ? iter->second : nullptr;
	}

	void GameObject::SetTag(std::string& name)
	{
		SetTag(name.c_str());
	}

	void GameObject::SetTag(const char* name)
	{
		assert(IsValid());
		assert(name != nullptr);
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);
		mTag = tag;
	}

	void GameObject::SetActive(bool state)
	{
		assert(IsValid());
		mbActive = state;
		if ((!mbActive) & (mLevel != nullptr))
		{
			mLevel->removeActiveGameObject(*this);
			return;
		}
		mLevel->addActiveGameObject(*this);
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
		assert(IsValid());
		assert(IsControlled());
		if (mController != nullptr)
		{
			delete mController;
		}
		mController = &controller;
	}

	void GameObject::RemoveGameObjectInLevel()
	{
		assert(IsValid());
		assert(mLevel != nullptr);
		mLevel->RemoveGameObject(*this);
	}
}