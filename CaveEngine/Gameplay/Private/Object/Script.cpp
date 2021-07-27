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
#include "Object/Transform.h"

namespace cave
{
	std::unordered_set<std::string> Script::mGlobalUniqueName;

	Script::Script(std::string& name)
		: Object(name)
	{
		assert(!mGlobalUniqueName.contains(name));
		mGlobalUniqueName.insert(name);
	}

	Script::Script(const char* name)
		: Object(name)
	{
		assert(!mGlobalUniqueName.contains(name));
		mGlobalUniqueName.insert(name);
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
		void Test()
		{
			const char* testString = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

			std::vector<std::string> vecString;
			std::vector<char*> vecConstChar;
			std::vector<Script*> vec;

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> disIndex(1, 40);
			std::uniform_int_distribution<int> disStr(0, 61);

			for (size_t i = 0; i < 100; ++i)
			{
				int index = disIndex(gen);
				char* str = new char[index + 1];
				for (int j = 0; j < index; ++j)
				{
					str[j] = testString[disStr(gen)];
				}
				str[index] = '\0';
				std::cout << "word: " << str << std::endl;

				vecConstChar.push_back(str);
			}

			for (auto element : vecConstChar)
			{
				Script* script = new Script(element);
				vec.push_back(script);
			}

			for (auto element : vec)
			{
				std::cout << element->GetName() << std::endl;
			}

			for (auto element : vec)
			{
				delete element;
			}

			for (auto element : vecConstChar)
			{
				delete element;
			}
		}
	}

	TestScript::TestScript(const char* name, uint32_t spriteIndex, uint32_t textureIndex, float speed)
		: Script(name)
		, mSpriteIndex(spriteIndex)
		, mTextureIndex(textureIndex)
		, mNextTextureIndex(mTextureIndex + 1)
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
		gameObject.GetTransform()->GetPosition()->X += mSpeed;
		if (gameObject.GetTransform()->GetPosition()->X > 250.f)
		{
			gameObject.GetRenderer()->SetSpriteTexture(mSpriteIndex, mNextTextureIndex);
		}
		gameObject.GetRenderer()->SetSpritePosition(mSpriteIndex, *(gameObject.GetTransform()->GetPosition()));
		if (gameObject.GetTransform()->GetPosition()->X > 400.f)
		{
			gameObject.RemoveGameObjectInLevel();
		}
	}

	void TestScript::Update(GameObject& gameObject)
	{
	
	}

	uint32_t TestScript::GetTextureIndex() const
	{
		return mTextureIndex;
	}
#endif //CAVE_BUILD_DEBUG
}