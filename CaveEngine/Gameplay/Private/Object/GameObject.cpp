/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */


#include "Object/GameObject.h"

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

	}
}