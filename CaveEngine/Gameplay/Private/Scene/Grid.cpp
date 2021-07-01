/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Object/GameObject.h"
#include "Scene/Grid.h"

namespace cave
{
	Grid::Grid()
	{

	}

	Grid::~Grid()
	{

	}

	void Grid::AddObject(GameObject& object)
	{
		if (object.IsActive())
		{
			mActivateObject[object.GetName()] = &object;
			return;
		}
		mDeactivateObject[object.GetName()] = &object;
	}

	void Grid::RemoveObject(GameObject& object)
	{
		if (mActivateObject[object.GetName()] != nullptr)
		{
			mActivateObject.erase(object.GetName());
		}

		else if (mDeactivateObject[object.GetName()] != nullptr)
		{
			mDeactivateObject.erase(object.GetName());
		}
	}

	void Grid::MoveObject(std::string& name)
	{
		if (mActivateObject[name] != nullptr)
		{
			mDeactivateObject[name] = mActivateObject[name];
			mActivateObject.erase(name);
			return;
		}

		mActivateObject[name] = mDeactivateObject[name];
		mDeactivateObject.erase(name);
	}

	GameObject* Grid::FindObjectByName(std::string& name)
	{
		if (mActivateObject[name] != nullptr)
		{
			return mActivateObject[name];
		}

		else if (mDeactivateObject[name] != nullptr)
		{
			return mDeactivateObject[name];
		}

		return nullptr;
	}

	std::vector<GameObject*>& Grid::FindObjectsByTag(std::string& tag)
	{
		std::vector<GameObject*> result;

		for (auto element : mActivateObject)
		{
			if (element.second->CompareTag(tag.c_str()))
			{
				result.push_back(element.second);
			}
		}

		for (auto element : mDeactivateObject)
		{
			if (element.second->CompareTag(tag.c_str()))
			{
				result.push_back(element.second);
			}
		}

		return result;
	}
}