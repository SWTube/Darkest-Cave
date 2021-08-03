/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#ifdef CAVE_BUILD_DEBUG
#include <random>
#include <iostream>
#endif // CAVE_BUILD_DEBUG


#include "Assertion/Assert.h"
#include "Memory/MemoryPool.h"
#include "Object/TagPool.h"
#include "Object/Tag.h"

namespace cave
{
	MemoryPool* TagPool::mMemoryPool = nullptr;
	std::unordered_map<std::string, Tag*> TagPool::mTags;

	TagPool::~TagPool()
	{

	}

	void TagPool::Init(MemoryPool& memoryPool)
	{
		mMemoryPool = &memoryPool;
	}

	void TagPool::ShutDown()
	{
		assert(IsValid());

		
		mMemoryPool = nullptr;
	}

	void TagPool::AddTag(std::string& name)
	{
		assert(IsValid());

		Tag* tag = createTag(name);
		mTags[name] = tag;
	}

	void TagPool::AddTag(const char* name)
	{
		assert(IsValid());
		
		std::string convertedName(name);
	}

	void TagPool::RemoveTag(std::string& name)
	{
		assert(IsValid());

		auto iter = mTags.find(name);

		if (iter != mTags.end())
		{
			iter->second = nullptr;
			mMemoryPool->Deallocate(iter->second, sizeof(Tag));
		}
	}

	void TagPool::RemoveTag(const char* name)
	{
		assert(IsValid());

		std::string convertedName(name);
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

		std::string convertedName(name);
		auto iter = mTags.find(convertedName);

		return iter != mTags.end() ? iter->second : nullptr;
	}

	Tag* TagPool::createTag(std::string& name)
	{
		assert(IsValid());

		Tag* tag = new(reinterpret_cast<Tag*>(mMemoryPool->Allocate(sizeof(Tag)))) Tag(name);
		assert(tag != nullptr);

		return tag;
	}
	
	bool TagPool::IsValid()
	{
		return mMemoryPool != nullptr ? true : false;
	}

#ifdef CAVE_BUILD_DEBUG
	void TagPool::PrintElement()
	{
		for (auto begin = mTags.begin(); begin != mTags.end(); ++begin)
		{
			std::cout << (begin->second) << std::endl;
		}
	}
#endif //CAVE_BUILD_DEBUG

#ifdef CAVE_BUILD_DEBUG

	namespace TagPoolTest
	{
		void Test()
		{
			MemoryPool memoryPool(1024ul);

			TagPool::Init(memoryPool);

			const char* testString = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

			std::vector<std::string> vec;

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> disIndex(1, 20);
			std::uniform_int_distribution<int> disStr(0, 61);

			for (size_t i = 0; i < 100; ++i)
			{
				auto index = disIndex(gen);
				char* str = new char[index + 1];
				for (size_t j = 0; j < index; ++j)
				{
					str[j] = testString[disStr(gen)];
				}
				str[index] = '\0';
				std::cout << "word: " << str << std::endl;

				std::string tmp(str);
				vec.push_back(tmp);

				TagPool::AddTag(tmp);
				assert(TagPool::FindTagByName(tmp) != nullptr);

				delete str;
			}

			TagPool::PrintElement();

			for (size_t i = 0; i < 100; ++i)
			{
				TagPool::RemoveTag(vec[i]);
				assert(TagPool::FindTagByName(vec[i]) == nullptr);
			}
		}
	}
#endif // CAVE_BUILD_DEBUG
}