/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include <cassert>

#include "Object/GameObject.h"
#include "Scene/Scene.h"

namespace cave
{
	GameObject::GameObject() :
		mbActive(true),
		mbStatic(false),
		mLayer(0),
		mTags(),
		mTransform(),
		mScene(nullptr)
	{

	}

	GameObject::GameObject(const GameObject& other) :
		mbActive(other.mbActive),
		mbStatic(other.mbStatic),
		mLayer(other.mLayer),
		mTags(other.mTags),
		mTransform(),
		mScene(other.mScene)
	{

	}

	GameObject::GameObject(GameObject&& other) noexcept :
		mbActive(other.mbActive),
		mbStatic(other.mbStatic),
		mLayer(other.mLayer),
		mTags(std::move(other.mTags)),
		mTransform(std::move(other.mTransform)),
		mScene(other.mScene)
	{

	}


	GameObject::~GameObject()
	{

	}

	GameObject& GameObject::operator=(const GameObject& other)
	{
		mbActive = other.mbActive;
		mbStatic = other.mbStatic;
		mLayer = other.mLayer;
		mTags = other.mTags;
		mTransform = other.mTransform;
		mScene = other.mScene;

		return *this;
	}

	GameObject& GameObject::operator=(GameObject&& other) noexcept
	{
		mbActive = other.mbActive;
		mbStatic = other.mbStatic;
		mLayer = other.mLayer;
		mTags = std::move(other.mTags);
		mTransform = std::move(other.mTransform);
		mScene = other.mScene;

		return *this;
	}

	void GameObject::AddComponent(Component& component)
	{
		assert(component.IsValid());
		eComponentType type = component.GetComponentType();
		if (mComponents[type] == nullptr)
		{
			mComponents[type] = &component;
		}
	}

	void GameObject::AddTag(std::string& tag)
	{
		mTags.insert(tag);
	}

	void GameObject::RemoveComponent(eComponentType type)
	{
		if (mComponents[type] != nullptr)
		{
			delete mComponents[type];
			mComponents[type] = nullptr;
		}
	}

	void GameObject::RemoveTag(std::string& tag)
	{
		mTags.erase(tag);
	}

	bool GameObject::CompareTag(std::string& tag) const
	{
		return mTags.contains(tag);
	}

	GameObject* FindObjectByName(Scene& target, std::string& name)
	{
		return target.FindObjectByName(name);
	}
}