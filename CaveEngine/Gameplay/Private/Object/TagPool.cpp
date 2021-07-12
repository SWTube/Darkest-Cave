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
	Tag* TagPool::mTags = nullptr;
	size_t TagPool::mMaxTagCount = 0;
	std::unordered_map<std::string, size_t> TagPool::mTagIndex;

	TagPool::~TagPool()
	{

	}

	void TagPool::Init(MemoryPool& memoryPool)
	{
		mMemoryPool = &memoryPool;
		mMaxTagCount = 100;
		mTags = reinterpret_cast<Tag*>(mMemoryPool->Allocate(sizeof(Tag) * mMaxTagCount));

		for (size_t index = 0; index < mMaxTagCount; ++index)
		{
			mTags[index].setValid(false);
		}
	}

	void TagPool::ShutDown()
	{
		assert(IsValid());

		mMemoryPool->Deallocate(mTags, sizeof(Tag) * mMaxTagCount);
		mMaxTagCount = 0;
		mTags = nullptr;
		mMemoryPool = nullptr;
	}

	void TagPool::AddTag(std::string& name)
	{
		assert(IsValid());

		Tag* tag = availableTag(name);
		new(tag) Tag(name);
	}

	void TagPool::AddTag(const char* name)
	{
		assert(IsValid());
		
		std::string convertedName(name);

		Tag* tag = availableTag(convertedName);
		new(tag) Tag(convertedName);
	}

	void TagPool::RemoveTag(std::string& name)
	{
		assert(IsValid());

		auto iter = mTagIndex.find(name);

		if (iter != mTagIndex.end())
		{
			mTags[iter->second].~Tag();
			mTagIndex.erase(name);
		}
	}

	void TagPool::RemoveTag(const char* name)
	{
		assert(IsValid());

		std::string convertedName(name);

		auto iter = mTagIndex.find(convertedName);
		
		if (iter != mTagIndex.end())
		{
			mTags[iter->second].~Tag();
			mTagIndex.erase(convertedName);
		}
	}

	Tag* TagPool::FindTagByName(std::string& name)
	{
		assert(IsValid());

		auto iter = mTagIndex.find(name);

		return iter != mTagIndex.end() ? &mTags[iter->second] : nullptr;
	}

	Tag* TagPool::FindTagByName(const char* name)
	{
		assert(IsValid());

		std::string convertedName(name);

		auto iter = mTagIndex.find(name);

		return iter != mTagIndex.end() ? &mTags[iter->second] : nullptr;
	}

	Tag* TagPool::availableTag(std::string& name)
	{
		for (size_t index = 0; index < mMaxTagCount; ++index)
		{
			if (!mTags[index].IsValid())
			{
				mTagIndex[name] = index;
				return &mTags[index];
			}
		}

		return nullptr;
	}
	
	bool TagPool::IsValid()
	{
		return mMemoryPool != nullptr && mTags != nullptr ? true : false;
	}

#ifdef CAVE_BUILD_DEBUG

	namespace TagPoolTest
	{
		void Test()
		{
			MemoryPool memoryPool(1024ul);

			TagPool::Init(memoryPool);

			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> disIndex(1, 20);
			std::uniform_int_distribution<int> disStr(32, 122);

			for (size_t i = 0; i < 100; ++i)
			{
				auto index = disIndex(gen);
				char* str = new char[index + 1];
				for (size_t j = 0; j < index; ++j)
				{
					str[j] = disStr(gen);
				}
				str[index] = '\0';
				std::cout << "word: " << str << std::endl;

				std::string tmp(str);

				TagPool::AddTag(tmp);
				assert(TagPool::FindTagByName(tmp) != nullptr);
				TagPool::RemoveTag(tmp);
				assert(TagPool::FindTagByName(tmp) == nullptr);

				delete str;
			}
		}
	}
#endif // CAVE_BUILD_DEBUG
}