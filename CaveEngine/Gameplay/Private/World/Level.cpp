/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "World/Level.h"
#include "Assertion/Assert.h"
#include "Object/GameObject.h"

namespace cave
{
	Level::Level(std::string& name) :
		mName(name),
		mMap(nullptr)
	{

	}

	Level::Level(const char* name) :
		mName(name),
		mMap(nullptr)
	{

	}

	void Level::SetName(std::string& name)
	{
		mName = std::move(name);
	}

	void Level::SetName(const char* name)
	{
		assert(name != nullptr);
		mName = name;
	}

	void Level::AddGameObject(GameObject& gameObject)
	{
		mGameObjectsSortedByTag.insert({ gameObject.GetTag(), &gameObject });
		if (!gameObject.IsActive())
		{
			mDeactiveGameObjects.insert({ gameObject.GetName(), &gameObject });
			return;
		}
		mActiveGameObjects.insert({ gameObject.GetName(), &gameObject });
	}

	void Level::RemoveGameObject(std::string& name)
	{
			
	}
}