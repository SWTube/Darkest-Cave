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
		: mName(name)
	{

	}

	Tag::Tag(const char* name)
		: mName(name)
	{

	}

	Tag::~Tag()
	{
		
	}

	bool operator==(const Tag& lhs, std::string& rhs)
	{
		Tag* tag = TagPool::FindTagByName(rhs);
		assert(tag != nullptr);
		return &lhs == tag;
	}

	bool operator==(const Tag& lhs, const char* name)
	{
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);
		return &lhs == tag;
	}

	bool operator!=(const Tag& lhs, std::string& name)
	{
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);
		return &lhs != tag;
	}

	bool operator!=(const Tag& lhs, const char* name)
	{
		Tag* tag = TagPool::FindTagByName(name);
		assert(tag != nullptr);
		return &lhs != tag;
	}
}