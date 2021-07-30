/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <vector>
#include <map>

#include "Engine.h"
#include "Object/Object.h"
#include "Assertion/Assert.h"

namespace cave
{
	class Controller;
	class Script;
	class Tag;
	class Transform;
	class Physics;
	class Level;

	class GameObject : public Object
	{
	public:
		GameObject();
		GameObject(std::string& name);
		GameObject(const char* name);
		GameObject(std::string& name, std::string& tag);
		GameObject(std::string& name, const char* tag);
		GameObject(std::string& name, Tag& tag);
		GameObject(const char* name, std::string& tag);
		GameObject(const char* name, const char* tag);
		GameObject(const char* name, Tag& tag);
		GameObject(const GameObject& gameObject);
		GameObject(GameObject&& gameObject) noexcept;

		virtual ~GameObject();
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	
		void Init();

		void UpdateScripts();
		void FixedUpdateScripts();

		void AddScript(Script& script);
		void AddScripts(std::vector<Script*>& scripts);

		void RemoveScript(std::string& name);
		void RemoveScript(const char* name);
		void RemoveScripts(std::vector<std::string>& names);
		void RemoveScripts(std::vector<const char*>& names);

		Script* FindScriptByName(std::string& name);
		Script* FindScriptByName(const char* name);

		FORCEINLINE Tag* GetTag() const;

		void SetActive(bool state);
		FORCEINLINE bool IsActive() const;

		FORCEINLINE void SetLayer(unsigned char layer);
		FORCEINLINE uint8_t GetLayer() const;

		FORCEINLINE Transform* GetTransform() const;

		void SetRenderer(Renderer& renderer);
		FORCEINLINE Renderer* GetRenderer() const;

		void SetPhysics(Physics& physics);
		FORCEINLINE Physics* GetPhysics() const;
		
		FORCEINLINE Level* GetLevel() const;

		void RemoveGameObjectInLevel();

	private:
		void setLevel(Level& level);

	private:
		/*Active indicates the game object was active or deactive.
		  Gameloop updates active game object for defalut option.*/
		bool mbActive = false;

		/*Layer indicates draw order.
		  Default value is 0. If value > 0, game object draw later.*/
		uint8_t mLayer;

		std::map<std::string, Script*> mScripts;
		Tag* mTag;

		Transform* mTransform;
		Renderer* mRenderer;
		Physics* mPhysics;

		Level* mLevel;
	};

	FORCEINLINE Tag* GameObject::GetTag() const
	{
		assert(IsValid() & (mTag != nullptr));
		return mTag;
	}

	FORCEINLINE bool GameObject::IsActive() const
	{
		assert(IsValid());
		return mbActive;
	}

	FORCEINLINE void GameObject::SetLayer(unsigned char layer)
	{
		assert(IsValid());
		mLayer = layer;
	}

	FORCEINLINE unsigned char GameObject::GetLayer() const
	{
		assert(IsValid());
		return mLayer;
	}

	FORCEINLINE Transform* GameObject::GetTransform() const
	{
		assert(IsValid() & (mTransform != nullptr));
		return mTransform;
	}

	FORCEINLINE Renderer* GameObject::GetRenderer() const
	{
		assert(IsValid());
		return mRenderer;
	}

	FORCEINLINE Physics* GameObject::GetPhysics() const
	{
		assert(IsValid());
		return mPhysics;
	}

	FORCEINLINE Level* GameObject::GetLevel() const
	{
		assert(IsValid());
		return mLevel;
	}

#ifdef CAVE_BUILD_DEBUG
	namespace GameObjectTest
	{
		void Test();
	}
#endif //CAVE_BUILD_DEBUG
}