/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <vector>

#include "Object/Obejct.h"

namespace cave
{
	class Script;
	class Tag;
	class Transform;
	class Renderer;
	class Physics;

	class World;

	class GameObject final : public Object
	{
	public:
		GameObject();
		GameObject(const GameObject& gameObject);
		GameObject(GameObject&& gameObject) noexcept;

		virtual ~GameObject();
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other) noexcept;
		
		void UpdateScripts();

		FORCEINLINE void SetTag(Tag& tag)
		{
			mTag = &tag;
		}

		FORCEINLINE Tag* GetTag() const
		{
			return mTag;
		}

		FORCEINLINE void SetActive(bool state)
		{
			mbActive = state;
		}

		FORCEINLINE void SetStatic(bool state)
		{
			mbStatic = state;
		}

		FORCEINLINE bool IsActive() const
		{
			return mbActive;
		}

		FORCEINLINE bool IsStatic() const
		{
			return mbStatic;
		}

		FORCEINLINE void SetLayer(unsigned char layer)
		{
			mLayer = layer;
		}

		FORCEINLINE unsigned char GetLayer() const
		{
			return mLayer;
		}
		
		FORCEINLINE void SetName(std::string& name)
		{
			mName = std::move(name);
		}

		FORCEINLINE std::string& GetName()
		{
			return mName;
		}

		FORCEINLINE Transform* GetTransform()
		{
			return mTransform;
		}

	private:
		bool mbActive;
		bool mbStatic;

		unsigned char mLayer;

		std::vector<Script*> mScripts;

		std::string mName;
		Tag* mTag;

		Transform* mTransform;
		Renderer* mRenderer;
		Physics* mPhysics;

		World* mOwner;
	};
}