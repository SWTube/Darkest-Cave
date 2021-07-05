/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "Object/Component.h"
#include "Object/Obejct.h"
#include "Tmp/Transform.h"

namespace cave
{
	class Scene;
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
		void AddTag(std::string& tag);

		void RemoveComponent(eComponentType type);
		void RemoveTag(std::string& tag);

		bool CompareTag(std::string& tag) const;

		__forceinline Component* GetComponent(eComponentType type) const
		{
			return mComponents[type];
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

		__forceinline void SetLayer(int layer)
		{
			mLayer = layer;
		}

		__forceinline int GetLayer() const
		{
			return mLayer;
		}

		__forceinline void SetScene(Scene& scene)
		{
			mScene = &scene;
		}

		__forceinline Scene* GetScene() const
		{
			return mScene;
		}

		__forceinline std::unordered_set<std::string>& GetTags()
		{
			return mTags;
		}

		__forceinline Transform* GetTransform()
		{
			return &mTransform;
		}

		__forceinline std::string& GetName()
		{
			return mName;
		}

	private:
		bool mbActive;
		bool mbStatic;

		int mLayer;

		std::vector<Component*> mComponents;

		std::string mName;

		std::unordered_set<std::string> mTags;

		Transform mTransform;
		Scene* mScene;
		Grid* mGrid;
	};

	GameObject* FindObjectByName(Scene& targetScene, std::string& name);
}