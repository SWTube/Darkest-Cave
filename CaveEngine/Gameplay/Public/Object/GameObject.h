/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include <map>

#include "Object/Obejct.h"
#include "Tmp/Transform.h"

namespace cave
{
	class Component;
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

		static void	CreatePrimitive();
		static void Find();
		static void FindGameObjectWithTag();
		static void FindWithTag();

		void AddComponent(Component& component);
		void BroadcastMessage();
		void CompareTag();
		void GetComponent();
		void GetComponentInChildren();
		void GetComponentInParent();
		void GetComponents();
		void GetComponentsInChildren();
		void GetComponentsInParent();

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

		void AddTag(const char* tag);
		void FindTag(const char* tag);

		__forceinline std::vector<const char*>* GetTags()
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

		std::map<unsigned char, std::vector<Component*>> mComponents;

		std::vector<const char*> mTags;
		Transform mTransform;
		Scene* mScene;
	};
}