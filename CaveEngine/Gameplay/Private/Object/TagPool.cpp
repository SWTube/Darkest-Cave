/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#ifdef CAVE_BUILD_DEBUG
#include <random>
#include <iostream>
#endif // CAVE_BUILD_DEBUG

#include "CoreGlobals.h"
#include "Assertion/Assert.h"
#include "Object/TagPool.h"
#include "Object/Tag.h"

namespace cave
{
	bool TagPool::mbValid = false;
	std::map<std::string, Tag*> TagPool::mTags;

	TagPool::~TagPool()
	{

	}

	void TagPool::Init()
	{
		mbValid = true;
		assert(IsValid());
		AddTag("None");
	}

	void TagPool::ShutDown()
	{
		assert(IsValid());
		mbValid = false;
	}

	void TagPool::AddTag(std::string& name)
	{
		assert(IsValid());

		Tag* tag = new(gCoreMemoryPool.Allocate(sizeof(Tag))) Tag(name);
		assert(tag != nullptr);
		mTags.insert({ name, tag });
	}

	void TagPool::AddTag(const char* name)
	{
		assert(IsValid());
		
		Tag* tag = new(gCoreMemoryPool.Allocate(sizeof(Tag))) Tag(name);
		assert(tag != nullptr);
		mTags.insert({ name, tag });
	}

	void TagPool::RemoveTag(std::string& name)
	{
		assert(IsValid());

		Tag* tag = FindTagByName(name);
		assert(tag != nullptr);
		mTags.erase(name);
		gCoreMemoryPool.Deallocate(tag, sizeof(Tag));
	}

	void TagPool::RemoveTag(const char* name)
	{
		assert(IsValid());

		Tag* tag = FindTagByName(name);
		assert(tag != nullptr);
		mTags.erase(name);
		gCoreMemoryPool.Deallocate(tag, sizeof(Tag));
	}

	Tag* TagPool::FindTagByName(std::string& name)
	{
		assert(IsValid());

		auto iter = mTags.find(name);

		return iter != mTags.end() ? iter->second : nullptr;
	}

	Tag* TagPool::FindTagByName(const char* name)
	{
		assert(IsValid());

		auto iter = mTags.find(name);

		return iter != mTags.end() ? iter->second : nullptr;
	}
	
	bool TagPool::IsValid()
	{
		return mbValid;
	}

#ifdef CAVE_BUILD_DEBUG
	void TagPool::PrintElement()
	{
		assert(IsValid());
		std::cout << '\n' << std::endl;
		for (auto begin = mTags.begin(); begin != mTags.end(); ++begin)
		{
			std::cout << (begin->second)->GetName() << std::endl;
		}
	}
#endif //CAVE_BUILD_DEBUG

#ifdef CAVE_BUILD_DEBUG

	namespace TagPoolTest
	{
		void Test()
		{
			TagPool::Init();
			assert(TagPool::IsValid());
			
			const char* testString = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

			std::vector<std::string> vecString;
			std::vector<char*> vecConstChar;

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
				TagPool::AddTag(element);
				assert(TagPool::FindTagByName(element) != nullptr);
			}

			for (auto element : vecConstChar)
			{
				assert(TagPool::FindTagByName(element)->GetName() == element);
				TagPool::RemoveTag(element);
				assert(TagPool::FindTagByName(element) == nullptr);
				delete element;
			}
		}
	}
#endif // CAVE_BUILD_DEBUG
}