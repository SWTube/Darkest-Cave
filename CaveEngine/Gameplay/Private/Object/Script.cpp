/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#ifdef CAVE_BUILD_DEBUG
#include <random>
#include <iostream>
#include <limits>
#include <vector>
#endif // CAVE_BUILD_DEBUG

#include "Assertion/Assert.h"
#include "Object/Script.h"
#include "Object/GameObject.h"
#include "Object/Transform.h"

namespace cave
{
	std::unordered_set<std::string> Script::mGlobalUniqueName;

	Script::Script(std::string& name)
		: Object(name, mGlobalUniqueName)
	{

	}

	Script::Script(const char* name)
		: Object(name, mGlobalUniqueName)
	{

	}

	Script::Script(const Script& other)
		: Object(other, mGlobalUniqueName)
	{
	
	}

	Script::~Script()
	{
	}

	void Script::Init(GameObject& gameObject)
	{

	}

	void Script::FixedUpdate(GameObject& gameObject, float elapsedTime)
	{

	}

	void Script::Update(GameObject& gameObject, float elapsedTime)
	{

	}
}