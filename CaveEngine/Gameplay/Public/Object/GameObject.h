/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <vector>
#include <map>

#include "Object/Obejct.h"
#include "Assertion/Assert.h"

namespace cave
{
	class Controller;
	class Script;
	class Tag;
	class Transform;
	class Renderer;
	class Physics;
	class Level;

	class GameObject : public Object
	{
	public:
		GameObject() = delete;
		GameObject(std::string& name, bool isControlled = false);
		GameObject(const char* name = "GameObject", bool isControlled = false);
		GameObject(const GameObject& gameObject);
		GameObject(GameObject&& gameObject) noexcept;

		virtual ~GameObject();
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other) noexcept;
		
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

		void SetTag(std::string& name);
		void SetTag(const char* name);
		FORCEINLINE Tag* GetTag() const;

		void SetActive(bool state);
		FORCEINLINE bool IsActive() const;

		FORCEINLINE void SetStatic(bool state);
		FORCEINLINE bool IsStatic() const;

		FORCEINLINE void SetLayer(unsigned char layer);
		FORCEINLINE unsigned char GetLayer() const;

		void SetTransform(Transform& transform);
		FORCEINLINE Transform* GetTransform() const;

		void SetRenderer(Renderer& renderer);
		FORCEINLINE Renderer* GetRenderer() const;

		void SetPhysics(Physics& physics);
		FORCEINLINE Physics* GetPhysics() const;

		void SetController(Controller& controller);
		FORCEINLINE Controller* GetController() const;
		FORCEINLINE bool IsControlled() const;
		
		FORCEINLINE void SetLevel(Level& level);
		FORCEINLINE Level* GetLevel() const;
		void RemoveGameObjectInLevel();

	private:
		/*Active indicates the game object was active or deactive.
		  Gameloop updates active game object for defalut option.*/
		bool mbActive = false;
		bool mbStatic;
		bool mbControlled;

		/*Layer indicates draw order.
		  Default value is 0. If value > 0, game object draw later.*/
		unsigned char mLayer;

		std::map<std::string, Script*> mScripts;

		Tag* mTag;

		Transform* mTransform;
		Renderer* mRenderer;
		Physics* mPhysics;
		Controller* mController;

		Level* mLevel;
	};

	FORCEINLINE Tag* GameObject::GetTag() const
	{
		assert(IsValid());
		assert(mTag != nullptr);
		return mTag;
	}

	FORCEINLINE bool GameObject::IsActive() const
	{
		assert(IsValid());
		return mbActive;
	}

	FORCEINLINE void GameObject::SetStatic(bool state)
	{
		assert(IsValid());
		mbStatic = state;
	}

	FORCEINLINE bool GameObject::IsStatic() const
	{
		assert(IsValid());
		return mbStatic;
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
		assert(IsValid());
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

	FORCEINLINE Controller* GameObject::GetController() const
	{
		assert(IsValid() & IsControlled());
		return mController;
	}

	FORCEINLINE bool GameObject::IsControlled() const
	{
		assert(IsValid());
		return mbControlled;
	}

	FORCEINLINE void GameObject::SetLevel(Level& level)
	{
		assert(IsValid());
		mLevel = &level;
	}

	FORCEINLINE Level* GameObject::GetLevel() const
	{
		assert(IsValid());
		return mLevel;
	}
}