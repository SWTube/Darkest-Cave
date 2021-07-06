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
		mTag(nullptr),
		mTransform(),
		mGrid(nullptr)
	{

	}

	GameObject::GameObject(const GameObject& other) :
		mbActive(other.mbActive),
		mbStatic(other.mbStatic),
		mLayer(other.mLayer),
		mTransform()
	{

	}

	GameObject::GameObject(GameObject&& other) noexcept :
		mbActive(other.mbActive),
		mbStatic(other.mbStatic),
		mLayer(other.mLayer),
		mTransform(std::move(other.mTransform))
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
		mTransform = other.mTransform;

		return *this;
	}

	GameObject& GameObject::operator=(GameObject&& other) noexcept
	{
		mbActive = other.mbActive;
		mbStatic = other.mbStatic;
		mLayer = other.mLayer;
		mTransform = std::move(other.mTransform);

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

	void GameObject::RemoveComponent(eComponentType type)
	{
		if (mComponents[type] != nullptr)
		{
			delete mComponents[type];
			mComponents[type] = nullptr;
		}
	}

	GameObject* FindObjectByName(Scene& target, std::string& name)
	{
		return target.FindObjectByName(name);
	}
}