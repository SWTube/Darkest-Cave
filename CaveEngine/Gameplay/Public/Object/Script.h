/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <string>
#include <set>

#include "CoreTypes.h"
#include "Object/Obejct.h"
#include "Object/GameObject.h"

namespace cave
{	
	class Script : public Object
    {
    public:
		Script() = delete;
		Script(std::string& name);
		Script(const char* name);
		Script(const Script& other) = delete;
		Script(Script&& other) = delete;

		virtual ~Script();
		Script& operator=(const Script& other) = delete;
		Script& operator=(Script&& other) = delete;

		virtual void FixedUpdate(GameObject& gameObject);
		virtual void Update(GameObject& gameObject);
    };
}