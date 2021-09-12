/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#ifdef CAVE_BUILD_DEBUG
#include <random>
#include <iostream>
#include <limits>
#include <vector>
#endif // CAVE_BUILD_DEBUG

#include "Assertion/Assert.h"
#include "Object/Script.h"
#include "Object/GameObject.h"
#include "Object/Transform.h"

namespace cave
{
	std::unordered_set<std::string> Script::mGlobalUniqueName;

	Script::Script(std::string& name)
		: Object(name, mGlobalUniqueName)
	{

	}

	Script::Script(const char* name)
		: Object(name, mGlobalUniqueName)
	{

	}

	Script::Script(const Script& other)
		: Object(other, mGlobalUniqueName)
	{
	
	}

	Script::~Script()
	{
	}

	void Script::Init(GameObject& gameObject)
	{

	}

	void Script::FixedUpdate(GameObject& gameObject)
	{
	}

	void Script::Update(GameObject& gameObject)
	{
	}

#ifdef CAVE_BUILD_DEBUG
	namespace ScriptTest
	{
	}

	TestScript::TestScript(const char* name, uint32_t spriteIndex, uint32_t textureIndex, float speed)
		: Script(name)
		, mSpriteIndex(spriteIndex)
		, mTextureIndex(textureIndex)
		, mNextTextureIndex(100)
		, mSpeed(speed)
	{
		
	}

	TestScript::~TestScript()
	{

	}

	void TestScript::Init(GameObject& gameObject)
	{
		gameObject.GetTransform()->GetPosition()->Y = 200.f;
	}

	void TestScript::FixedUpdate(GameObject& gameObject)
	{
		/*gameObject.GetTransform()->GetPosition()->X += mSpeed;
		if (gameObject.GetTransform()->GetPosition()->X > 250.f)
		{
			gameObject.GetRenderer()->SetSpriteTexture(mSpriteIndex, mNextTextureIndex);
		}
		gameObject.GetRenderer()->SetSpritePosition(mSpriteIndex, *(gameObject.GetTransform()->GetPosition()));
		if (gameObject.GetTransform()->GetPosition()->X > 400.f)
		{
			gameObject.RemoveGameObjectInLevel();
		}*/
	}

	void TestScript::Update(GameObject& gameObject)
	{
		/*gameObject.GetTransform()->GetPosition()->X += mSpeed;
		if (gameObject.GetTransform()->GetPosition()->X > 250.f)
		{
			gameObject.GetRenderer()->SetSpriteTexture(mSpriteIndex, mNextTextureIndex);
		}
		gameObject.GetRenderer()->SetSpritePosition(mSpriteIndex, *(gameObject.GetTransform()->GetPosition()));
		if (gameObject.GetTransform()->GetPosition()->X > 400.f)
		{
			gameObject.RemoveGameObjectInLevel();
		}*/
	}

	void TestScript::SetSpriteIndex(uint32_t index)
	{
		mSpriteIndex = index;
	}

	uint32_t TestScript::GetTextureIndex() const
	{
		return mTextureIndex;
	}

	void TestScript::SetSpeed(float speed)
	{
		mSpeed = speed;
	}
#endif //CAVE_BUILD_DEBUG
}