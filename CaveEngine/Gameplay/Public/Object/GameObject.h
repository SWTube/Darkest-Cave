/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <unordered_map>

#include "Object/Component.h"
#include "Object/Obejct.h"
#include "Tmp/Transform.h"

namespace cave
{
	class Scene;
	class Tag;
	class Transform;
	class Grid;

	class GameObject : public Object
	{
	public:
		GameObject();
		GameObject(const GameObject& gameObject);
		GameObject(GameObject&& gameObject) noexcept;

		virtual ~GameObject();
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other) noexcept;

		void AddComponent(Component& component);
		void RemoveComponent(eComponentType type);
		
		__forceinline void SetTag(Tag& tag)
		{
			mTag = &tag;
		}

		__forceinline Tag* GetTag() const
		{
			return mTag;
		}

		__forceinline Component* GetComponent(eComponentType type) const
		{
			return mComponents.find(type)->second;
		}

		__forceinline void SetActive(bool state)
		{
			mbActive = state;
		}

		__forceinline void SetStatic(bool state)
		{
			mbStatic = state;
		}

		__forceinline bool IsActive() const
		{
			return mbActive;
		}

		__forceinline bool IsStatic() const
		{
			return mbStatic;
		}

		__forceinline void SetLayer(unsigned char layer)
		{
			mLayer = layer;
		}

		__forceinline int GetLayer() const
		{
			return mLayer;
		}

		
		__forceinline void SetName(std::string& name)
		{
			mName = std::move(name);
		}

		__forceinline std::string& GetName()
		{
			return mName;
		}

		__forceinline void SetGrid(Grid& grid)
		{
			mGrid = &grid;
		}

		__forceinline Grid* GetGrid() const
		{
			return mGrid;
		}

		__forceinline Transform* GetTransform()
		{
			return &mTransform;
		}

	private:
		bool mbActive;
		bool mbStatic;

		unsigned char mLayer;

		std::unordered_map<size_t, Component*> mComponents;

		std::string mName;
		Tag* mTag;

		Transform mTransform;
		Grid* mGrid;
	};

	GameObject* FindObjectByName(Scene& targetScene, std::string& name);
}