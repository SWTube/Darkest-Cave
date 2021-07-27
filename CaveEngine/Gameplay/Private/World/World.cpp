/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "World/World.h"

namespace cave
{
	World::World(std::string& name) 
		: mName(std::move(name))
		, mCurrentLevel(nullptr)
	{

	}

	World::World(const char* name) 
		: mName(name)
		, mCurrentLevel(nullptr)
	{

	}

	World::~World()
	{

	}
}