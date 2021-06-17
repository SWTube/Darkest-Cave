/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include <unordered_set>

#include "Object/Component.h"
#include "Object/Obejct.h"
#include "Tmp/Transform.h"

namespace cave
{
	class Scene;
	class Transform;

	class GameObject : public Object
	{
	public:
		GameObject();
		GameObject(const GameObject& gameObject);
		GameObject(GameObject&& gameObject) noexcept;

		virtual ~GameObject();
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other) noexcept;

		static GameObject* FindWithName(const char* name);
		static GameObject* FindGameObjectsWithTag(const char* tag);
		static GameObject* FindWithTag(const char* tag);

		void AddComponent(Component& component);
		void AddTag(const char* tag);

		void RemoveComponent(eComponentType type);

		bool CompareTag(const char* tag) const;

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

		__forceinline bool IsActive()
		{
			return mbActive;
		}

		__forceinline bool IsStatic()
		{
			return mbStatic;
		}

		__forceinline void SetLayer(int layer)
		{
			mLayer = layer;
		}

		__forceinline int GetLayer()
		{
			return mLayer;
		}

		__forceinline void SetScene(Scene& scene)
		{
			mScene = &scene;
		}

		__forceinline Scene* GetScene()
		{
			return mScene;
		}

		__forceinline std::unordered_set<const char*>* GetTags()
		{
			return &mTags;
		}

		__forceinline Transform* GetTransform()
		{
			return &mTransform;
		}

	private:
		bool mbActive;
		bool mbStatic;

		int mLayer;

		std::vector<Component*> mComponents;

		std::unordered_set<const char*> mTags;
		Transform mTransform;
		Scene* mScene;
	};
}