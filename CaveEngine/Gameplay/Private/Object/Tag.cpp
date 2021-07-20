/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include <cassert>
#include <xhash>

#include "Object/Tag.h"

namespace cave
{
	Tag::Tag(std::string& name) 
		: mName(name) 
		, mCompareSeed(std::hash<std::string>{}(mName))
	{

	}

	Tag::~Tag()
	{

	}
}