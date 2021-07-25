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

#include "Object/Script.h"

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
#endif //CAVE_BUILD_DEBUG
}