/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <string>

#include "CoreTypes.h"

namespace cave
{
	class GameObject;

	class Tag final
	{
	public:
		friend class TagPool;

		Tag() = delete;
		Tag(const Tag& other) = delete;
		Tag(Tag&& other) = delete;

		~Tag();
		Tag& operator=(const Tag& other) = delete;
		Tag& operator=(const Tag&& other) = delete;

		friend bool operator==(const Tag& lhs, std::string& rhs);
		friend bool operator==(const Tag& lhs, const char* rhs);
		friend bool operator!=(const Tag& lhs, std::string& rhs);
		friend bool operator!=(const Tag& lhs, const char* rhs);

	private:
		Tag(const char* name);
		Tag(std::string& name);
		Tag(const std::string& name);

	private:
		std::string mName;
	};
}