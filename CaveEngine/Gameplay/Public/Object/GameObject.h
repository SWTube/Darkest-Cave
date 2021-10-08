/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "Assertion/Assert.h"
#include "Object/Object.h"

import cave.Core.Types.Float;
import Renderable;

namespace cave
{
	class Script;
	class Tag;
	class Transform;
	class PhysicsBody;

	class GameObject : public Object
	{
	public:
		GameObject() = delete;
		GameObject(const char* name);
		GameObject(std::string& name);
		GameObject(const std::string& name);
		GameObject(const GameObject& gameObject);
		GameObject(GameObject&& gameObject) noexcept;

		virtual ~GameObject();
		GameObject& operator=(const GameObject& other);
		GameObject& operator=(GameObject&& other) noexcept;
	
		void Init();
		void Update(float elapsedTimestep);
		void FixedUpdate(float elapsedTimestep);

		void AddScript(Script* script);
		void AddScripts(std::vector<Script*>& scripts);

		void SetTag(const char* name);
		void SetTag(std::string& name);
		void SetTag(const std::string& name);
		
		Tag* GetTag() const;

		void SetActive(bool state);
		bool IsActive() const;

		void SetStatic(bool state);
		bool IsStatic() const;

		Float2* GetPosition() const;
		Float2* GetRotation() const;
		Float2* GetScale() const;

		void SetRenderable(Renderable* renderable);
		Renderable* GetRenderable() const;

		void SetPhysicsBody(PhysicsBody* physicsBody);
		PhysicsBody* GetPhysicsBody() const;

	protected:
		std::vector<Script*> mScripts;

		bool mbStatic = false;
		bool mbActive = false;
		bool mbVisible = false;

		Tag* mTag = nullptr;

		Transform* mTransform = nullptr;
		Renderable* mRenderable = nullptr;
		PhysicsBody* mPhysicsBody = nullptr;

	private:
		static std::unordered_set<std::string> mGlobalUniqueNames;
	};
}