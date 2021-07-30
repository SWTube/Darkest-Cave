/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <unordered_set>

#include "CoreTypes.h"
#include "Object/Object.h"
#include "Object/GameObject.h"

namespace cave
{	
	class Script : public Object
    {
    public:
		Script() = delete;
		Script(std::string& name);
		Script(const char* name);
		Script(const Script& other) = delete;
		Script(Script&& other) = delete;

		virtual ~Script();
		Script& operator=(const Script& other) = delete;
		Script& operator=(Script&& other) = delete;

		virtual void Init(GameObject& gameObject);
		virtual void FixedUpdate(GameObject& gameObject);
		virtual void Update(GameObject& gameObject);

	private:
		static std::unordered_set<std::string> mGlobalUniqueName;
    };
#ifdef CAVE_BUILD_DEBUG
	namespace ScriptTest
	{
		void Test();
	}

	class TestScript : public Script
	{
	public:
		TestScript(const char* name, uint32_t spriteIndex, uint32_t textureIndex, float speed);

		virtual ~TestScript();

		virtual void Init(GameObject& gameObject) override;
		virtual void FixedUpdate(GameObject& gameObject) override;
		virtual void Update(GameObject& gameObject) override;

		uint32_t GetTextureIndex() const;

	private:
		uint32_t mSpriteIndex;
		uint32_t mTextureIndex;
		uint32_t mNextTextureIndex;
		float mSpeed;
	};
#endif //CAVE_BUILD_DEBUG
}