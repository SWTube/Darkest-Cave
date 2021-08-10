/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Renderer/Renderer.h"
#include "Assertion/Assert.h"
#include "Object/Object.h"

namespace cave
{
	class Script;
	class Tag;
	class Transform;
	class PhysicsBody;
	class Level;

	class GameObject : public Object
	{
	public:
		friend class Level;

		GameObject() = delete;
		GameObject(std::string& name);
		GameObject(const char* name);
		GameObject(std::string& name, std::string& tag);
		GameObject(std::string& name, const char* tag);
		GameObject(std::string& name, Tag& tag);
		GameObject(const char* name, std::string& tag);
		GameObject(const char* name, const char* tag);
		GameObject(const char* name, Tag& tag);
		GameObject(const GameObject& gameObject);

		virtual ~GameObject();
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other) noexcept;
	
		void InitializeScripts();
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

		void SetPhysicsBody(PhysicsBody& physicsBody);
		FORCEINLINE PhysicsBody* GetPhysicsBody() const;
		
		void SetLevel(Level& level);
		FORCEINLINE Level* GetLevel() const;

		void RemoveGameObjectInLevel();

	private:
		static std::unordered_set<std::string> mGlobalUniqueNames;

		/*Active indicates the game object was active or deactive.
		  Gameloop updates active game object for defalut option.*/
		bool mbActive = false;

		/*Layer indicates draw order.
		  Default value is 0. If value > 0, game object draw later.*/
		uint8_t mLayer;

		std::unordered_map<std::string, Script*> mScripts;
		Tag* mTag;

		Transform* mTransform;
		Renderer* mRenderer;
		PhysicsBody* mPhysicsBody;

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

	FORCEINLINE uint8_t GameObject::GetLayer() const
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

	FORCEINLINE PhysicsBody* GameObject::GetPhysicsBody() const
	{
		assert(IsValid());
		return mPhysicsBody;
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