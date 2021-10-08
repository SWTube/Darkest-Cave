/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Physics.h"
#include "Object/GameObject.h"
#include "Object/TagPool.h"
#include "Object/Script.h"
#include "Object/Transform.h"
#include "Body/PhysicsBody.h"

namespace cave
{
	std::unordered_set<std::string> GameObject::mGlobalUniqueNames;

	GameObject::GameObject(const char* name)
		: Object(name, mGlobalUniqueNames)
		, mbActive(true)
		, mTag(TagPool::FindTagByName("None"))
		, mTransform(new Transform())
	{
		assert(mTag != nullptr && mTransform != nullptr);
	}

	GameObject::GameObject(std::string& name)
		: Object(name, mGlobalUniqueNames)
		, mbActive(true)
		, mTag(TagPool::FindTagByName("None"))
		, mTransform(new Transform())
	{
		assert(mTag != nullptr && mTransform != nullptr);
	}

	GameObject::GameObject(const std::string& name)
		: Object(name, mGlobalUniqueNames)
		, mbActive(true)
		, mbStatic(false)
		, mTag(TagPool::FindTagByName("None"))
		, mTransform(new Transform())
	{
		assert(mTag != nullptr && mTransform != nullptr);
	}

	GameObject::GameObject(const GameObject& other)
		: Object(other, mGlobalUniqueNames)
		, mbActive(other.mbActive)
		, mTag(other.mTag)
		, mTransform(other.mTransform)
	{
		assert(mTag != nullptr && mTransform != nullptr);
	}

	GameObject::GameObject(GameObject&& other) noexcept
		: Object(std::move(other), mGlobalUniqueNames)
		, mbActive(other.mbActive)
		, mTag(other.mTag)
		, mTransform(other.mTransform)
	{
		assert(mTag != nullptr && mTransform != nullptr);
	}

	GameObject::~GameObject()
	{
		assert(IsValid());
		if (mTransform != nullptr)
		{
			delete mTransform;
		}

		for (auto& iter : mScripts)
		{
			Script* script = iter;
			assert(script != nullptr);
			delete script;
		}
		mScripts.clear();
	}

	GameObject& GameObject::operator=(const GameObject& other)
	{
		return *this;
	}

	GameObject& GameObject::operator=(GameObject&& other) noexcept
	{
		return *this;
	}

	void GameObject::Init()
	{
		assert(IsValid());
		for (auto& script : mScripts)
		{
			assert(script->IsValid());
			script->Init(*this);
		}
	}

	void GameObject::Update(float elapsedTimestep)
	{
		assert(IsValid());
		for (auto& script : mScripts)
		{
			script->Update(*this, elapsedTimestep);
		}
	}

	void GameObject::FixedUpdate(float elapsedTimestep)
	{
		assert(IsValid());
		for (auto& script : mScripts)
		{
			script->FixedUpdate(*this, elapsedTimestep);
		}
	}

	void GameObject::AddScript(Script* script)
	{
		assert(IsValid() && script != nullptr);
		mScripts.push_back(script);
	}

	void GameObject::AddScripts(std::vector<Script*>& scripts)
	{
		for (auto& script : scripts)
		{
			AddScript(script);
		}
	}

	void GameObject::SetTag(const char* name)
	{
		assert(IsValid() && name != nullptr);
		mTag = TagPool::FindTagByName(name);
		assert(mTag != nullptr);
	}

	void GameObject::SetTag(std::string& name)
	{
		assert(IsValid());
		mTag = TagPool::FindTagByName(name);
		assert(mTag != nullptr);
	}

	void GameObject::SetTag(const std::string& name)
	{
		assert(IsValid());
		mTag = TagPool::FindTagByName(name);
		assert(mTag != nullptr);
	}

	Tag* GameObject::GetTag() const
	{
		assert(IsValid() && mTag != nullptr);
		return mTag;
	}

	void GameObject::SetActive(bool state)
	{
		assert(IsValid());
		if (mbActive == state)
		{
			return;
		}

		mbActive = state;
	}

	bool GameObject::IsActive() const
	{
		assert(IsValid());
		return mbActive;
	}

	void GameObject::SetStatic(bool state)
	{
		assert(IsValid());
		if (mbStatic == state)
		{
			return;
		}

		mbStatic = state;
	}

	bool GameObject::IsStatic() const
	{
		assert(IsValid());
		return mbStatic;
	}

	Float2* GameObject::GetPosition() const
	{
		assert(IsValid());
		return mTransform->GetPosition();
	}

	Float2* GameObject::GetRotation() const
	{
		assert(IsValid());
		return mTransform->GetRotation();
	}

	Float2* GameObject::GetScale() const
	{
		assert(IsValid());
		return mTransform->GetScale();
	}

	void GameObject::SetRenderable(Renderable* renderable)
	{
		assert(IsValid() && renderable != nullptr);
		if (mRenderable != nullptr)
		{
			delete mRenderable;
		}
		mRenderable = renderable;
	}

	Renderable* GameObject::GetRenderable() const
	{
		assert(IsValid());
		return mRenderable;
	}

	void GameObject::SetPhysicsBody(PhysicsBody* physicsBody)
	{
		assert(IsValid() && physicsBody != nullptr);
		if (mPhysicsBody != nullptr)
		{
			delete physicsBody;
		}
		mPhysicsBody = physicsBody;
	}

	PhysicsBody* GameObject::GetPhysicsBody() const
	{
		assert(IsValid());
		return mPhysicsBody;
	}
}