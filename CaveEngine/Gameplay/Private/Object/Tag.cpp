/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include <xhash>

#include "Object/GameObject.h"
#include "Object/Tag.h"
#include "Object/TagPool.h"

namespace cave
{
	Tag::Tag(std::string& name)
		: Object(name)
	{

	}

	Tag::Tag(const char* name)
		: Object(name)
	{

	}

	Tag::~Tag()
	{
		assert(IsValid());
	}

	bool operator==(const Tag& lhs, std::string& rhs)
	{
		assert(lhs.IsValid());
		Tag* tag = TagPool::FindTagByName(rhs);
		assert(tag != nullptr);
		return lhs == *tag;
	}

	bool operator==(const Tag& lhs, const char* name)
	{
		assert(lhs.IsValid());
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);
		return lhs == *tag;
	}

	bool operator!=(const Tag& lhs, std::string& name)
	{
		assert(lhs.IsValid());
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);
		return lhs != *tag;
	}

	bool operator!=(const Tag& lhs, const char* name)
	{
		assert(lhs.IsValid());
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);
		return lhs != *tag;
	}
}