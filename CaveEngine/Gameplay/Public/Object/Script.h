/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>
#include <unordered_set>

#include "CoreTypes.h"
#include "Object/Object.h"

namespace cave
{	
	class GameObject;

	class Script : public Object
    {
    public:
		Script() = delete;
		Script(std::string& name);
		Script(const char* name);
		Script(const Script& other);
		Script(Script&& other) = delete;

		virtual ~Script();
		Script& operator=(const Script& other) = delete;
		Script& operator=(Script&& other) = delete;

		virtual void Init(GameObject& gameObject);
		virtual void FixedUpdate(GameObject& gameObject, float elapsedTime);
		virtual void Update(GameObject& gameObject, float elapsedTime);

	private:
		static std::unordered_set<std::string> mGlobalUniqueName;
    };
}