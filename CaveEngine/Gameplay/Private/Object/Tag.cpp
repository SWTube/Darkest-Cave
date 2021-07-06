/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include <cassert>
#include <xhash>

#include "Object/Tag.h"

namespace cave
{
	Tag::Tag(const char& typeName)  :
		mTypeName(&typeName),
		mType(std::hash<std::string>{}(mTypeName))
	{
		
	}

	Tag::Tag(std::string& typeName) :
		mTypeName(std::move(typeName)),
		mType(std::hash<std::string>{}(mTypeName))
	{

	}

	Tag::~Tag()
	{

	}
}