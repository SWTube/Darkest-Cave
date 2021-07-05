/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include <cassert>

#include "Object/Tag.h"

namespace cave
{
	Tag::Tag() :
		mTypeName(nullptr),
		mType(0)
	{

	}

	Tag::Tag(const char* typeName)
	{
		assert(typeName != nullptr);

		mTypeName = typeName;

	}
}