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
	std::unordered_map<std::string, Tag*> TagPool::mTags;

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
		for (auto iter = mTags.begin(); iter != mTags.end(); ++iter)
		{
			Tag* tag = iter->second;
			iter->second = nullptr;
			assert(tag != nullptr);
			delete tag;
		}
		mTags.clear();
		mbValid = false;
	}

	void TagPool::AddTag(const char* name)
	{
		assert(IsValid() && !mTags.contains(name) && name != nullptr);
		
		Tag* tag = new Tag(name);
		assert(tag != nullptr);
		mTags.insert({ name, tag });
	}

	void TagPool::AddTag(std::string& name)
	{
		assert(IsValid() && !mTags.contains(name));

		Tag* tag = new Tag(name);
		assert(tag != nullptr);
		mTags.insert({ name, tag });
	}

	void TagPool::AddTag(const std::string& name)
	{
		assert(IsValid() && !mTags.contains(name));

		Tag* tag = new Tag(name);
		assert(tag != nullptr);
		mTags.insert({ name, tag });
	}

	void TagPool::RemoveTag(const char* name)
	{
		assert(IsValid() && name != nullptr);

		Tag* tag = FindTagByName(name);
		assert(tag != nullptr);
		mTags.erase(name);
		delete tag;
	}

	void TagPool::RemoveTag(std::string& name)
	{
		assert(IsValid());

		Tag* tag = FindTagByName(name);
		assert(tag != nullptr);
		mTags.erase(name);
		delete tag;
	}

	void TagPool::RemoveTag(const std::string& name)
	{
		assert(IsValid());

		Tag* tag = FindTagByName(name);
		assert(tag != nullptr);
		mTags.erase(name);
		delete tag;
	}

	Tag* TagPool::FindTagByName(const char* name)
	{
		assert(IsValid());
		assert(name != nullptr);

		auto iter = mTags.find(name);

		return iter != mTags.end() ? iter->second : nullptr;
	}

	Tag* TagPool::FindTagByName(std::string& name)
	{
		assert(IsValid());

		auto iter = mTags.find(name);

		return iter != mTags.end() ? iter->second : nullptr;
	}

	Tag* TagPool::FindTagByName(const std::string& name)
	{
		assert(IsValid());

		auto iter = mTags.find(name);

		return iter != mTags.end() ? iter->second : nullptr;
	}
	
	bool TagPool::IsValid()
	{
		return mbValid;
	}
}