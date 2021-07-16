/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <string>
#include <unordered_set>

#include "Object/Obejct.h"

namespace cave
{	
	class GameObject;

	class Script : public Object
    {
    public:
		Script();
		Script(const Script& other) = delete;
		Script(Script&& other) = delete;

		virtual ~Script();
		Script& operator=(const Script& other) = delete;
		Script& operator=(Script&& other) = delete;

		__forceinline const std::string& GetName() const
		{
			return mName;
		}

		virtual void FixedUpdate(GameObject& gameObject);
		virtual void Update(GameObject& gameObject);

    private:
		/*Global unique name.*/
		static std::unordered_set<std::string> mGUName;

		/*Script's name.*/
		std::string mName;
    };
}